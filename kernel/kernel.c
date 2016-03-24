#include "kernel.h"

/* Since we *know* there will be 2 processes, stemming from the 2 user
 * programs, we can
 *
 * - allocate a fixed-size process table (of PCBs), and use a pointer
 *   to keep track of which entry is currently executing, and
 * - employ a fixed-case of round-robin scheduling: no more processes
 *   can be created, and neither is able to complete.
 */

pcb_t pcb[ 1000 ], *current = NULL;
entry_t entry[1000];
uint32_t nAP  = 0; //number of active proceses
uint32_t nDCP = 0;  //number of dynamically create processes
uint32_t next[1000];
uint32_t slice = 1;

void rrScheduler( ctx_t* ctx ) {
  uint32_t pid = (*current).pid;
  uint32_t nxt = next[ pid ];
  memcpy( &pcb[ pid ].ctx, ctx, sizeof( ctx_t ) );
  memcpy( ctx, &pcb[ nxt ].ctx, sizeof( ctx_t ) );
  current = &pcb[ nxt ];
}

void kernel_handler_rst( ctx_t* ctx              ) {
  /* Initialise PCBs representing processes stemming from execution of
   * the two user programs.  Note in each case that
   *
   * - the CPSR value of 0x50 means the processor is switched into USR
   *   mode, with IRQ interrupts enabled, and
   * - the PC and SP values matche the entry point and top of stack.
   */

  for(uint32_t i=0;i<=999;i++){
    next[i] = 1001;
  }

  memset( &pcb[ 0 ], 0, sizeof( pcb_t ) );
  pcb[ 0 ].pid      = 0;
  pcb[ 0 ].ctx.cpsr = 0x50;
  pcb[ 0 ].ctx.pc   = ( uint32_t )( entry_Sh );
  pcb[ 0 ].ctx.sp   = ( uint32_t )(  &tos_Sh );
  entry[ 0 ].wt     = 100;
  entry[ 0 ].pc     = ( uint32_t )( entry_Sh );
  entry[ 0 ].active = 1;
  next[ 0 ]         = 1;

  memset( &pcb[ 1 ], 0, sizeof( pcb_t ) );
  pcb[ 1 ].pid      = 1;
  pcb[ 1 ].ctx.cpsr = 0x50;
  pcb[ 1 ].ctx.pc   = ( uint32_t )( entry_P0 );
  pcb[ 1 ].ctx.sp   = ( uint32_t )(  &tos_P0 );
  entry[ 1 ].wt     = 50;
  entry[ 1 ].pc     = ( uint32_t )( entry_P0 );
  entry[ 1 ].active = 1;
  next[ 1 ] = 2;

  memset( &pcb[ 2 ], 0, sizeof( pcb_t ) );
  pcb[ 2 ].pid      = 2;
  pcb[ 2 ].ctx.cpsr = 0x50;
  pcb[ 2 ].ctx.pc   = ( uint32_t )( entry_P1 );
  pcb[ 2 ].ctx.sp   = ( uint32_t )(  &tos_P1 );
  entry[ 2 ].wt     = 50;
  entry[ 2 ].pc     = ( uint32_t )( entry_P1 );
  entry[ 2 ].active = 1;
  next[ 2 ]         = 3;

  memset( &pcb[ 3 ], 0, sizeof( pcb_t ) );
  pcb[ 3 ].pid      = 3;
  pcb[ 3 ].ctx.cpsr = 0x50;
  pcb[ 3 ].ctx.pc   = ( uint32_t )( entry_P2 );
  pcb[ 3 ].ctx.sp   = ( uint32_t )(  &tos_P2 );
  entry[ 3 ].wt     = 50;
  entry[ 3 ].pc     = ( uint32_t )( entry_P2 );
  entry[ 3 ].active = 1;
  next[ 3 ]         = 0;

  /* Once the PCBs are initialised, we (arbitrarily) select one to be
   * restored (i.e., executed) when the function then returns.
   */

  current = &pcb[ 0 ]; memcpy( ctx, &current->ctx, sizeof( ctx_t ) );
  nAP = 4;
  TIMER0->Timer1Load     = 0x00100000; // select period = 2^20 ticks ~= 1 sec
  TIMER0->Timer1Ctrl     = 0x00000002; // select 32-bit   timer
  TIMER0->Timer1Ctrl    |= 0x00000040; // select periodic timer
  TIMER0->Timer1Ctrl    |= 0x00000020; // enable          timer interrupt
  TIMER0->Timer1Ctrl    |= 0x00000080; // enable          timer

  GICC0->PMR             = 0x000000F0; // unmask all            interrupts
  GICD0->ISENABLER[ 1 ] |= 0x00000010; // enable timer          interrupt
  GICC0->CTLR            = 0x00000001; // enable GIC interface
  GICD0->CTLR            = 0x00000001; // enable GIC distributor

  irq_enable();

  return;
}

void kernel_handler_irq(ctx_t* ctx) {
  // Step 2: read  the interrupt identifier so we know the source.

  uint32_t id = GICC0->IAR;

  // Step 4: handle the interrupt, then clear (or reset) the source.

  if( id == GIC_SOURCE_TIMER0 ) {
    TIMER0->Timer1IntClr = 0x01;
    if(slice%4 == 0)
      rrScheduler( ctx );
    slice++;
  }

  // Step 5: write the interrupt identifier to signal we're done.

  GICC0->EOIR = id;
}

void kernel_handler_svc( ctx_t* ctx, uint32_t id ) {
  /* Based on the identified encoded as an immediate operand in the
   * instruction,
   *
   * - read  the arguments from preserved usr mode registers,
   * - perform whatever is appropriate for this system call,
   * - write any return value back to preserved usr mode registers.
   */

  switch( id ) {
    case 0x00 : { // yield()
      //scheduler( ctx );
      break;
    }
    case 0x01 : { // write( fd, x, n )
      uint32_t   fd = ( uint32_t   )( ctx->gpr[ 0 ] );
      char*  x      = ( char* )( ctx->gpr[ 1 ] );
      uint32_t    n = ( uint32_t   )( ctx->gpr[ 2 ] );

      PL011_t* stream = getStream(fd);
      for( uint32_t i = 0; i < n; i++ ) {
        if( fd==0 ){
          PL011_putc( stream, *x++ );
        }
      }

      ctx->gpr[ 0 ] = n;
      break;
    }

    case 0x02: { // read(fd, x, n )
      uint32_t    fd = ( uint32_t   )( ctx->gpr[ 0 ] );
      char*  x       = ( char* )( ctx->gpr[ 1 ] );
      uint32_t    n  = ( uint32_t   )( ctx->gpr[ 2 ] );
      PL011_t* stream = getStream(fd);
      for( uint32_t i=0; i < n; i++){
        x[i] = PL011_getc( stream );
      }

      break;
    }
    case 0x03: { // readLine(fd, x)
      uint32_t    fd = ( uint32_t   )( ctx->gpr[ 0 ] );
      char*  x       = ( char* )( ctx->gpr[ 1 ] );
      uint32_t     n = 0;
      char y;
      PL011_t* stream = getStream(fd);
      while(1){
        char y = PL011_getc( stream );
        if( y==13){
          x[n] = '\0';
          PL011_putc( stream, '\n');
          break;
        }
        x[n] = y;
        PL011_putc( stream, y);
        n++;
      }

      ctx->gpr[ 0 ] = n;
      break;
    }
    case 0x04: { // fork(pid,weight)
      uint32_t    pid    = ( uint32_t   )( ctx->gpr[ 0 ] );
      uint32_t     wt    = ( uint32_t   )( ctx->gpr[ 1 ] );

      uint32_t currentID = (*current).pid;
      uint32_t     n     = 0;
      if(!entry[pid].active){
        ctx->gpr[ 0 ] = -1;
        break;
      }
      while( entry[n].active ){
        n++;
      }

      if(n<1000){

        nDCP++;
        memset( &pcb[ n ], 0, sizeof( pcb_t ) );
        pcb[ n ].pid      = n;
        pcb[ n ].ctx.sp   = (nDCP)*4096 + ((uint32_t)&boh);
        pcb[ n ].ctx.cpsr = 0x50;
        pcb[ n ].ctx.pc   = entry[ pid ].pc;
        entry[ n ].wt     = wt;
        entry[ n ].pc     = pcb[ n ].ctx.pc;
        entry[ n ].active = 1;
        nAP++;
        for(uint32_t i = 0; i <= 999; i++){
          if(next[ i ] == 0){
            next[ i ] = n;
            next[ n ] = 0;
          }
        }
        //current = &pcb[n];
        //memcpy( ctx, &current->ctx, sizeof( ctx_t ) );
      }

      ctx->gpr[ 0 ] = n;
      break;
    }
    case 0x05: { // exit(pid)
      uint32_t    pid     = ( uint32_t   )( ctx->gpr[ 0 ] );
      if( entry[ pid ].active )
        entry[ pid ].active = 0;
      else{
        ctx->gpr[ 0 ] = -1;
        break;
      }
      nAP--;
      for(uint32_t i =0; i <= 999; i++){
        if(next[ i ] == pid){
          next[ i ] = next[ pid ];
          next[ pid ] = 1001;
        }
      }
      ctx->gpr[ 0 ] = pid;
      break;
    }
    case 0x06: { // exec(pid)
      break;
    }
    default: {
      break;
    }
  }

  return;
}
