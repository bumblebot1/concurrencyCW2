#ifndef __P9_H
#define __P9_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P1 entry point and top of stack
extern void (*entry_P9)();
extern uint32_t tos_P9;

#endif
