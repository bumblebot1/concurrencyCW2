#include "kernel.h"

/* Since we *know* there will be 2 processes, stemming from the 2 user
 * programs, we can
 *
 * - allocate a fixed-size process table (of PCBs), and use a pointer
 *   to keep track of which entry is currently executing, and
 * - employ a fixed-case of round-robin scheduling: no more processes
 *   can be created, and neither is able to complete.
 */
#define maxProcesses 1000
#define heapSize 1001
#define lastPindex 999
#define subBlockSize 256
#define subBlockNo 256 //indexes start from 1 to 255
#define inodeSize 256
#define diskEnd 65536
pcb_t pcb[ maxProcesses ], *current = NULL;
entry_t entry[ maxProcesses ];
heap_t heap[ heapSize ];
uint32_t nAP  = 0; //number of active proceses
uint32_t nDCP = 0; //number of dynamically create processes
uint32_t next[maxProcesses];
uint32_t slice = 1;
heap_t res;
chan_t channels[maxProcesses];
uint32_t nChans = 0;
uint8_t schedType = 2;
uint8_t used[subBlockSize]; //disk subblock used/unused
file_t fileList[inodeSize];

void rrScheduler( ctx_t* ctx ) {
  uint32_t pid = (*current).pid;
  uint32_t nxt = next[ pid ];
  while(pcb[ nxt ].block == 1){
    pid = nxt;
    nxt = next[pid];
  }
  memcpy( &pcb[ (*current).pid ].ctx, ctx, sizeof( ctx_t ) );
  memcpy( ctx, &pcb[ nxt ].ctx, sizeof( ctx_t ) );
  current = &pcb[ nxt ];
}

void heap_decreaseKey(pid_t pid, uint32_t wt){
  uint32_t i;
  for(i=1; i<=maxProcesses; i++){
    if( heap[ i ].pid == pid)
      break;
  }
  if(heap[i].wt < wt)
    return;
  else{
    heap[i].wt = wt;
    uint32_t parent = i/2;
    while(1 <= parent && heap[ parent ].wt > heap[ i ].wt){
      heap_t aux = heap[ parent ];
      heap[ parent ] = heap[ i ];
      heap[ i ] = aux;
      i = parent;
      parent = i/2;
    }
  }
}

void heap_insert(pid_t pid, uint32_t wt ){
  uint32_t i;
  for(i=1; i<=maxProcesses; i++){
    if( heap[i].pid == heapSize )
      break;
  }
  heap[ i ].wt  = wt;
  heap[ i ].pid = pid;
  heap_decreaseKey(pid,wt);
}

heap_t heap_extractMin(){
  heap_t toReturn = heap[1];
  heap[ 1 ] = heap[ nAP ];
  heap[ nAP ].wt  = heapSize;
  heap[ nAP ].pid = heapSize;
  uint32_t i = 1;
  while(heap[ i ].wt > heap[ 2*i ].wt || heap[ i ].wt > heap[ 2*i+1 ].wt){
    uint32_t min ;
    if(heap[ 2*i ].wt > heap[ 2*i+1 ].wt)
      min = 2*i+1;
    else
      min = 2*i;
    heap_t aux  = heap[i];
    heap[ i ]   = heap[ min ];
    heap[ min ] = aux;
    i = min;
  }
  return toReturn;
}

void heap_remove(pid_t pid){
  heap_decreaseKey(pid,0);
  heap_extractMin();
}

void prScheduler(ctx_t* ctx){
  uint32_t pid = (*current).pid;
  heap_t min = heap_extractMin();
  uint32_t nxt = min.pid;
  if(min.wt+10<maxProcesses){
    heap_insert(nxt,min.wt+10);
  }
  else{
    heap_insert(nxt,maxProcesses);
  }
  memcpy( &pcb[ pid ].ctx, ctx, sizeof( ctx_t ) );
  memcpy( ctx, &pcb[ nxt ].ctx, sizeof( ctx_t ) );
  current = &pcb[ nxt ];
}

void scheduler(ctx_t* ctx){
  switch (schedType){
    case 0:
      rrScheduler(ctx);
      break;
    case 1:
      prScheduler(ctx);
      break;
    default:
      rrScheduler(ctx);
      break;
  }

}

void blockProc(int pid){
  heap_remove(pid);
  pcb[ pid ].block = 1;
}

void unblockProc(int pid){
  heap_insert(pid,50);
  pcb[ pid ].block = 0;
}

void kernel_handler_rst( ctx_t* ctx              ) {
  /* Initialise PCBs representing processes stemming from execution of
   * the two user programs.  Note in each case that
   *
   * - the CPSR value of 0x50 means the processor is switched into USR
   *   mode, with IRQ interrupts enabled, and
   * - the PC and SP values matche the entry point and top of stack.
   */

  for(uint32_t i=0;i<=lastPindex;i++){
    next[ i ] = heapSize;
    heap[ i ].wt  = heapSize;
    heap[ i ].pid = heapSize;
  }
  heap[ maxProcesses ].wt  = heapSize;
  heap[ maxProcesses ].pid = heapSize;

  memset( &pcb[ 0 ], 0, sizeof( pcb_t ) );
  pcb[ 0 ].pid      = 0;
  pcb[ 0 ].ctx.cpsr = 0x50;
  pcb[ 0 ].ctx.pc   = ( uint32_t )( entry_Sh );
  pcb[ 0 ].ctx.sp   = ( uint32_t )(  &tos_Sh );
  entry[ 0 ].pc     = ( uint32_t )( entry_Sh );
  entry[ 0 ].active = 1;
  next[ 0 ]         = 1;

  memset( &pcb[ 1 ], 0, sizeof( pcb_t ) );
  pcb[ 1 ].pid      = 1;
  pcb[ 1 ].ctx.cpsr = 0x50;
  pcb[ 1 ].ctx.pc   = ( uint32_t )( entry_P0 );
  pcb[ 1 ].ctx.sp   = ( uint32_t )(  &tos_P0 );
  entry[ 1 ].pc     = ( uint32_t )( entry_P0 );
  entry[ 1 ].active = 1;
  next[ 1 ]         = 2;

  memset( &pcb[ 2 ], 0, sizeof( pcb_t ) );
  pcb[ 2 ].pid      = 2;
  pcb[ 2 ].ctx.cpsr = 0x50;
  pcb[ 2 ].ctx.pc   = ( uint32_t )( entry_P1 );
  pcb[ 2 ].ctx.sp   = ( uint32_t )(  &tos_P1 );
  entry[ 2 ].pc     = ( uint32_t )( entry_P1 );
  entry[ 2 ].active = 1;
  next[ 2 ]         = 3;

  memset( &pcb[ 3 ], 0, sizeof( pcb_t ) );
  pcb[ 3 ].pid      = 3;
  pcb[ 3 ].ctx.cpsr = 0x50;
  pcb[ 3 ].ctx.pc   = ( uint32_t )( entry_P2 );
  pcb[ 3 ].ctx.sp   = ( uint32_t )(  &tos_P2 );
  entry[ 3 ].pc     = ( uint32_t )( entry_P2 );
  entry[ 3 ].active = 1;
  next[ 3 ]         = 0;

  memset( &pcb[ 4 ], 0, sizeof( pcb_t ) );
  pcb[ 4 ].pid      = 4;
  pcb[ 4 ].ctx.cpsr = 0x50;
  pcb[ 4 ].ctx.pc   = ( uint32_t )( entry_Aristotle );
  pcb[ 4 ].ctx.sp   = ( uint32_t )(  &tos_Aristotle );
  entry[ 4 ].pc     = ( uint32_t )( entry_Aristotle );
  entry[ 4 ].active = 1;
  next[ 4 ]         = 0;

  memset( &pcb[ 5 ], 0, sizeof( pcb_t ) );
  pcb[ 5 ].pid      = 5;
  pcb[ 5 ].ctx.cpsr = 0x50;
  pcb[ 5 ].ctx.pc   = ( uint32_t )( entry_Confucius );
  pcb[ 5 ].ctx.sp   = ( uint32_t )(  &tos_Confucius );
  entry[ 5 ].pc     = ( uint32_t )( entry_Confucius );
  entry[ 5 ].active = 1;
  next[ 5 ]         = 0;

  memset( &pcb[ 6 ], 0, sizeof( pcb_t ) );
  pcb[ 6 ].pid      = 6;
  pcb[ 6 ].ctx.cpsr = 0x50;
  pcb[ 6 ].ctx.pc   = ( uint32_t )( entry_Descartes );
  pcb[ 6 ].ctx.sp   = ( uint32_t )(  &tos_Descartes );
  entry[ 6 ].pc     = ( uint32_t )( entry_Descartes );
  entry[ 6 ].active = 1;
  next[ 6 ]         = 0;

  memset( &pcb[ 7 ], 0, sizeof( pcb_t ) );
  pcb[ 7 ].pid      = 7;
  pcb[ 7 ].ctx.cpsr = 0x50;
  pcb[ 7 ].ctx.pc   = ( uint32_t )( entry_Socrates );
  pcb[ 7 ].ctx.sp   = ( uint32_t )(  &tos_Socrates );
  entry[ 7 ].pc     = ( uint32_t )( entry_Socrates );
  entry[ 7 ].active = 1;
  next[ 7 ]         = 0;

  memset( &pcb[ 8 ], 0, sizeof( pcb_t ) );
  pcb[ 8 ].pid      = 8;
  pcb[ 8 ].ctx.cpsr = 0x50;
  pcb[ 8 ].ctx.pc   = ( uint32_t )( entry_Voltaire );
  pcb[ 8 ].ctx.sp   = ( uint32_t )(  &tos_Voltaire );
  entry[ 8 ].pc     = ( uint32_t )( entry_Voltaire );
  entry[ 8 ].active = 1;
  next[ 8 ]         = 0;

  memset( &pcb[ 9 ], 0, sizeof( pcb_t ) );
  pcb[ 9 ].pid      = 9;
  pcb[ 9 ].ctx.cpsr = 0x50;
  pcb[ 9 ].ctx.pc   = ( uint32_t )( entry_DiskTest );
  pcb[ 9 ].ctx.sp   = ( uint32_t )(  &tos_DiskTest );
  entry[ 9 ].pc     = ( uint32_t )( entry_DiskTest );
  entry[ 9 ].active = 1;
  next[ 9 ]         = 9;

  switch(schedType){
    case 2: {
      heap_insert(4,30);
      heap_insert(5,30);
      heap_insert(6,30);
      heap_insert(7,30);
      heap_insert(8,30);
      next[ 4 ] = 5;
      next[ 5 ] = 6;
      next[ 6 ] = 7;
      next[ 7 ] = 8;
      next[ 8 ] = 4;
      current = &pcb[ 4 ]; memcpy( ctx, &current->ctx, sizeof( ctx_t ) );
      break;
    }
    case 3: {
      for(uint32_t index=0;index<inodeSize;index++){
        uint8_t block[16];
        disk_rd(index,block,16);
        if(block[0] != 0){
          uint8_t fd;
          char name[8];
          uint8_t active;
          uint8_t blockIndex;
          uint8_t blockLine;
          uint8_t lineChar;

          fileList[index].fd     = index+100;
          fileList[index].active = 1;
          fileList[index].open = 0;
          for(int k=0; k<8; k++){
            fileList[index].blocks[k] = block[k];
          }
          int j;
          for(j=8; j<15 && (char) block[j]!='\0'; j++){
            fileList[index].name[j-8] = (char) block[j];
          }
          fileList[index].name[j-8] = '\0';
          fileList[index].blockIndex = 0;
          fileList[index].blockLine = 0;
          fileList[index].lineChar = 0;

          for(int i=0; i<8; i++){
            if(block[i] != 0){
              used[block[i]] = 1;
            }
          }
        }
      }
      current = &pcb[ 9 ]; memcpy( ctx, &current->ctx, sizeof( ctx_t ) );
      break;
    }
    default: {
      heap_insert(0,5);
      heap_insert(1,50);
      heap_insert(2,20);
      heap_insert(3,30);
      current = &pcb[ 0 ]; memcpy( ctx, &current->ctx, sizeof( ctx_t ) );
      break;
    }
  }
  /* Once the PCBs are initialised, we (arbitrarily) select one to be
   * restored (i.e., executed) when the function then returns.
   */

  nAP = 10;
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
    scheduler(ctx);
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
    case 0x00 : { // ps()
      int* procs = (int *)ctx->gpr[ 0 ];
      for(int i = 0; i<= lastPindex ; i++){
        if(entry[i].active == 1){
          procs[i]=1;
        }
      }
      break;
    }

    case 0x01 : { // write( fd, x, n )
      uint32_t   fd = ( uint32_t   )( ctx->gpr[ 0 ] );
      char*  x      = ( char* )( ctx->gpr[ 1 ] );
      uint32_t    n = ( uint32_t   )( ctx->gpr[ 2 ] );

      if( fd == 0 ){
        for( uint32_t i = 0; i < n; i++ ) {
          PL011_putc( UART0, *x++ );
        }
        ctx->gpr[ 0 ] = n;
        break;
      }

    }


    case 0x02: { // read(fd, x, n )
      uint32_t    fd = ( uint32_t   )( ctx->gpr[ 0 ] );
      char*  x       = ( char* )( ctx->gpr[ 1 ] );
      uint32_t    n  = ( uint32_t   )( ctx->gpr[ 2 ] );

      if( fd == 0 ){
        for( uint32_t i=0; i < n; i++){
          x[i] = PL011_getc( UART0 );
        }
      }

      break;
    }


    case 0x03: { // readLine(fd, x)
      uint32_t    fd = ( uint32_t   )( ctx->gpr[ 0 ] );
      char*  x       = ( char* )( ctx->gpr[ 1 ] );
      uint32_t     n = 0;
      char y;

      if( fd == 0 ){
        while(1){
          char y = PL011_getc( UART0 );
          if( y==13){
            x[n] = '\0';
            PL011_putc( UART0, '\n');
            break;
          }
          x[n] = y;
          PL011_putc( UART0, y);
          n++;
        }

        ctx->gpr[ 0 ] = n;
        break;
      }
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

      if(n<maxProcesses){

        nDCP++;
        memset( &pcb[ n ], 0, sizeof( pcb_t ) );
        pcb[ n ].pid      = n;
        pcb[ n ].ctx.sp   = (nDCP)*4096 + ((uint32_t)&boh);
        pcb[ n ].ctx.cpsr = 0x50;
        pcb[ n ].ctx.pc   = entry[ pid ].pc;
        heap_insert(n,wt);
        entry[ n ].pc     = pcb[ n ].ctx.pc;
        entry[ n ].active = 1;
        nAP++;
        for(uint32_t i = 0; i <= lastPindex; i++){
          if(next[ i ] == 0){
            next[ i ] = n;
            next[ n ] = 0;
          }
        }
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
      for(uint32_t i =0; i <= lastPindex; i++){
        if(next[ i ] == pid){
          next[ i ] = next[ pid ];
          next[ pid ] = heapSize;
          heap_remove(pid);
          break;
        }
      }
      nAP--;
      ctx->gpr[ 0 ] = pid;
      break;
    }


    case 0x06: {  //int makeChan(int pidWrite,int pidRead);
      if(nChans>=maxProcesses){
        break;
      }
      int pidWrite = (int   ) ctx->gpr[ 0 ];
      int pidRead  = (int   ) ctx->gpr[ 1 ];
      for(int i=0;i<=lastPindex;i++){
        if(channels[i].active == 1 && channels[i].writeID == pidWrite && channels[i].readID == pidRead){
          ctx->gpr[ 0 ] = i;
          return;
        }
      }
      chan_t channel;
      int i = 0;
      channel.readID  = pidRead;
      channel.writeID = pidWrite;
      channel.active  = 1;
      channel.ready   = 0;
      for(i=0;i<=lastPindex;i++){
        if(channels[i].active == 0){
          channels[i] = channel;
          nChans++;
          break;
        }
      }
      ctx->gpr[ 0 ] = i;

      break;
    }


    case 0x07: {  //int writeChan(int id,void* value);
      int cid        = (int    ) ctx->gpr[ 0 ];
      void* value    = (void*  ) ctx->gpr[ 1 ];
      if(channels[cid].active == 0){
        ctx->gpr[ 0 ] = 0;
        break;
      }
      channels[ cid ].chan  = value;
      int blockID = channels[ cid ].writeID;
      int unblockID = channels[ cid ].readID;
      channels[ cid ].ready = 1;
      blockProc(blockID);
      unblockProc(unblockID);
      scheduler(ctx);
      ctx->gpr[ 0 ] = 1;
      break;
    }


    case 0x08: {  //void* readChan(int id);
      int cid        = (int   ) ctx->gpr[ 0 ];
      void * toReturn;
      if(channels[cid].active == 0){
        toReturn = NULL;
        ctx->gpr[ 0 ] = (uint32_t) (toReturn);
        break;
      }
      toReturn = channels[ cid ].chan;
      ctx->gpr[ 0 ]  = (uint32_t) (toReturn);
      int unblockID = channels[ cid ].writeID;
      int blockID = channels[ cid ].readID;
      channels[ cid ].ready = 0;
      blockProc(blockID);
      unblockProc(unblockID);
      scheduler(ctx);
      break;
    }


    case 0x09: { //int blockChan(int id);
      int cid        = (int   ) ctx->gpr[ 0 ];
      void* toReturn = channels[ cid ].chan;
      if(channels[ cid ].ready == 0){
        int unblockID = channels[ cid ].writeID;
        int blockID = channels[ cid ].readID;
        blockProc(blockID);
        unblockProc(unblockID);
        scheduler(ctx);
        ctx->gpr[0] = 1;
        break;
      }
      ctx->gpr[0] = 0;
      break;
    }


    case 0x0a: {  //int closeChan(int id);
      int cid = (int) ctx->gpr[ 0 ];
      if(channels[ cid ].active == 1){
        channels[cid].active = 0;
        ctx->gpr[ 0 ] = 1;
      }
      else{
        ctx->gpr[ 0 ] = 0;
      }
      break;
    }


    case 0x0b: {  //uint32_t creat(char* name);
      char* name = (char *) ctx->gpr[ 0 ];
      uint8_t ok = 0;
      uint8_t block[16];
      int i=0;
      uint32_t index = 0;
      for (index = 0; index<inodeSize; index++){
        if(fileList[index].active==0){
          ok=1;
          fileList[index].active = 1;
          fileList[index].open = 0;
          fileList[index].fd = index+100;
          strcpy(fileList[index].name,name);
          fileList[index].blockIndex=0;
          fileList[index].blockLine=0;
          fileList[index].lineChar=0;
          break;
        }
      }
      if( ok == 1 ){
        for(i=1; i<subBlockNo;i++){
          if(used[i]==0){
            used[i] = 1;
            fileList[index].blocks[0] = i;
            ok = 0;
            break;
          }
        }
        if(ok==0){
          for(int j = 0; j<16; j++)
            block[j] = 0;
          block[0] = i;
          for(i = 8; i < 15 && name[i-8]!='\0'; i++){
            block[i] = (uint8_t) name[i-8];
          }
          block[15] = (uint8_t) '\0';
          disk_wr(index,block,16);
          ctx->gpr[0] = 1;
          break;
        }
      }
      ctx->gpr[0] = 0;
      break;
    }

    case 0x0c:{ //int unlink(char* name)
      char* name = (char *) ctx->gpr[0];
      for(int i = 0; i<inodeSize;i++){
        if(strcmp(name,fileList[i].name) == 0){
            uint8_t block[16];
            memset( block, 0, 16*sizeof( uint8_t) );
            disk_wr(i,block,16);
            fileList[i].active = 0;
            ctx->gpr[0] = 1;
            return;
        }
      }
      ctx->gpr[0] = 0;
      break;
    }

    case 0x0d:{  //int open(char* name,int mode);
      char* name = (char *) ctx->gpr[0];
      for(int i = 0; i<inodeSize;i++){
        if(strcmp(name,fileList[i].name) == 0){
          fileList[i].open = (uint8_t) ctx->gpr[0];
          ctx->gpr[0] = (int)fileList[i].fd;
          return;
        }
      }
      ctx->gpr[0] = 0;
      break;
    }

    case 0x0e:{ //int close(char* name);
      char* name = (char *) ctx->gpr[0];
      for(int i=0;i<inodeSize;i++){
        if(strcmp(name,fileList[i].name) == 0){
          fileList[i].open = 0;
          ctx->gpr[0] = 1;
          return;
        }
      }
      ctx->gpr[0] = 0;
      break;
    }
    default: {
      break;
    }
  }

  return;
}
