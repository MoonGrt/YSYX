#***************************************************************************************
# Copyright (c) 2014-2024 Zihao Yu, Nanjing University
#
# MEMU is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
#
# See the Mulan PSL v2 for more details.
#**************************************************************************************/

ifdef CONFIG_DIFFTEST
DIFF_REF_PATH = $(MEMU_HOME)/$(call remove_quote,$(CONFIG_DIFFTEST_REF_PATH))
DIFF_REF_SO = $(DIFF_REF_PATH)/build/$(GUEST_ISA)-$(call remove_quote,$(CONFIG_DIFFTEST_REF_NAME))-so
MKFLAGS = GUEST_ISA=$(GUEST_ISA) SHARE=1 ENGINE=interpreter
ARGS_DIFF = --diff=$(DIFF_REF_SO)

ifdef CONFIG_SOC
# Give the reference model one sparse-on-demand host mapping from SRAM through
# SDRAM. This also covers the MMIO, flash and PSRAM regions between them; only
# pages actually touched by the test consume physical host memory.
DIFF_MBASE = $(CONFIG_SOC_SRAM_BASE)
DIFF_MSIZE = $(shell printf '0x%x' $$(( $(CONFIG_SOC_SDRAM_BASE) + \
  $(CONFIG_SOC_SDRAM_SIZE) - $(CONFIG_SOC_SRAM_BASE) )))
ifeq ($(CONFIG_SOC_BOOT_MROM),y)
DIFF_RESET_OFFSET = 0x11000000
else
DIFF_RESET_OFFSET = 0x21000000
endif
else
DIFF_MBASE = $(CONFIG_MBASE)
DIFF_MSIZE = $(CONFIG_MSIZE)
DIFF_RESET_OFFSET = $(CONFIG_PC_RESET_OFFSET)
endif

$(DIFF_REF_SO):
	$(MAKE) -s -C $(DIFF_REF_PATH) $(MKFLAGS) \
		CONFIG_RVE=$(CONFIG_RVE) CONFIG_SOC=$(CONFIG_SOC) \
		CONFIG_MBASE=$(DIFF_MBASE) CONFIG_MSIZE=$(DIFF_MSIZE) \
		CONFIG_PC_RESET_OFFSET=$(DIFF_RESET_OFFSET)

.PHONY: $(DIFF_REF_SO)
endif
