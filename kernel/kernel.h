#ifndef __KERNEL_H
#define __KERNEL_H

#include <stddef.h>
#include <stdint.h>

#include   "GIC.h"
#include "PL011.h"
#include "SP804.h"

#include "interrupt.h"

// Include functionality from newlib, the embedded standard C library.
#include <string.h>

// Include definitions relating to the 2 user programs.

#include "P0.h"
#include "P1.h"
#include "P2.h"
#include "P3.h"
#include "Sh.h"

/* The kernel source code is made simpler by three type definitions:
 *
 * - a type that captures each component of an execution context (i.e.,
 *   processor state) in a compatible order wrt. the low-level handler
     preservation and restoration prologue and epilogue,
 * - a type that captures a process identifier, which is basically an
 *   integer, and
 * - a type that captures a process PCB.
 */

typedef struct {
  uint32_t cpsr, pc, gpr[ 13 ], sp, lr;
} ctx_t;

typedef int pid_t;

typedef struct {
  pid_t pid;
  ctx_t ctx;
} pcb_t;

typedef struct {
  uint32_t pc;
  uint8_t active;
} entry_t;

typedef struct {
  uint32_t wt;
  pid_t pid;
} heap_t;

extern uint32_t boh;

PL011_t* getStream(uint32_t fd){
  switch (fd) {
    case 0:
      return UART0;
    case 1:
      return UART1;
    case 2:
      return UART2;
    case 3:
      return UART3;
    default:
      return UART0;
  }
}

#endif
