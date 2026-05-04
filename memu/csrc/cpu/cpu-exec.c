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

#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <locale.h>
#include "../monitor/sdb/sdb.h"

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INST_TO_PRINT 10

CPU_state cpu = {};
Decode decode = {};
uint64_t g_nr_guest_inst = 0;
static uint64_t g_timer = 0; // unit: us
static bool g_print_step = false;

void device_update();

static void trace_and_difftest(Decode *_this, vaddr_t dnpc) {
#ifdef CONFIG_ITRACE_COND
  if (_this->logbuf[0] == '\0') return;
  log_write("%s\n", _this->logbuf);
#endif
  if (g_print_step) { IFDEF(CONFIG_ITRACE, puts(_this->logbuf)); }
#ifdef CONFIG_NEMU
  IFDEF(CONFIG_DIFFTEST, difftest_step());
#endif
#ifdef CONFIG_WATCHPOINT
  // 扫描所有监视点
  WP *wp = head;
  while (wp) {
    bool success = true;
    word_t val = expr(wp->expr_str, &success);
    if (!success) {
      printf("  Failed to evaluate watchpoint %d: %s\n", wp->NO, wp->expr_str);
      wp = wp->next;
      continue;
    }
    if (val != wp->last_val) {
      printf("  Watchpoint %d triggered: %s\n", wp->NO, wp->expr_str);
      printf("  Old value = 0x%x, New value = 0x%x\n", wp->last_val, val);
      wp->last_val = val;
      memu_state.state = MEMU_STOP;
      return;
    }
    wp = wp->next;
  }
#endif
}

static void exec_once(vaddr_t pc) {
  decode.pc = pc;
  decode.snpc = pc;
  isa_exec_once(decode);
#ifdef CONFIG_ITRACE
  if (decode.isa.inst == 0 || (decode.snpc == decode.pc)) {
    strcpy(decode.logbuf, "");
    return;
  }
  void trace_inst(word_t pc, uint32_t inst);
  IFDEF(CONFIG_ITRACE, trace_inst(decode.pc, decode.isa.inst));
  char *p = decode.logbuf;
  p += snprintf(p, sizeof(decode.logbuf), "[I] " FMT_WORD ": ", decode.pc);
  int ilen = decode.snpc - decode.pc;
  int i;
  uint8_t *inst = (uint8_t *)&decode.isa.inst;
#ifdef CONFIG_ISA_x86
  for (i = 0; i < ilen; i ++)
#else
  for (i = ilen - 1; i >= 0; i --)
#endif
    p += snprintf(p, 4, "%02x", inst[i]);
  int ilen_max = MUXDEF(CONFIG_ISA_x86, 8, 4);
  int space_len = ilen_max - ilen;
  if (space_len < 0) space_len = 0;
  space_len = space_len * 3 + 1;
  memset(p, ' ', space_len);
  p += space_len;
  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
  disassemble(p, decode.logbuf + sizeof(decode.logbuf) - p,
    MUXDEF(CONFIG_ISA_x86, decode.snpc, decode.pc), (uint8_t *)&decode.isa.inst, ilen);
#endif
}

static void execute(uint64_t n) {
  for (;n > 0; n--) {
    exec_once(cpu.pc);
    g_nr_guest_inst ++;
    trace_and_difftest(&decode, cpu.pc);
    if (memu_state.state != MEMU_RUNNING) break;
    IFDEF(CONFIG_DEVICE, if (g_nr_guest_inst % 10) device_update());
  }
}

static void statistic() {
  IFNDEF(CONFIG_TARGET_AM, setlocale(LC_NUMERIC, ""));
#define NUMBERIC_FMT MUXDEF(CONFIG_TARGET_AM, "%", "%'") PRIu64
  Log("host time spent = " NUMBERIC_FMT " us", g_timer);
  Log("total guest instructions = " NUMBERIC_FMT, g_nr_guest_inst);
  if (g_timer > 0) Log("simulation frequency = " NUMBERIC_FMT " inst/s", g_nr_guest_inst * 1000000 / g_timer);
  else Log("Finish running in less than 1 us and can not calculate the simulation frequency");
}

void display_inst(void);
void assert_fail_msg() {
  IFDEF(CONFIG_ITRACE, display_inst());
  isa_reg_display();
  statistic();
}

/* Simulate how the CPU works. */
void rtl_exit(void);
void cpu_exec(uint64_t n) {
  g_print_step = (n < MAX_INST_TO_PRINT);
  switch (memu_state.state) {
    case MEMU_END: case MEMU_ABORT: case MEMU_QUIT:
      printf("Program execution has ended. To restart the program, exit MEMU and run again.\n");
      return;
    default: memu_state.state = MEMU_RUNNING;
  }

  uint64_t timer_start = get_time();
  execute(n);
  uint64_t timer_end = get_time();
  g_timer += timer_end - timer_start;
  switch (memu_state.state) {
    case MEMU_RUNNING: memu_state.state = MEMU_STOP; break;
    case MEMU_END: case MEMU_ABORT:
      Log("memu: %s at pc = " FMT_WORD,
          (memu_state.state == MEMU_ABORT ? ANSI_FMT("ABORT", ANSI_FG_RED) :
          (memu_state.halt_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) : ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
          memu_state.halt_pc);
      // fall through
    case MEMU_QUIT: statistic();
  }
  #if defined(CONFIG_NPC)
    rtl_exit();
  #endif
}
