/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256,  // 空格
  TK_EQ,            // ==
  TK_NUM,           // 数字
  TK_HEX,           // 十六进制
  TK_REG,           // 寄存器，例如 $eax
  TK_PLUS,          // +
  TK_MINUS,         // -
  TK_MUL,           // *
  TK_DIV,           // /
  TK_LPAREN,        // (
  TK_RPAREN,        // )
  TK_DEREF,         // 一元 *
  TK_NEG,           // 一元 -
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {
  {" +", TK_NOTYPE},          // spaces
  {"\\+", TK_PLUS},           // plus
  {"-", TK_MINUS},            // minus
  {"\\*", TK_MUL},            // multiply or deref
  {"/", TK_DIV},              // divide
  {"\\(", TK_LPAREN},         // left parenthesis
  {"\\)", TK_RPAREN},         // right parenthesis
  {"0x[0-9a-fA-F]+", TK_HEX}, // hex number
  {"[0-9]+", TK_NUM},         // decimal number
  {"\\$[a-zA-Z]+", TK_REG},   // register
  {"==", TK_EQ},              // equal
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        switch (rules[i].token_type) {
          case TK_NOTYPE: break; // 忽略空格
          case TK_NUM:
          case TK_HEX:
          case TK_REG:
          case TK_PLUS:
          case TK_MINUS:
          case TK_MUL:
          case TK_DIV:
          case TK_LPAREN:
          case TK_RPAREN:
          case TK_EQ:
            tokens[nr_token].type = rules[i].token_type;
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            tokens[nr_token].str[substr_len] = '\0';
            nr_token++;
            break;
          default:
            printf("Unknown token type %d\n", rules[i].token_type);
            return false;
        }        

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

static int get_precedence(int type) {
  switch(type) {
    case TK_EQ: return 1;
    case TK_PLUS:
    case TK_MINUS: return 2;
    case TK_MUL:
    case TK_DIV: return 3;
    case TK_NEG:
    case TK_DEREF: return 4;
    default: return 0;
  }
}

static int find_main_op(int p, int q) {
  int level = 0;     // 括号深度
  int min_pri = 100; // 初始值很大
  int main_op = -1;
  for (int i = p; i <= q; i++) {
    int type = tokens[i].type;
    if (type == TK_LPAREN) { level++; continue; }
    if (type == TK_RPAREN) { level--; continue; }
    if (level == 0) {
      int pri = get_precedence(type);
      if (pri > 0) {
        if (pri <= min_pri) {
          min_pri = pri;
          main_op = i;
        }
      }
    }
  }

  return main_op;
}

static bool check_parentheses(int p, int q, bool *success) {
  if (tokens[p].type != TK_LPAREN || tokens[q].type != TK_RPAREN)
    return false;

  int level = 0;
  for (int i = p; i <= q; i++) {
    if (tokens[i].type == TK_LPAREN) level++;
    else if (tokens[i].type == TK_RPAREN) level--;
    if (level == 0 && i < q) return false;
  }

  if (level != 0) {
    *success = false;
    return false;
  }

  return true;
}

word_t eval(int p, int q, bool *success) {
  if (p > q) { *success = false; return 0; }
  else if (p == q) {
    // 单个 token
    if (tokens[p].type == TK_NUM) return atoi(tokens[p].str);
    if (tokens[p].type == TK_HEX) return strtoul(tokens[p].str, NULL, 16);
    if (tokens[p].type == TK_REG) return isa_reg_str2val(tokens[p].str + 1, success);
    *success = false;
    return 0;
  }
  else if (check_parentheses(p, q, success) == true) {
    printf("check_parentheses(%d, %d) == true\n", p, q);
    return eval(p + 1, q - 1, success);
  }
  else {
    int op = find_main_op(p, q);
    if (op < 0) { *success = false; return 0; }

    word_t val1 = 0, val2 = 0;
    if (tokens[op].type != TK_NEG && tokens[op].type != TK_DEREF)
      val1 = eval(p, op-1, success);
    val2 = eval(op+1, q, success);
    if (!*success) return 0;

    switch (tokens[op].type) {
      case TK_PLUS: return val1 + val2;
      case TK_MINUS: return val1 - val2;
      case TK_MUL: return val1 * val2;
      case TK_DIV: return val1 / val2;
      case TK_EQ: return val1 == val2;
      case TK_NEG: return -val2;
      // case TK_DEREF: return vaddr_read(val2, 4); // 读取内存
      default: *success = false; return 0;
    }
  }
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  // 标记一元操作符
  for (int i = 0; i < nr_token; i++) {
    if (tokens[i].type == TK_MUL) {
      if (i == 0 || (tokens[i-1].type != TK_NUM && tokens[i-1].type != TK_HEX &&
                     tokens[i-1].type != TK_REG && tokens[i-1].type != TK_RPAREN))
        tokens[i].type = TK_DEREF;
    }
    if (tokens[i].type == TK_MINUS) {
      if (i == 0 || (tokens[i-1].type != TK_NUM && tokens[i-1].type != TK_HEX &&
                     tokens[i-1].type != TK_REG && tokens[i-1].type != TK_RPAREN))
        tokens[i].type = TK_NEG;
    }
  }

  return eval(0, nr_token-1, success);
}
