#include <lightsss.h>

#ifdef CONFIG_WAVE_RELATIVE

pid_t LightSSS::p_pid = -1;
std::deque<pid_t> LightSSS::pidSlot = {};
ForkShareMemory LightSSS::forkshm;

static int futex_wait(int *addr, int val) {
  return syscall(SYS_futex, addr, FUTEX_WAIT, val, nullptr, nullptr, 0);
}

static int futex_wake(int *addr) {
  return syscall(SYS_futex, addr, FUTEX_WAKE, INT_MAX, nullptr, nullptr, 0);
}

ForkShareMemory::ForkShareMemory() {
  if ((key_n = ftok(".", 's') < 0)) {
    perror("ftok failed...\n");
    FAIT_EXIT
  }
  if ((shm_id = shmget(key_n, 1024, 0666 | IPC_CREAT)) == -1) {
    perror("shmget failed...\n");
    FAIT_EXIT
  }
  void *ret = shmat(shm_id, NULL, 0);
  if (ret == (void *)-1) {
    perror("shmat failed...\n");
    FAIT_EXIT
  } else info = (shinfo *)ret;
  info->flag = 0;
  info->notgood = 0;
  info->endCycles = 0;
  info->oldest = 0;
}

ForkShareMemory::~ForkShareMemory() {
  if (shmdt(info) == -1)
    perror("detach error\n");
  shmctl(shm_id, IPC_RMID, NULL);
}

void ForkShareMemory::shwait() {
  while (true) {
    if (__atomic_load_n(&info->flag, __ATOMIC_ACQUIRE) != 0)
      break;
    futex_wait(&info->flag, 0);
  }
  if (info->notgood == 0) {
    _exit(0);
  }
}

int LightSSS::do_fork() {
  //kill the oldest blocked checkpoint process
  if (slotCnt == CONFIG_WAVE_REL_SLOTNUM) {
    pid_t temp = pidSlot.back();
    pidSlot.pop_back();
    kill(temp, SIGKILL);
    int status = 0;
    waitpid(temp, NULL, 0);
    slotCnt--;
  }
  // fork a new checkpoint process and block it
  if ((pid = fork()) < 0) {
    FORK_PRINTF("[%d]Error: could not fork process!\n", getpid());
    return FORK_ERROR;
  }
  // the original process
  else if (pid != 0) {
    slotCnt++;
    pidSlot.push_front(pid);
    return FORK_OK;
  }
  // for the fork child
  waitProcess = 1;
  forkshm.shwait();
  //checkpoint process wakes up
  //start wave dumping
  if (forkshm.info->oldest != getpid()) {
    FORK_PRINTF("Error, non-oldest process should not live. Parent Process should kill the process manually.\n")
    return FORK_ERROR;
  }
  return FORK_CHILD;
}

int LightSSS::wakeup_child(uint64_t cycles) {
  forkshm.info->endCycles = cycles;
  forkshm.info->oldest = pidSlot.back();
  pid_t keep = forkshm.info->oldest;
  // kill all non-oldest
  for (auto pid : pidSlot) {
    if (pid != keep) {
      kill(pid, SIGKILL);
      waitpid(pid, NULL, 0);
    }
  }
  fflush(stdout);
  fflush(stderr);

  // set control state
  forkshm.info->notgood = 1;
  // release all waiting children
  __atomic_store_n(&forkshm.info->flag, 1, __ATOMIC_RELEASE);
  futex_wake(&forkshm.info->flag);
  int status = 0;
  waitpid(keep, &status, 0);
  return 0;
}

bool LightSSS::is_child() {
  return waitProcess;
}

int LightSSS::do_clear() {
  FORK_PRINTF("clear processes...\n")
  while (!pidSlot.empty()) {
    pid_t temp = pidSlot.back();
    pidSlot.pop_back();
    kill(temp, SIGKILL);
    waitpid(temp, NULL, 0);
    slotCnt--;
  }
  if(getpid() != p_pid) {
    kill(getpid(), SIGKILL);
    waitpid(getpid(), NULL, 0);
  }
  return 0;
}

#endif
