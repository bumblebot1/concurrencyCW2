#ifndef __DiskTest_H
#define __DiskTest_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libc.h"

// define symbols for P0 entry point and top of stack
extern void (*entry_DiskTest)();
extern uint32_t tos_DiskTest;

#endif
