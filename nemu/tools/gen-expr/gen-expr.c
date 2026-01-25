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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

// 随机选择 0~n-1
static int choose(int n) {
  return rand() % n;
}

// 往 buf 里加一个字符
static void gen(char c) {
  int len = strlen(buf);
  buf[len] = c;
  buf[len + 1] = '\0';
}

// 生成一个随机数字
static void gen_num() {
  int num = rand() % 100; // 0~99
  char tmp[16];
  sprintf(tmp, "%d", num);
  strcat(buf, tmp);
}

// 生成随机运算符 + - * /
static void gen_rand_op() {
  char ops[] = "+-*/";
  char op = ops[choose(4)];
  gen(op);
}

// 生成随机表达式
static void gen_rand_expr() {
  static int depth = 0;
  depth++;
  if (depth > 3) { // 避免生成太深的表达式
    gen_num();
    depth--;
    return;
  }

  switch (choose(3)) {
    case 0:
      gen_num();
      break;
    case 1:
      gen('(');
      gen_rand_expr();
      gen(')');
      break;
    default:
      gen_rand_expr();
      // 如果右侧可能是除法，防止除零
      if (choose(4) == 3) { // 25% 几率生成 '/'
        gen('/');
        int num = rand() % 99 + 1; // 1~99
        char tmp[16];
        sprintf(tmp, "%d", num);
        strcat(buf, tmp);
      } else {
        gen_rand_op();
        gen_rand_expr();
      }
      break;
  }

  depth--;
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
