#include <am.h>
#include <klib.h>
#include <klib-macros.h>

bool vme_init(void *(*pgalloc)(int), void (*pgfree)(void *)) {
  return false;
}

void protect(AddrSpace *as) {
  as->ptr = NULL;
}

void unprotect(AddrSpace *as) {
}

void map(AddrSpace *as, void *va, void *pa, int prot) {
  panic("SoC VME is not implemented");
}

Context *ucontext(AddrSpace *as, Area kstack, void *entry) {
  return NULL;
}

void __am_get_cur_as(Context *c) {
  c->pdir = NULL;
}

void __am_switch(Context *c) {
}
