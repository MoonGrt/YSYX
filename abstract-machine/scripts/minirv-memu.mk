include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/memu.mk

export PATH := $(PATH):$(abspath $(AM_HOME)/tools/minirv)
CC = minirv-gcc
AS = minirv-gcc
CXX = minirv-g++

CFLAGS  += -DISA_H=\"riscv/riscv.h\"
COMMON_CFLAGS += -march=rv32i_zicsr -mabi=ilp32  # overwrite
LDFLAGS       += -melf32lriscv                   # overwrite

AM_SRCS += riscv/memu/start.S \
           riscv/memu/cte.c \
           riscv/memu/trap.S \
           riscv/memu/vme.c

AM_SRCS += riscv/memu/libgcc/div.S \
           riscv/memu/libgcc/muldi3.S \
           riscv/memu/libgcc/multi3.c \
           riscv/memu/libgcc/ashldi3.c \
           riscv/memu/libgcc/unused.c
