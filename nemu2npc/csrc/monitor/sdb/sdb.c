/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NPC is licensed under Mulan PSL v2.
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
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <utils.h>

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(npc) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_help(char *args);

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}

static int cmd_q(char *args) {
  nemu_state.state = NPC_QUIT;
  return -1;
}

static int cmd_r(char *args) {
  init_isa();
  nemu_state.state = NPC_STOP;
  return 0;
}

static int cmd_s(char *args) {
  int step = 1; // 默认 1 步

  if (args != NULL) {
    // 解析用户输入的步数
    char *endptr;
    long n = strtol(args, &endptr, 10);
    if (*endptr != '\0') {
      printf("  Invalid argument '%s'. Usage: s [N]\n", args);
      return 0;
    }
    step = (int)n;
  }

  cpu_exec(step);
  return 0;
}

static int cmd_info(char *args) {
  if (args == NULL) {
    printf("  Usage: info SUBCMD\n");
    return 0;
  }

  if (strcmp(args, "r") == 0) {
    // 打印寄存器状态
    isa_reg_display();
  } 
  else if (strcmp(args, "w") == 0) {
    // 打印监视点信息
    print_wp();
  } 
  else {
    printf("  Unknown subcommand '%s' for info\n", args);
  }
  return 0;
}

// #define TESTCWD
#ifdef TESTCWD
#include <unistd.h>
#endif
static int cmd_test(char *args) {
  if (args == NULL) {
    printf("  Usage: test filename\n");
    return 0;
  }

#ifdef TESTCWD
  char cwd[256];
  char *ret = getcwd(cwd, sizeof(cwd));
  assert(ret != NULL);
  printf("  CWD: %s\n", cwd);
#endif

  FILE *fp = fopen(args, "r");
  if (fp == NULL) {
    perror("  fopen");
    return 0;
  }

  char line[1024];
  int line_no = 0;

  while (fgets(line, sizeof(line), fp)) {
    line_no++;

    // 1. 去掉行尾 '\n'
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }

    // 2. 读取期望结果
    uint32_t golden;
    int offset = 0;
    if (sscanf(line, "%u%n", &golden, &offset) != 1) {
      printf("  X Line %d: invalid format\n", line_no);
      continue;
    }

    // 3. offset 之后就是完整表达式（允许任意空格）
    char *expr_str = line + offset;

    bool success = true;
    uint32_t result = expr(expr_str, &success);

    if (!success) {
      printf("  X Line %d: expr eval failed\n", line_no);
      printf("    expr: %s\n", expr_str);
      assert(0);
    }

    if (result != golden) {
      printf("  X Line %d: mismatch\n", line_no);
      printf("    expr   : %s", expr_str);
      printf("    npc   : %u\n", result);
      printf("    golden : %u\n", golden);
      assert(0);
    }

    printf("  O Line %d: %u = %s \n", line_no, result, expr_str);
  }

  fclose(fp);
  printf("  O All tests passed!\n");
  return 0;
}

static int pcnt;
static int cmd_p(char *args) {
  if (args == NULL) {
    printf("  Usage: p EXPR\n");
    return 0;
  }

  bool success = true;
  word_t result = expr(args, &success);
  if (success) {
    pcnt++;
    printf("  $%d = %u\n", pcnt, result);
  } else {
    printf("  Invalid expression: %s\n", args);
  }

  return 0;
}

static int cmd_w(char *args) {
  if (args == NULL) {
    printf("  Usage: w EXPR\n");
    return 0;
  }
  int wp_no = new_wp(args);
  if (wp_no < 0) {
    printf("  Failed to set watchpoint\n");
  }
  return 0;
}

static int cmd_d(char *args) {
  if (args == NULL) {
    printf("  Usage: d N\n");
    return 0;
  }

  char *endptr;
  long n = strtol(args, &endptr, 10);
  if (*endptr != '\0' || n < 0 || n >= NR_WP) {
      printf("  Invalid watchpoint number: %s\n", args);
      return 0;
  }

  if (free_wp((int)n) == 0) {
    printf("  Watchpoint %d deleted\n", (int)n);
  } else {
    printf("  No watchpoint %d\n", (int)n);
  }

  return 0;
}

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "info", "Print program status: info r (registers), info w (watchpoints)", cmd_info },
  { "help", "Display information about all supported commands", cmd_help },
  { "test", "Test expression from file", cmd_test },
  { "r", "Reset the processor", cmd_r },
  { "c", "Continue the execution of the program", cmd_c },
  { "s", "Step execution", cmd_s },
  { "p", "Evaluate expression EXPR", cmd_p },
  { "w", "Set watchpoint on EXPR", cmd_w },
  { "d", "Delete watchpoint N", cmd_d },
  { "q", "Exit NPC", cmd_q },
};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("  %s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("  %s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("  Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("  Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  pcnt = 0;  // init expr cnt
  init_regex();
  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
