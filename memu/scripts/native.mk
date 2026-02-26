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

-include $(MEMU_HOME)/../Makefile
include $(MEMU_HOME)/scripts/build.mk
include $(MEMU_HOME)/tools/difftest.mk

compile_git:
	$(call git_commit, "compile MEMU")
$(BINARY):: compile_git

# Some convenient rules

override ARGS ?= --log=$(BUILD_DIR)/memu-log.txt
override ARGS += $(ARGS_DIFF)

# Command to execute MEMU
IMG ?=
MEMU_EXEC := $(BINARY) $(ARGS)

run-env: $(BINARY) $(DIFF_REF_SO)

run: run-env
	$(call git_commit, "run NEMU batch mode")
	$(MEMU_EXEC) -b $(IMG)

run-sdb: run-env
	$(call git_commit, "run NEMU")
	$(MEMU_EXEC) $(IMG)

gdb: run-env
	$(call git_commit, "gdb MEMU")
	gdb -s $(BINARY) --args $(MEMU_EXEC) -b $(IMG)

clean-tools = $(dir $(shell find ./tools -maxdepth 2 -mindepth 2 -name "Makefile"))
$(clean-tools):
	-@$(MAKE) -s -C $@ clean
clean-tools: $(clean-tools)
clean-all: clean distclean clean-tools

.PHONY: run gdb run-env clean-tools clean-all $(clean-tools)
