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

#include "Aristotle.h"
#include "Confucius.h"
#include "Descartes.h"
#include "Socrates.h"
#include "Voltaire.h"


#include "disk.h"
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
  uint8_t block;
} pcb_t;

typedef struct {
  uint32_t pc;
  uint8_t active;
} entry_t;

typedef struct {
  uint32_t wt;
  pid_t pid;
} heap_t;

typedef struct {
  uint32_t fd;
  uint8_t blocks[8];
  char name[8];
  uint8_t active;
  open_t open;
  uint8_t blockIndex;
  uint8_t blockLine;
  uint8_t lineChar;
} file_t;

typedef struct {
  void* chan;
  pid_t readID;
  pid_t writeID;
  uint8_t active;
  uint8_t ready;
} chan_t;

extern uint32_t boh;

#endif
