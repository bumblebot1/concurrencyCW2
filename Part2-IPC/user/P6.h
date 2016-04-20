#ifndef __P6_H
#define __P6_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P1 entry point and top of stack
extern void (*entry_P6)();
extern uint32_t tos_P6;

#endif
