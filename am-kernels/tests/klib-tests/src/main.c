#include <klib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#define N 32

uint8_t data[N];
uint8_t src[N];

/* =========================
 * 公共辅助函数
 * ========================= */

void reset() {
  for (int i = 0; i < N; i++) {
    data[i] = i + 1;
  }
}

void reset_src() {
  for (int i = 0; i < N; i++) {
    src[i] = 100 + i;
  }
}

// 检查 [l, r) 是否为 val, val+1, ...
void check_seq(int l, int r, int val) {
  for (int i = l; i < r; i++) {
    assert(data[i] == val + i - l);
  }
}

// 检查 [l, r) 是否全为 val
void check_eq(int l, int r, int val) {
  for (int i = l; i < r; i++) {
    assert(data[i] == val);
  }
}

/* =========================
 * 第一类：写内存 / 字符串
 * ========================= */

void test_memset() {
  for (int l = 0; l < N; l++) {
    for (int r = l + 1; r <= N; r++) {
      reset();
      uint8_t val = (l + r) / 2;

      memset(data + l, val, r - l);

      check_seq(0, l, 1);
      check_eq(l, r, val);
      check_seq(r, N, r + 1);
    }
  }
}

void test_memcpy() {
  for (int l = 0; l < N; l++) {
    for (int r = l + 1; r <= N; r++) {
      reset();
      reset_src();

      memcpy(data + l, src, r - l);

      check_seq(0, l, 1);
      for (int i = l; i < r; i++) {
        assert(data[i] == src[i - l]);
      }
      check_seq(r, N, r + 1);
    }
  }
}

void test_strcpy() {
  char buf[32];
  const char *s = "hello";

  memset(buf, 'x', sizeof(buf));
  strcpy(buf, s);

  assert(strcmp(buf, "hello") == 0);
  assert(buf[5] == '\0');
  assert(buf[6] == 'x'); // 检查是否越界
}

void test_strncpy() {
  char buf[16];

  memset(buf, 'x', sizeof(buf));
  strncpy(buf, "hi", 5);

  assert(buf[0] == 'h');
  assert(buf[1] == 'i');
  assert(buf[2] == '\0');
}

/* =========================
 * 第二类：只读函数
 * ========================= */

void test_strlen() {
  assert(strlen("") == 0);
  assert(strlen("a") == 1);
  assert(strlen("abc") == 3);

  char buf[8] = {'a', 'b', 'c', '\0', 'x'};
  assert(strlen(buf) == 3);
}

void test_memcmp() {
  uint8_t a[] = {1, 2, 3};
  uint8_t b[] = {1, 2, 3};
  uint8_t c[] = {1, 2, 4};

  assert(memcmp(a, b, 3) == 0);
  assert(memcmp(a, c, 3) < 0);
  assert(memcmp(c, a, 3) > 0);
}

void test_strcmp() {
  assert(strcmp("abc", "abc") == 0);
  assert(strcmp("abc", "abd") < 0);
  assert(strcmp("abd", "abc") > 0);
}

/* =========================
 * 第三类：格式化输出
 * ========================= */

void test_sprintf_d() {
    int nums[] = {0, INT_MAX/17, INT_MAX, INT_MIN, INT_MIN + 1};
    char buf[64], ref[64];

    for (int i = 0; i < sizeof(nums)/sizeof(nums[0]); i++) {
        memset(buf, 0, sizeof(buf));
        memset(ref, 0, sizeof(ref));
        sprintf(buf, "%d", nums[i]);
        snprintf(ref, sizeof(ref), "%d", nums[i]);
        assert(strcmp(buf, ref) == 0);
    }
}

void test_sprintf_u() {
    unsigned int nums[] = {0, UINT_MAX/17, UINT_MAX};
    char buf[64], ref[64];

    for (int i = 0; i < sizeof(nums)/sizeof(nums[0]); i++) {
        memset(buf, 0, sizeof(buf));
        memset(ref, 0, sizeof(ref));
        sprintf(buf, "%u", nums[i]);
        snprintf(ref, sizeof(ref), "%u", nums[i]);
        assert(strcmp(buf, ref) == 0);
    }
}

/* =========================
 * main
 * ========================= */

int main() {
  test_memset();
  test_memcpy();
  test_strcpy();
  test_strncpy();

  test_strlen();
  test_memcmp();
  test_strcmp();

  test_sprintf_d();
  test_sprintf_u();

  printf("All klib tests passed!\n");
  return 0;
}
