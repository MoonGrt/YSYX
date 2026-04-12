#include <am.h>
#include <klib.h>
#include <rtthread.h>

/* =======================
 * 线程上下文切换参数
 * ======================= */
typedef struct {
  rt_ubase_t to;
  rt_ubase_t from;
} ctx_switch_ud_t;

/* =======================
 * 线程入口参数
 * ======================= */
typedef struct {
  void (*tentry)(void*);
  void* parameter;
  void (*texit)(void);
} thread_args_t;

/* =======================
 * 线程启动包装
 * ======================= */
static void context_wrapper(thread_args_t* args) {
  args->tentry(args->parameter);
  args->texit();
  while (1);  // 不应返回
}

/* =======================
 * AM 事件处理
 * ======================= */
static Context* ev_handler(Event e, Context* c) {
  switch (e.event) {
    case EVENT_YIELD: {
      rt_thread_t current = rt_thread_self();
      ctx_switch_ud_t *ud = (ctx_switch_ud_t *)current->user_data;
      if (ud->from) *((Context**)ud->from) = c;
      c = *(Context**)ud->to;
      break;
    }
    case EVENT_IRQ_TIMER:
      return c;
    case EVENT_IRQ_IODEV:
      return c;
    default:
      printf("Unhandled event ID = %d\n", e.event);
      assert(0);
  }
  return c;
}

/* =======================
 * CTE 初始化
 * ======================= */
void __am_cte_init() {
  cte_init(ev_handler);
}

/* =======================
 * 切换到新线程（无 from）
 * ======================= */
void rt_hw_context_switch_to(rt_ubase_t to) {
  rt_thread_t current = rt_thread_self();
  ctx_switch_ud_t ud;
  ud.to   = to;
  ud.from = 0;
  rt_ubase_t old_ud = current->user_data;
  current->user_data = (rt_ubase_t)&ud;
  yield();
  current->user_data = old_ud;
}

/* =======================
 * 线程间上下文切换
 * ======================= */
void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to) {
  rt_thread_t current = rt_thread_self();
  ctx_switch_ud_t ud;
  ud.to   = to;
  ud.from = from;
  rt_ubase_t old_ud = current->user_data;
  current->user_data = (rt_ubase_t)&ud;
  yield();
  current->user_data = old_ud;
}

/* =======================
 * 中断上下文切换（未实现）
 * ======================= */
void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread) {
  assert(0);
}

/* =======================
 * 线程栈初始化
 * ======================= */
rt_uint8_t* rt_hw_stack_init(void* tentry, void* parameter, rt_uint8_t* stack_addr, void* texit) {
  stack_addr = (rt_uint8_t*)(((uintptr_t)stack_addr + sizeof(uintptr_t) - 1) & ~(sizeof(uintptr_t) - 1));
  stack_addr -= sizeof(thread_args_t); // 在栈上分配参数结构体空间
  thread_args_t* args = (thread_args_t*)stack_addr; // 转型
  // 设置参数
  args->tentry = (void (*)(void*))tentry;
  args->parameter = parameter;
  args->texit = (void (*)(void))texit;
  Area stack_area = {.end = (rt_uint8_t*)stack_addr};  // 设置栈区域
  rt_uint8_t* c = (rt_uint8_t*)kcontext(stack_area, (void*)context_wrapper, args);
  return c;
}
