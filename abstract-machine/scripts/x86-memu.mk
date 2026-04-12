include $(AM_HOME)/scripts/isa/x86.mk
include $(AM_HOME)/scripts/platform/memu.mk
CFLAGS  += -mstringop-strategy=loop -DISA_H=\"x86/x86.h\"
# overwrite _pmem_start and _entry_offset defined in memu.mk
LDFLAGS += --defsym=_pmem_start=0x0 --defsym=_entry_offset=0x100000

AM_SRCS += x86/memu/start.S \
           x86/memu/cte.c \
           x86/memu/trap.S \
           x86/memu/vme.c
