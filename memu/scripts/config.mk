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

COLOR_RED := $(shell echo "\033[1;31m")
COLOR_END := $(shell echo "\033[0m")

ifeq ($(wildcard .config),)
$(warning $(COLOR_RED)Warning: .config does not exist!$(COLOR_END))
$(warning $(COLOR_RED)To build the project, first run 'make menuconfig'.$(COLOR_END))
endif

Q            := @
KCONFIG_PATH := $(MEMU_HOME)/tools/kconfig
FIXDEP_PATH  := $(MEMU_HOME)/tools/fixdep
Kconfig      := $(MEMU_HOME)/Kconfig
rm-distclean += include/generated include/config .config .config.old
silent       := -s

CONF   := $(KCONFIG_PATH)/build/conf
MCONF  := $(KCONFIG_PATH)/build/mconf
FIXDEP := $(FIXDEP_PATH)/build/fixdep

$(CONF):
	$(Q)$(MAKE) $(silent) -C $(KCONFIG_PATH) NAME=conf

$(MCONF):
	$(Q)$(MAKE) $(silent) -C $(KCONFIG_PATH) NAME=mconf

$(FIXDEP):
	$(Q)$(MAKE) $(silent) -C $(FIXDEP_PATH)

menuconfig: $(MCONF) $(CONF) $(FIXDEP)
	$(Q)$(MCONF) $(Kconfig)
	$(Q)$(CONF) $(silent) --syncconfig $(Kconfig)

savedefconfig: $(CONF)
	$(Q)$< $(silent) --$@=configs/defconfig $(Kconfig)

%defconfig: $(CONF) $(FIXDEP)
	$(Q)$< $(silent) --defconfig=configs/$@ $(Kconfig)
	$(Q)$< $(silent) --syncconfig $(Kconfig)

.PHONY: menuconfig savedefconfig defconfig

# Help text used by make help
help:
	@echo 'Usage: make [target]'
	@echo ''
	@echo 'Config targets:'
	@echo '  menuconfig      - Configure MEMU via menu-based interface'
	@echo '  savedefconfig   - Save current config as configs/defconfig (minimal config)'
	@echo '  defconfig       - Load default configuration'
	@echo '  <xxx>defconfig  - Load configs/xxx defconfig'
	@echo ''
	@echo 'Build targets:'
	@echo '  app             - Build MEMU binary (default target)'
	@echo '  compile         - Compile MEMU (alias of app)'
	@echo '  rtl             - Generate Verilog from Chisel'
	@echo '  verilate        - Verilate RTL and build simulation library'
	@echo ''
	@echo 'Run targets:'
	@echo '  run             - Run MEMU in batch mode'
	@echo '  run-sdb         - Run MEMU with interactive debugger'
	@echo '  gdb             - Run MEMU under gdb'
	@echo ''
	@echo 'Waveform targets:'
	@echo '  wave            - Open waveform (gtkwave)'
	@echo ''
	@echo 'Clean targets:'
	@echo '  clean           - Remove build directory'
	@echo '  clean-tools     - Clean all tool sub-projects'
	@echo '  clean-all       - Clean everything (build + tools)'
	@echo '  distclean       - Remove build files and configuration'
	@echo ''
	@echo 'Variables (override by command line):'
	@echo '  IMG=<file>      - Image to run'
	@echo '  ARGS=<args>     - Arguments passed to MEMU'
	@echo '  SHARE=1         - Build shared library (.so)'

distclean: clean
	-@rm -rf $(rm-distclean)

.PHONY: help distclean

define call_fixdep
	@$(FIXDEP) $(1) $(2) unused > $(1).tmp
	@mv $(1).tmp $(1)
endef
