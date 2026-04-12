include $(AM_HOME)/scripts/isa/mips32.mk
include $(AM_HOME)/scripts/platform/memu.mk
CFLAGS  += -DISA_H=\"mips/mips32.h\"

AM_SRCS += mips/memu/start.S \
           mips/memu/cte.c \
           mips/memu/trap.S \
           mips/memu/vme.c
