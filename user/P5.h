#ifndef __P5_H
#define __P5_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P0 entry point and top of stack
extern void (*entry_P5)();
extern uint32_t tos_P5;

#endif
