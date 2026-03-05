#include <amtest.h>

void hello() {
  for (int i = 0; i < 2; i ++) {
    putstr("Hello, AM World @"__ISA__ "\n");
  }
}
