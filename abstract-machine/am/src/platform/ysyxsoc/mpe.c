#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdatomic.h>

bool mpe_init(void (*entry)(void)) {
  entry();
  panic("MPE entry returns");
}

int cpu_count(void) {
  return 1;
}

int cpu_current(void) {
  return 0;
}

int atomic_xchg(int *addr, int newval) {
  return atomic_exchange(addr, newval);
}
