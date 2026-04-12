include $(AM_HOME)/scripts/isa/loongarch32r.mk
include $(AM_HOME)/scripts/platform/memu.mk
CFLAGS  += -DISA_H=\"loongarch/loongarch32r.h\"

AM_SRCS += loongarch/memu/start.S \
           loongarch/memu/cte.c \
           loongarch/memu/trap.S \
           loongarch/memu/vme.c
