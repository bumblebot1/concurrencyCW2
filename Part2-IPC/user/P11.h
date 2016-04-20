#ifndef __P11_H
#define __P11_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P1 entry point and top of stack
extern void (*entry_P11)();
extern uint32_t tos_P11;

#endif
