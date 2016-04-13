#ifndef __ConcDisk_H
#define __ConcDisk_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P0 entry point and top of stack
extern void (*entry_ConcDisk)();
extern uint32_t tos_ConcDisk;

#endif
