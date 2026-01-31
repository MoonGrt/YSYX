// #define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <am.h>
#include <klib-macros.h>

#define M_SIZE 0x1000000

static uint32_t PC;
static uint32_t R[16];          // x0..x31 (x0 hardwired to 0)
static uint32_t M[M_SIZE];
static uint32_t pixels[256][256];

// ---- helpers ----
static inline uint32_t reg_read(uint32_t r) { return r ? R[r] : 0; }
static inline void     reg_write(uint32_t r, uint32_t v) { if (r) R[r] = v; }
static inline int32_t  sext(uint32_t v, int b) { return (int32_t)(v << (32-b)) >> (32-b); }

// ---- one cycle ----
static uint32_t stepcnt;
static void step(void) {
  uint32_t ins = M[PC >> 2];
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
      uint32_t addr = (a + imm) & (M_SIZE - 1);
      uint32_t w = M[addr >> 2];
#ifdef DEBUG
      printf("raddr = %08x; rdata = %08x\n", addr, M[addr>>2]);
#endif
      if (funct3 == 4) {  // LB
        uint32_t sh = (addr & 3) * 8;
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
      if (funct3 == 0) {  // SB
        addr &= M_SIZE-1;
        uint32_t sh = (addr & 3) * 8;
        uint32_t w = M[addr >> 2];
        w = (w & ~(0xff << sh)) | ((b & 0xff) << sh);
        M[addr >> 2] = w;
#ifdef DEBUG
        printf("waddr = %08x; wdata = %08x\n", addr, w);
#endif
      } else {  // SW
        if (addr >= 0x20000000 && addr < 0x20040000) {
          pixels[(addr >> 10) & 0xff][(addr >> 2) & 0xff] = b;
          io_write(AM_GPU_FBDRAW, 0, 0, pixels, 256, 256, true);
        } else if (funct3 == 2) {
          addr &= M_SIZE-1;
          M[addr >> 2] = b;
#ifdef DEBUG
          printf("waddr = %08x; wdata = %08x\n", addr, b);
#endif
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

    while (1) {
#ifdef DEBUG
        if (stepcnt > 117) getchar();  // 等待回车 // 746
#endif
        step();
#ifdef DEBUG
        for (int i = 0; i < 16; i++) {
            printf("   0x%08x", R[i]);
            if ((i + 1) % 4 == 0) printf("\n");
        }
        printf("\n");
#endif
    }
    return 0;
}
