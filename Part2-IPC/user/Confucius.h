#ifndef __Confucius_H
#define __Confucius_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P0 entry point and top of stack
extern void (*entry_Confucius)();
extern uint32_t tos_Confucius;

#endif
