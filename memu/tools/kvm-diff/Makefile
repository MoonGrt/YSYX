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

NAME  = x86-kvm
SRCS  = $(shell find src/ -name "*.c")

SHARE = 1
INC_PATH += $(MEMU_HOME)/include $(MEMU_HOME)/src/isa/x86/include
GUEST_ISA = x86

include $(MEMU_HOME)/scripts/build.mk
