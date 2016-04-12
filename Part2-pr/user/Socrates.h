#ifndef __Socrates_H
#define __Socrates_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P0 entry point and top of stack
extern void (*entry_Socrates)();
extern uint32_t tos_Socrates;

#endif
