#ifndef __P8_H
#define __P8_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P1 entry point and top of stack
extern void (*entry_P8)();
extern uint32_t tos_P8;

#endif
