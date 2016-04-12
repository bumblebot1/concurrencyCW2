#ifndef __Sh_H
#define __Sh_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P0 entry point and top of stack
extern void (*entry_Sh)();
extern uint32_t tos_Sh;

#endif
