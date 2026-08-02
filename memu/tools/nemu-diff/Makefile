MEMU_HOME := $(abspath ../..)
GUEST_ISA ?= riscv32

NAME := $(GUEST_ISA)-nemu-so
BUILD_DIR := $(CURDIR)/build
OBJ_DIR := $(BUILD_DIR)/obj-$(GUEST_ISA)
BINARY := $(BUILD_DIR)/$(NAME)
CONFIG_HEADER := $(BUILD_DIR)/include/generated/autoconf.h

CONFIG_MBASE ?= 0x80000000
CONFIG_MSIZE ?= 0x08000000
CONFIG_PC_RESET_OFFSET ?= 0

SRCS := \
  csrc/cpu/cpu-exec.c \
  csrc/cpu/difftest/ref.c \
  csrc/engine/interpreter/hostcall.c \
  csrc/isa/$(GUEST_ISA)/init.c \
  csrc/isa/$(GUEST_ISA)/inst.c \
  csrc/isa/$(GUEST_ISA)/logo.c \
  csrc/isa/$(GUEST_ISA)/reg.c \
  csrc/isa/$(GUEST_ISA)/system/intr.c \
  csrc/isa/$(GUEST_ISA)/system/mmu.c \
  csrc/memory/paddr.c \
  csrc/memory/vaddr.c \
  csrc/utils/log.c \
  csrc/utils/state.c \
  csrc/utils/timer.c

OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)
CPPFLAGS := \
  -I$(BUILD_DIR)/include \
  -I$(MEMU_HOME)/include \
  -I$(MEMU_HOME)/csrc/isa/$(GUEST_ISA)/include \
  -I$(MEMU_HOME)/csrc/engine/interpreter \
  -D__GUEST_ISA__=$(GUEST_ISA)
CFLAGS := -O2 -MMD -MP -Wall -Werror -fPIC -fvisibility=hidden
LDFLAGS := -shared -fPIC

.PHONY: all clean FORCE
all: $(BINARY)

$(BINARY): $(OBJS)
	@mkdir -p $(dir $@)
	@echo + LD $@
	@$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(MEMU_HOME)/%.c $(CONFIG_HEADER)
	@mkdir -p $(dir $@)
	@echo + CC $<
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(CONFIG_HEADER): FORCE
	@mkdir -p $(dir $@)
	@{ \
	  echo '#ifndef __NEMU_DIFF_AUTOCONF_H__'; \
	  echo '#define __NEMU_DIFF_AUTOCONF_H__'; \
	  echo '#define CONFIG_NEMU 1'; \
	  echo '#define CONFIG_ISA_riscv 1'; \
	  echo '#define CONFIG_TARGET_SHARE 1'; \
	  echo '#define CONFIG_PMEM_MALLOC 1'; \
	  echo '#define CONFIG_RT_CHECK 1'; \
	  echo '#define CONFIG_MBASE $(CONFIG_MBASE)'; \
	  echo '#define CONFIG_MSIZE $(CONFIG_MSIZE)'; \
	  echo '#define CONFIG_PC_RESET_OFFSET $(CONFIG_PC_RESET_OFFSET)'; \
	  $(if $(filter y,$(CONFIG_RVE)),echo '#define CONFIG_RVE 1';,) \
	  echo '#endif'; \
	} > $@.tmp
	@cmp -s $@.tmp $@ || cp $@.tmp $@
	@rm -f $@.tmp

FORCE:

clean:
	@rm -rf $(BUILD_DIR)

-include $(OBJS:.o=.d)
