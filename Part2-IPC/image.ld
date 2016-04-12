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
  /* allocate stack for Aristotle       */
  .       = . + 0x00001000;
  tos_Aristotle  = .;
  /* allocate stack for Confucius       */
  .       = . + 0x00001000;
  tos_Confucius  = .;
  /* allocate stack for Descartes       */
  .       = . + 0x00001000;
  tos_Descartes  = .;
  /* allocate stack for Socrates       */
  .       = . + 0x00001000;
  tos_Socrates = .;
  /* allocate stack for Voltaire       */
  .       = . + 0x00001000;
  tos_Voltaire  = .;
}
