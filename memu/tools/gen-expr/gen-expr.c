#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define TOKENNUM 256
#define MAXNUM 256
int len, tn;

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() {"
"  unsigned result = %s;"
"  printf(\"%%u\", result);"
"  return 0;"
"}";

// 随机选择 0~n-1
static int choose(int n) {
  return rand() % n;
}

static void gen_space() {
  int k = rand() % 3;   // 0~2 个空格
  while (k--) buf[len++] = ' ';
}

static void gen(char c) {
  if (rand() % 2) gen_space();  // 前空格
  buf[len++] = c;
  tn++;
  if (rand() % 2) gen_space();  // 后空格
}

// 生成一个随机数字
static void gen_num() {
  int x = choose(MAXNUM) + 1;  // 永远 >= 1
  len += sprintf(buf + len, "%d", x);
  tn++;
}

// 生成随机运算符 + - * /
static void gen_rand_op() {
  static char ops[] = "+-*/";
  buf[len++] = ops[choose(4)];
  tn++;
}

// 生成随机表达式
static void gen_rand_expr() {
  if(tn >= TOKENNUM) {gen_num(); return;}
  switch (choose(3)) {
    case 0: gen_num(); break;
    case 1: if(tn + 3 > TOKENNUM) {gen_num(); return;} gen('('); gen_rand_expr(); gen(')'); break;
    default: if(tn + 3 > TOKENNUM) {gen_num(); return;} gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break;
  }
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
    len = 0; tn = 0;

    gen_rand_expr();
    buf[len] = '\0';

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system(  
      // "-Werror": 把 warning 当 error, 阻止写入input
      // "2>/dev/null": 把 gcc 的 stderr 重定向到 /dev/null, 不打印任何东西
      "gcc -Werror /tmp/.code.c -o /tmp/.expr 2>/dev/null"
    );
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
    fflush(stdout);  // printf immediately
  }
  return 0;
}
