SECTIONS {
  /* assign address (per  QEMU)  */
  .       =     0x70010000;
  /* place text segment(s)       */
  .text : { kernel/interrupt.o(.text) *(.text .rodata) }
  /* place data segment(s)       */
  .data : {                           *(.data        ) }
  /* place bss  segment(s)       */
  .bss  : {                           *(.bss         ) }
  /* align  address (per AAPCS)  */
  .       = ALIGN(8);
  /* allocate stack for svc mode */
  .       = . + 0x00001000;
  tos_svc = .;
  /* allocate stack for irq mode */
  .       = . + 0x00001000;
  tos_irq = .;
  /* allocate bottom of heap kernel*/
  boh     = .;
  .       = . + 0x00800000;
  /* allocate stack for P0       */
  .       = . + 0x00001000;
  tos_P0  = .;
  /* allocate stack for P1       */
  .       = . + 0x00001000;
  tos_P1  = .;
  /* allocate stack for P2       */
  .       = . + 0x00001000;
  tos_P2  = .;
  /* allocate stack for P3       */
  .       = . + 0x00001000;
  tos_P3  = .;
  /* allocate stack for P4       */
  .       = . + 0x00001000;
  tos_P4  = .;
  /* allocate stack for P5       */
  .       = . + 0x00001000;
  tos_P5  = .;
  /* allocate stack for P6       */
  .       = . + 0x00001000;
  tos_P6  = .;
  /* allocate stack for P7       */
  .       = . + 0x00001000;
  tos_P7  = .;
  /* allocate stack for P8       */
  .       = . + 0x00001000;
  tos_P8  = .;
  /* allocate stack for P9       */
  .       = . + 0x00001000;
  tos_P9  = .;
  /* allocate stack for P10       */
  .       = . + 0x00001000;
  tos_P10  = .;
  /* allocate stack for P11       */
  .       = . + 0x00001000;
  tos_P11  = .;
}
