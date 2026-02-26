#ifndef __EXEC_H__
#define __EXEC_H__

#include <cpu/decode.h>

void rtl_init(int argc, char *argv[]);
void rtl_step(void);
void rtl_exit(void);

extern Decode RTL_Decode;

#endif
