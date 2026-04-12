include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/memu.mk
CFLAGS  += -DISA_H=\"riscv/riscv.h\"

AM_SRCS += riscv/memu/start.S \
           riscv/memu/cte.c \
           riscv/memu/trap.S \
           riscv/memu/vme.c
