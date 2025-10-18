/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
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

#include "sdb.h"

WP wp_pool[NR_WP] = {};
WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

int new_wp(char *e) {
  if (free_ == NULL) {
    printf("No free watchpoints!\n");
    assert(0);  // 没有空闲监视点时直接终止程序
  }

  WP *wp = free_;
  free_ = free_->next;

  wp->next = head;
  head = wp;

  // 保存表达式字符串
  snprintf(wp->expr_str, sizeof(wp->expr_str), "%s", e);

  // 初始化 last_val
  bool success = true;
  wp->last_val = expr((char*)e, &success);
  if (!success) wp->last_val = 0;

  printf("Watchpoint %d set on '%s', initial value = 0x%x\n",
         wp->NO, wp->expr_str, wp->last_val);

  return 0;
}

int free_wp(int no) {
  WP **cur = &head;
  while (*cur != NULL) {
    if ((*cur)->NO == no) {
      WP *tmp = *cur;
      *cur = tmp->next;  // 从链表中移除
      tmp->next = free_; // 放回空闲链表
      free_ = tmp;
      return 0;
    }
    cur = &((*cur)->next);
  }
  return -1;
}

void print_wp() {
  if (head == NULL) {
    printf("No watchpoints.\n");
    return;
  }

  printf("Num\tExpression\tLast Value\n");
  WP *wp = head;
  while (wp) {
    printf("%d\t%s\t\t0x%x\n", wp->NO, wp->expr_str, wp->last_val);
    wp = wp->next;
  }
}

bool check_wp() {
  bool triggered = false;
  WP *wp = head;
  while (wp) {
    bool success;
    word_t val = expr(wp->expr_str, &success);
    if (!success) { wp = wp->next; continue; }

    if (val != wp->last_val) {
      printf("Watchpoint %d triggered: %s\n", wp->NO, wp->expr_str);
      printf("Old value = 0x%x, New value = 0x%x\n", wp->last_val, val);
      wp->last_val = val;
      triggered = true;
    }
    wp = wp->next;
  }
  return triggered;
}
