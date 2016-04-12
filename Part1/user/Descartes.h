#ifndef __Descartes_H
#define __Descartes_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P0 entry point and top of stack
extern void (*entry_Descartes)();
extern uint32_t tos_Descartes;

#endif
