#define LOG
// #define DEBUG
// #define IMG_HEX

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <am.h>
#include <klib-macros.h>


#ifdef LOG
#include <assert.h>

#define ANSI_FG_RED     "\33[1;31m"
#define ANSI_FG_GREEN   "\33[1;32m"
#define ANSI_FG_BLUE    "\33[1;34m"
#define ANSI_NONE       "\33[0m"
#define ANSI_FMT(str, fmt) fmt str ANSI_NONE

FILE *log_fp = NULL;
#define log_write(...) { \
  if (log_fp != NULL) { \
    fprintf(log_fp, __VA_ARGS__); \
    fflush(log_fp); \
  } \
}
#define SHORT_FILE(file) ((strncmp(file, "../../", 6) == 0) ? ((file)+6) : (file))
#define Log(fmt, ...) do { \
  printf(ANSI_FMT("[%s:%d %s] " fmt, ANSI_FG_BLUE) "\n", \
    SHORT_FILE(__FILE__), __LINE__, __func__, ##__VA_ARGS__); \
  log_write(ANSI_FMT("[%s:%d %s] " fmt, ANSI_FG_BLUE) "\n", \
    SHORT_FILE(__FILE__), __LINE__, __func__, ##__VA_ARGS__); \
} while (0)
void init_log(char *log_file) {
  log_fp = stdout;
  if (log_file != NULL) {
    FILE *fp = fopen(log_file, "w");
    assert(fp);
    log_fp = fp;
  }
  Log("Log is written to %s", log_file ? log_file : "stdout");
}
#endif


#ifdef IMG_HEX
#define M_BASE 0x00000000L
#else
#define M_BASE 0x80000000L
#endif
#define M_SIZE 0x01000000L
static uint32_t PC = M_BASE;
static uint32_t M[M_SIZE];
static uint32_t pixels[256][256];
#ifdef DEBUG
static uint32_t R[16], R_prev[16];  // x0..x31 (x0 hardwired to 0)
#else
static uint32_t R[16];  // x0..x31 (x0 hardwired to 0)
#endif

// ---- helpers ----
static inline uint32_t reg_read(uint32_t r) { return r ? R[r] : 0; }
static inline void     reg_write(uint32_t r, uint32_t v) { if (r) R[r] = v; }
static inline int32_t  sext(uint32_t v, int b) { return (int32_t)(v << (32-b)) >> (32-b); }
static inline uint32_t guest_to_host(uint32_t addr) {
  if (addr < M_BASE || addr >= M_BASE + M_SIZE) {
    printf("Memory access out of range: addr = 0x%08x\n", addr);
    exit(1);
  }
  return addr - M_BASE;
}



// ---- one cycle ----
static uint32_t stepcnt;
static void step(void) {
  uint32_t ins = M[guest_to_host(PC) >> 2];

  if (ins == 0x00100073) {  // EBREAK
    Log("%s", ANSI_FMT("EBREAK: HIT GOOD TRAP", ANSI_FG_GREEN));
    exit(0);
  }

  uint32_t opcode = ins & 0x7f;
  uint32_t rd  = (ins >> 7)  & 0x1f;
  uint32_t rs1 = (ins >> 15) & 0x1f;
  uint32_t rs2 = (ins >> 20) & 0x1f;
  uint32_t funct3 = (ins >> 12) & 7;

  uint32_t pc_next = PC + 4;
  uint32_t a = reg_read(rs1);
  uint32_t b = reg_read(rs2);

#ifdef DEBUG
  printf("step = %d; PC = %08x, inst = %08x\n", stepcnt, PC, ins);
#endif
  switch (opcode) {
    // LUI
    case 0x37:
      reg_write(rd, ins & 0xfffff000);
      break;
    // JALR
    case 0x67: {
      int32_t imm = sext(ins >> 20, 12);
      reg_write(rd, PC + 4);
      pc_next = (a + imm) & ~1u;
      break;
    }
    // LOAD (LB/LW)
    case 0x03: {
      int32_t imm = sext(ins >> 20, 12);
      uint32_t addr = (a + imm);
      uint32_t w = M[guest_to_host(addr) >> 2];
#ifdef DEBUG
        printf("raddr = %08x;  rdata = %08x\n", addr, M[guest_to_host(addr)>>2]);
#endif
      if (funct3 == 4) {  // LB
        uint32_t sh = (addr & 3) * 8;
#ifdef DEBUG
        printf("raddr = %08x; rbdata = %08x\n", addr, sext((w >> sh) & 0xff, 8));
#endif
        reg_write(rd, sext((w >> sh) & 0xff, 8));
      } else {  // LW
        reg_write(rd, w);
      }
      break;
    }
    // STORE (SB/SW)
    case 0x23: {
      int32_t imm = sext(((ins >> 7) & 0x1f) | ((ins >> 25) << 5), 12);
      uint32_t addr = a + imm;
#ifdef DEBUG
      printf("waddr = %08x;  wdata = %08x\n", addr, b);
#endif
      if (funct3 == 0) {  // SB
        uint32_t sh = (addr & 3) * 8;
        uint32_t w = M[guest_to_host(addr) >> 2];
        w = (w & ~(0xff << sh)) | ((b & 0xff) << sh);
#ifdef DEBUG
        printf("waddr = %08x; wbdata = %08x, sh = %d\n", addr, w, sh);
#endif
        M[guest_to_host(addr) >> 2] = w;
      } else {  // SW
        if (addr >= 0x20000000 && addr < 0x20040000) {
          pixels[(addr >> 10) & 0xff][(addr >> 2) & 0xff] = b;
          io_write(AM_GPU_FBDRAW, 0, 0, pixels, 256, 256, true);
        } else if (funct3 == 2) {
          M[guest_to_host(addr) >> 2] = b;
        }
      }
      break;
    }
    // OP-IMM (only ADDI)
    case 0x13: {
      int32_t imm = sext(ins >> 20, 12);
      reg_write(rd, a + imm);
      break;
    }
    // OP (only ADD)
    case 0x33:
      reg_write(rd, a + b);
      break;
    default:
      printf("Illegal opcode: %02x\n", opcode);
      break;
  }
  PC = pc_next;
  R[0] = 0; // enforce x0
  stepcnt++;
}

// ---- loader + main ----
int main(void) {
 ioe_init();

#ifdef LOG
  init_log("emu.log");
#endif

#ifdef IMG_HEX
  /* =======================
   * HEX 文件加载
   * ======================= */
  FILE *f = fopen("../bin/vga.hex", "r");
  if (!f) return 1;
  char line[512];
  fgets(line, sizeof(line), f); // skip first line
  while (fgets(line, sizeof(line), f)) {
    unsigned addr, val, off = 0;
    char *p = strchr(line, ':');
    if (!p || sscanf(line, "%x:", &addr) != 1) continue;
    p++;
    while (*p) {
      while (*p == ' ') p++;
      if (sscanf(p, "%x", &val) != 1) break;
      M[addr + off++] = val;
      while (*p && *p != ' ') p++;
    }
  }
  fclose(f);
#else
  /* =======================
   * BIN 文件加载
   * ======================= */
  FILE *f =fopen("../bin/dummy-minirv-npc.bin", "rb");
  size_t bytes_read;
  size_t elements_to_read;
  fseek(f, 0, SEEK_END);
  long file_size = ftell(f);
  rewind(f);
  elements_to_read = file_size / sizeof(uint32_t);
  bytes_read = fread(M, sizeof(uint32_t), elements_to_read, f);
  if (bytes_read != elements_to_read) {
    fclose(f);
    return 1;
  }
  Log("Load default image, size = %d bytes", bytes_read);
#endif

  Log("Build time: %s, %s", __TIME__, __DATE__);
  printf("[EMU] Welcome to MiniRV-EMU!\n");
  printf("[EMU] Simulation start\n");
  log_write("0x%08x: %08x\n", PC, M[guest_to_host(PC) >> 2]);
  while (1) {
#ifdef DEBUG
    if (stepcnt > 140) getchar();  // 等待回车
#endif
    step();
    log_write("0x%08x: %08x\n", PC, M[guest_to_host(PC) >> 2]);
#ifdef DEBUG
    for (int i = 0; i < 16; i++) {
      if (R[i] != R_prev[i]) printf("   \033[31m0x%08x\033[0m", R[i]);
      else printf("   0x%08x", R[i]);
      if ((i + 1) % 4 == 0) printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 16; i++) R_prev[i] = R[i];
#endif
  }
  return 0;
}
