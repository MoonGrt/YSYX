#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <common.h>
#include "../../../include/device/map.h"

#ifdef CONFIG_ITRACE

#define MAX_IRINGBUF 16

typedef struct {
  word_t pc;
  uint32_t inst;
} ItraceNode;

ItraceNode iringbuf[MAX_IRINGBUF];
int p_cur = 0;
bool full = false;

void trace_inst(word_t pc, uint32_t inst) {
  iringbuf[p_cur].pc = pc;
  iringbuf[p_cur].inst = inst;
  p_cur = (p_cur + 1) % MAX_IRINGBUF;
  full = full || p_cur == 0;
}

void display_inst(void) {
  if (!full && !p_cur) return;
  int end = p_cur;
  int i = full?p_cur:0;
  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
  char buf[128]; // 128 should be enough!
  char *p;
  do {
    p = buf;
    p += sprintf(buf, "%s" FMT_WORD ": %08x ", (i+1)%MAX_IRINGBUF==end?" --> ":"     ", iringbuf[i].pc, iringbuf[i].inst);
    disassemble(p, buf+sizeof(buf)-p, iringbuf[i].pc, (uint8_t *)&iringbuf[i].inst, 4);
    if ((i+1)%MAX_IRINGBUF==end) printf(ANSI_FG_MAGENTA);
    puts(buf);
  } while ((i = (i+1)%MAX_IRINGBUF) != end);
  puts(ANSI_NONE);
}

#endif // ITRACE

#ifdef CONFIG_MTRACE

static inline bool mtrace_limit(paddr_t addr) {
  return addr >= CONFIG_MTRACE_LO && addr < CONFIG_MTRACE_HI;
}

void mtrace(bool is_write, paddr_t addr, int len, word_t data) {
  if (!mtrace_limit(addr)) return;
  log_write("[M] %c addr=" FMT_PADDR ", len=%d, %s=" FMT_WORD "\n",
            is_write ? 'W' : 'R', addr, len,
            is_write ? "write" : "-read", data);
}

#endif  // CONFIG_MTRACE

#ifdef CONFIG_DTRACE

void dtrace(bool is_write, paddr_t addr, int len, word_t data, IOMap *map) {
  log_write("[D] %s %s: " FMT_PADDR ", len=%d, %s=" FMT_WORD "\n",
            is_write ? "W" : " R", map->name, addr, len,
            is_write ? "with" : "return", data);
}

#endif  // CONFIG_DTRACE

#ifdef CONFIG_ETRACE

void etrace(uint32_t epc, uint32_t ecode) {
  log_write("[E]: ecall at " FMT_WORD "\n", epc);
}

#endif  // CONFIG_ETRACE

#ifdef CONFIG_FTRACE

typedef struct {
  char name[32];  // func name, 32 should be enough
  paddr_t addr;
  unsigned char info;
  Elf32_Xword size;
} SymEntry;
SymEntry *symbol_tbl = NULL;  // dynamic allocated
typedef struct tail_rec_node {
  paddr_t pc, depend;
  struct tail_rec_node *next;
} TailRecNode;

int symbol_tbl_size = 0;
int call_depth = 0;
TailRecNode *tail_rec_head = NULL;  // linklist with head, dynamic allocated
FILE *ftrace_fp = NULL;

void ftrace_write(const char *format, ...) {
  extern bool log_enable();
  if (log_enable() && ftrace_fp != NULL) {
    va_list args;
    va_start(args, format);
    vfprintf(ftrace_fp, format, args);
    va_end(args);
  }
}

static void read_elf_header(int fd, Elf32_Ehdr *eh) {
  assert(lseek(fd, 0, SEEK_SET) == 0);
  assert(read(fd, (void *)eh, sizeof(Elf32_Ehdr)) == sizeof(Elf32_Ehdr));
  if (eh->e_ident[EI_MAG0] != ELFMAG0 ||
      eh->e_ident[EI_MAG1] != ELFMAG1 ||
      eh->e_ident[EI_MAG2] != ELFMAG2 ||
      eh->e_ident[EI_MAG3] != ELFMAG3) {
    printf("Not an ELF file\n");
  }
  // check if is elf using fixed format of Magic: 7f 45 4c 46 ...
  if(strncmp((char*)eh->e_ident, "\177ELF", 4))
    panic("malformed ELF file");
}

static void display_elf_hedaer(Elf32_Ehdr eh) {
  struct { uint8_t val; const char *desc; } class_map[] = {
    { ELFCLASS32, "32-bit objects" },
    { ELFCLASS64, "64-bit objects" }
  };
  struct { uint8_t val; const char *desc; } data_map[] = {
    { ELFDATA2LSB, "2's complement, little endian" },
    { ELFDATA2MSB, "2's complement, big endian" }
  };
  struct { uint8_t val; const char *desc; } osabi_map[] = {
    { ELFOSABI_SYSV, "UNIX System V ABI" },
    { ELFOSABI_HPUX, "HP-UX" },
    { ELFOSABI_NETBSD, "NetBSD" },
    { ELFOSABI_LINUX, "Linux" },
    { ELFOSABI_SOLARIS, "Sun Solaris" },
    { ELFOSABI_AIX, "IBM AIX" },
    { ELFOSABI_IRIX, "SGI Irix" },
    { ELFOSABI_FREEBSD, "FreeBSD" },
    { ELFOSABI_TRU64, "Compaq TRU64 UNIX" },
    { ELFOSABI_MODESTO, "Novell Modesto" },
    { ELFOSABI_OPENBSD, "OpenBSD" },
    { ELFOSABI_ARM_AEABI, "ARM EABI" },
    { ELFOSABI_ARM, "ARM" },
    { ELFOSABI_STANDALONE, "Standalone (embedded) app" }
  };
  struct { uint16_t val; const char *desc; } type_map[] = {
    { ET_NONE, "N/A (0x0)" },
    { ET_REL, "Relocatable" },
    { ET_EXEC, "Executable" },
    { ET_DYN, "Shared Object" }
  };
  struct { uint16_t val; const char *desc; } machine_map[] = {
    { EM_NONE, "None (0x0)" },
    { EM_386, "INTEL x86 (0x%x)" },
    { EM_X86_64, "AMD x86_64 (0x%x)" },
    { EM_AARCH64, "AARCH64 (0x%x)" }
  };
  #define PRINT_MAP(value, map, def_fmt) \
    do { \
      size_t i; \
      for (i = 0; i < sizeof(map)/sizeof(map[0]); i++) { \
        if ((value) == map[i].val) { \
          ftrace_write("%s\n", map[i].desc); \
          break; \
        } \
      } \
      if (i == sizeof(map)/sizeof(map[0])) \
        ftrace_write(def_fmt, value); \
    } while(0)
  ftrace_write("Storage class\t= "); 
  PRINT_MAP(eh.e_ident[EI_CLASS], class_map, "INVALID CLASS\n");
  ftrace_write("Data format\t= ");
  PRINT_MAP(eh.e_ident[EI_DATA], data_map, "INVALID Format\n");
  ftrace_write("OS ABI\t\t= ");
  PRINT_MAP(eh.e_ident[EI_OSABI], osabi_map, "Unknown (0x%x)\n");
  ftrace_write("Filetype \t= ");
  PRINT_MAP(eh.e_type, type_map, "Unknown (0x%x)\n");
  ftrace_write("Machine\t\t= ");
  PRINT_MAP(eh.e_machine, machine_map, "0x%x\n");
  /* Entry point */
  ftrace_write("Entry point\t= 0x%08lx\n", eh.e_entry);
  /* ELF header size in bytes */
  ftrace_write("ELF header size\t= 0x%08x\n", eh.e_ehsize);
  /* Program Header */
  ftrace_write("Program Header\t= 0x%08lx\n\t\t  %d entries\n\t\t  %d bytes\n",
                 eh.e_phoff, eh.e_phnum, eh.e_phentsize);
  /* Section header starts at */
  ftrace_write("Section Header\t= 0x%08lx\n\t\t  %d entries\n\t\t  %d bytes\n\t\t  0x%08x (string table offset)\n",
                 eh.e_shoff, eh.e_shnum, eh.e_shentsize, eh.e_shstrndx);
  /* File flags (Machine specific)*/
  ftrace_write("File flags \t= 0x%08x\n", eh.e_flags);
  /* ARM-specific ELF flags */
  int32_t ef = eh.e_flags;
  ftrace_write("\t\t  ");
  #define ARM_FLAG_PRINT(flag, name) if(ef & (flag)) ftrace_write("," name " ");
  ARM_FLAG_PRINT(EF_ARM_RELEXEC, "RELEXEC");
  ARM_FLAG_PRINT(EF_ARM_HASENTRY, "HASENTRY");
  ARM_FLAG_PRINT(EF_ARM_INTERWORK, "INTERWORK");
  ARM_FLAG_PRINT(EF_ARM_APCS_26, "APCS_26");
  ARM_FLAG_PRINT(EF_ARM_APCS_FLOAT, "APCS_FLOAT");
  ARM_FLAG_PRINT(EF_ARM_PIC, "PIC");
  ARM_FLAG_PRINT(EF_ARM_ALIGN8, "ALIGN8");
  ARM_FLAG_PRINT(EF_ARM_NEW_ABI, "NEW_ABI");
  ARM_FLAG_PRINT(EF_ARM_OLD_ABI, "OLD_ABI");
  ARM_FLAG_PRINT(EF_ARM_SOFT_FLOAT, "SOFT_FLOAT");
  ARM_FLAG_PRINT(EF_ARM_VFP_FLOAT, "VFP_FLOAT");
  ARM_FLAG_PRINT(EF_ARM_MAVERICK_FLOAT, "MAVERICK_FLOAT");
  ftrace_write("\n");
  /* MSB of flags conatins ARM EABI version */
  ftrace_write("ARM EABI\t= Version %d\n", (ef & EF_ARM_EABIMASK)>>24);
  ftrace_write("\n");	/* End of ELF header */
}

static void read_section(int fd, Elf32_Shdr sh, void *dst) {
  assert(dst != NULL);
  assert(lseek(fd, (off_t)sh.sh_offset, SEEK_SET) == (off_t)sh.sh_offset);
  assert(read(fd, dst, sh.sh_size) == sh.sh_size);
}

static void read_section_headers(int fd, Elf32_Ehdr eh, Elf32_Shdr *sh_tbl) {
  assert(lseek(fd, eh.e_shoff, SEEK_SET) == eh.e_shoff);
  for(int i = 0; i < eh.e_shnum; i++)
    assert(read(fd, (void *)&sh_tbl[i], eh.e_shentsize) == eh.e_shentsize);
}

static void display_section_headers(int fd, Elf32_Ehdr eh, Elf32_Shdr sh_tbl[]) {
  // warn: C99
  char sh_str[sh_tbl[eh.e_shstrndx].sh_size];
  read_section(fd, sh_tbl[eh.e_shstrndx], sh_str);
  /* Read section-header string-table */
  ftrace_write("========================================");
  ftrace_write("========================================\n");
  ftrace_write(" idx offset     load-addr  size       algn"
               " flags      type       section\n");
  ftrace_write("========================================");
  ftrace_write("========================================\n");
  for(int i = 0; i < eh.e_shnum; i++) {
    ftrace_write(" %03d ", i);
    ftrace_write("0x%08lx ", sh_tbl[i].sh_offset);
    ftrace_write("0x%08lx ", sh_tbl[i].sh_addr);
    ftrace_write("0x%08lx ", sh_tbl[i].sh_size);
    ftrace_write("%-4ld ", sh_tbl[i].sh_addralign);
    ftrace_write("0x%08lx ", sh_tbl[i].sh_flags);
    ftrace_write("0x%08x ", sh_tbl[i].sh_type);
    ftrace_write("%s\t", (sh_str + sh_tbl[i].sh_name));
    ftrace_write("\n");
  }
  ftrace_write("========================================");
  ftrace_write("========================================\n");
  ftrace_write("\n");	/* end of section header table */
}

static void read_symbol_table(int fd, Elf32_Ehdr eh, Elf32_Shdr sh_tbl[], int sym_idx) {
  Elf32_Sym sym_tbl[sh_tbl[sym_idx].sh_size];
  read_section(fd, sh_tbl[sym_idx], sym_tbl);
  int str_idx = sh_tbl[sym_idx].sh_link;
  char str_tbl[sh_tbl[str_idx].sh_size];
  read_section(fd, sh_tbl[str_idx], str_tbl);
  int sym_count = (sh_tbl[sym_idx].sh_size / sizeof(Elf32_Sym));
  // log
  ftrace_write("Symbol count: %d\n", sym_count);
  ftrace_write("====================================================\n");
  ftrace_write(" num    value            type size       name\n");
  ftrace_write("====================================================\n");
  for (int i = 0; i < sym_count; i++)
    ftrace_write(" %-3d    %016lx %-4d %-10ld %s\n", i,
      sym_tbl[i].st_value,
      ELF32_ST_TYPE(sym_tbl[i].st_info),
      sym_tbl[i].st_size,
      str_tbl + sym_tbl[i].st_name
    );
  ftrace_write("====================================================\n\n");
  // read
  symbol_tbl_size = sym_count;
  symbol_tbl = malloc(sizeof(SymEntry) * sym_count);
  for (int i = 0; i < sym_count; i++) {
    symbol_tbl[i].addr = sym_tbl[i].st_value;
    symbol_tbl[i].info = sym_tbl[i].st_info;
    symbol_tbl[i].size = sym_tbl[i].st_size;
    memset(symbol_tbl[i].name, 0, 32);
    strncpy(symbol_tbl[i].name, str_tbl + sym_tbl[i].st_name, 31);
  }
}

static void read_symbols(int fd, Elf32_Ehdr eh, Elf32_Shdr sh_tbl[]) {
  for (int i = 0; i < eh.e_shnum; i++)
    switch (sh_tbl[i].sh_type) {
    case SHT_SYMTAB: case SHT_DYNSYM:
      read_symbol_table(fd, eh, sh_tbl, i); break;
    }
}

static void init_tail_rec_list() {
  tail_rec_head = (TailRecNode *)malloc(sizeof(TailRecNode));
  tail_rec_head->pc = 0;
  tail_rec_head->next = NULL;
}

static int find_symbol_func(paddr_t target, bool is_call) {
  int i;
  for (i = 0; i < symbol_tbl_size; i++) {
    if (ELF64_ST_TYPE(symbol_tbl[i].info) == STT_FUNC) {
      if (is_call) {
        if (symbol_tbl[i].addr == target) break;
      } else {
        if (symbol_tbl[i].addr <= target && target < symbol_tbl[i].addr + symbol_tbl[i].size) break;
      }
    }
  }
  return i<symbol_tbl_size?i:-1;
}

static void insert_tail_rec(paddr_t pc, paddr_t depend) {
  TailRecNode *node = (TailRecNode *)malloc(sizeof(TailRecNode));
  node->pc = pc;
  node->depend = depend;
  node->next = tail_rec_head->next;
  tail_rec_head->next = node;
}

static void remove_tail_rec() {
  TailRecNode *node = tail_rec_head->next;
  tail_rec_head->next = node->next;
  free(node);
}

int call_num=0;
void ftrace_call(paddr_t pc, paddr_t target, bool is_tail) {
  if (symbol_tbl == NULL) return;
  ++call_depth;
  if (call_depth <= 2) return; // ignore _trm_init & main
  int i = find_symbol_func(target, true);
  int time = call_num;
  while(time>0){
    ftrace_write("  ");
    time--;
  }
  ftrace_write(FMT_PADDR ": %*scall [%s@" FMT_PADDR "]\n",
    pc,
    (call_depth-3)*2, "",
    i>=0?symbol_tbl[i].name:"???",
    target
  );
  if (is_tail) insert_tail_rec(pc, target);
  call_num++;
}

void ftrace_ret(paddr_t pc) {
  if (symbol_tbl == NULL) return;
  if (call_depth <= 2) return; // ignore _trm_init & main
  int i = find_symbol_func(pc, false);
  int time = call_num;
  while(time>0){
    ftrace_write("  ");
    time--;
  }
  ftrace_write(FMT_PADDR ": %*sret [%s]\n",
    pc,
    (call_depth-3)*2, "",
    i>=0?symbol_tbl[i].name:"???"
  );
  --call_depth;
  TailRecNode *node = tail_rec_head->next;
  if (node != NULL) {
    int depend_i = find_symbol_func(node->depend, true);
    if (depend_i == i) {
      paddr_t ret_target = node->pc;
      remove_tail_rec();
      ftrace_ret(ret_target);
    }
  }
  call_num--;
}

#define DEFAULT_FTRACE_FILE "build/memu-ftrace.txt"

void init_ftrace_log(const char *ftrace_file) {
  if (ftrace_file == NULL)
    ftrace_file = DEFAULT_FTRACE_FILE;
  FILE *fp = fopen(ftrace_file, "w");
  Assert(fp, "Can not open '%s'", ftrace_file);
  ftrace_fp = fp;
  Log("Ftrace log is written to %s", ftrace_file);
}

void parse_elf(const char *elf_file) {
  if (elf_file == NULL) return;
  Log("specified ELF file: %s", elf_file);
  int fd = open(elf_file, O_RDONLY | O_SYNC);
  Assert(fd >= 0, "Error %d: unable to open %s\n", fd, elf_file);
  Elf32_Ehdr eh;
  read_elf_header(fd, &eh);
  display_elf_hedaer(eh);
  Elf32_Shdr sh_tbl[eh.e_shentsize * eh.e_shnum];
  read_section_headers(fd, eh, sh_tbl);
  display_section_headers(fd, eh, sh_tbl);
  read_symbols(fd, eh, sh_tbl);
  init_tail_rec_list();
  close(fd);
}

void init_ftrace(const char *ftrace_file, const char *elf_file) {
  init_ftrace_log(ftrace_file);
  parse_elf(elf_file);
}

#endif  // CONFIG_FTRACE
