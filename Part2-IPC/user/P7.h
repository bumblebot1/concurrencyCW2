#ifndef __P7_H
#define __P7_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P1 entry point and top of stack
extern void (*entry_P7)();
extern uint32_t tos_P7;

#endif
