#ifndef __Voltaire_H
#define __Voltaire_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P0 entry point and top of stack
extern void (*entry_Voltaire)();
extern uint32_t tos_Voltaire;

#endif
