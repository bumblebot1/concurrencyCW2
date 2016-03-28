#ifndef __Aristotle_H
#define __Aristotle_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P0 entry point and top of stack
extern void (*entry_Aristotle)();
extern uint32_t tos_Aristotle;

#endif
