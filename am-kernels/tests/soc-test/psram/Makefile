NAME = psram
SRCS = psram.c
export ARCH ?= riscv32e-soc
export NO_DIFF := 1

ifneq ($(TEST_SIZE),)
CFLAGS += -DTEST_SIZE=$(TEST_SIZE)
endif

include $(AM_HOME)/Makefile

full:
	$(MAKE) clean
	$(MAKE) SOC_LOAD=sram TEST_SIZE=0x400000 run

.PHONY: full
