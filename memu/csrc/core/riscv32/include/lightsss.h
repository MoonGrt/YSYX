#ifndef __LIGHTSSS_H
#define __LIGHTSSS_H

#include <deque>
#include <list>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/prctl.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <debug.h>
#include <atomic>
#include <linux/futex.h>
#include <sys/syscall.h>

#include <cstdio>
#include <cstdint>
#include <cstdarg>
#include <cstdlib>
#include <climits>

#ifdef CONFIG_WAVE_RELATIVE

#define FAIT_EXIT exit(EXIT_FAILURE);

typedef struct shinfo {
  int flag;
  int notgood;
  uint64_t endCycles;
  pid_t oldest;
} shinfo;

class ForkShareMemory {
private:
  key_t key_n;
  int shm_id;

public:
  shinfo *info;

  ForkShareMemory();
  ~ForkShareMemory();

  void shwait();
};

const int FORK_OK = 0;
const int FORK_ERROR = 1;
const int FORK_CHILD = 2;

class LightSSS {
  pid_t pid = -1;
	static pid_t p_pid;
  int slotCnt = 0;
  int waitProcess = 0;
  // front() is the newest. back() is the oldest.
  static std::deque<pid_t> pidSlot;
  static ForkShareMemory forkshm;

public:
  int do_fork();
  int wakeup_child(uint64_t cycles);
  bool is_child();
  int do_clear();
  uint64_t get_end_cycles() {
    return forkshm.info->endCycles;
  }
};

#define FORK_PRINTF(format, args...)                       \
  do {                                                     \
    printf("[FORK_INFO pid(%d)] " format, getpid(), ##args); \
    fflush(stdout);                                        \
  } while (0);

#endif

#endif
