/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* MEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <common.h>
#if defined(CONFIG_NEMU)

#elif defined(CONFIG_NPC)
#include "../../core/riscv32/local-include/exec.h"
#endif

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

// #define PRINTARG
int main(int argc, char *argv[]) {
#ifdef PRINTARG
    printf("[MEMU] ARGC = %d\n", argc);
    for (int i = 0; i < argc; i++)
      printf("[MEMU] ARGV[%d] = '%s'\n", i, argv[i]);
#endif
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif
  /* Initialize the RISC-V execution engine. */
#if defined(CONFIG_NEMU)

#elif defined(CONFIG_NPC)
  rtl_init(argc, argv);
#endif
  /* Start engine. */
  engine_start();
  return is_exit_status_bad();
}
