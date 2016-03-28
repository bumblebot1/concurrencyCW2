#ifndef __P4_H
#define __P4_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P0 entry point and top of stack
extern void (*entry_P4)();
extern uint32_t tos_P4;

#endif
