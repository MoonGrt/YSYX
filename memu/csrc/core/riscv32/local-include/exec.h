#ifndef __EXEC_H__
#define __EXEC_H__

#include <cpu/decode.h>


void rtl_reset(void);

void rtl_exit(void);

extern Decode RTL_Decode;

#endif
