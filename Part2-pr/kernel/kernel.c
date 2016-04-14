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
uint8_t schedType = 1;
uint8_t used[subBlockSize]; //disk subblock used/unused
file_t fileList[inodeSize];

int writeFile(int id,char* x,int n);
int readFile(int id,char* x,int n);
int leftSeek(int index,int offset);
int rightSeek(int index,int offset);

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

  heap_insert(0,5);
  heap_insert(1,70);
  heap_insert(2,60);
  heap_insert(3,40);
  current = &pcb[ 0 ]; memcpy( ctx, &current->ctx, sizeof( ctx_t ) );
  /* Once the PCBs are initialised, we (arbitrarily) select one to be
   * restored (i.e., executed) when the function then returns.
   */

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

      if( fd < 100 ){
        for( uint32_t i = 0; i < n; i++ ) {
          PL011_putc( UART0, *x++ );
        }
        ctx->gpr[ 0 ] = n;
      }
      else{
        //fd is an actual file;
        for(int i=0;i<inodeSize;i++){
          if(fd == fileList[i].fd){
            //do the write logic
            if(fileList[i].open == O_WR || fileList[i].open == O_RDWR)
              ctx->gpr[0] = writeFile(i,x,n);
            else
              ctx->gpr[0] = 0;
            return;
          }
        }
        ctx->gpr[0] = 0;
      }
      break;
    }


    case 0x02: { // read(fd, x, n )
      uint32_t    fd = ( uint32_t   )( ctx->gpr[ 0 ] );
      char*  x       = ( char* )( ctx->gpr[ 1 ] );
      uint32_t    n  = ( uint32_t   )( ctx->gpr[ 2 ] );

      if( fd < 100 ){
        for( uint32_t i=0; i < n; i++){
          x[i] = PL011_getc( UART0 );
        }
        ctx->gpr[0] = n;
      }
      else{
        //fd is an actual file;
        for(int i=0;i<inodeSize;i++){
          if(fd == fileList[i].fd){
            //do the write logic
            if(fileList[i].open == O_RD || fileList[i].open == O_RDWR)
              ctx->gpr[0] = readFile(i,x,n);
            else
              ctx->gpr[0] = 0;
            return;
          }
        }
        ctx->gpr[0] = 0;
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
          if(y!=127){
            if(y>31 && y<127){
              x[n] = y;
              PL011_putc( UART0, y);
              n++;
            }
          }
          else{
            if(n!=0){
              PL011_putc(UART0,'\b');
              PL011_putc(UART0,' ');
              PL011_putc(UART0,'\b');
              n--;
            }
          }
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
          if(pid == (*current).pid){
            scheduler(ctx);
          }
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
          fileList[index].open = O_CLOSED;
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
            for(int j=0;j<8;j++){
              used[fileList[i].blocks[j]] = 0;
            }
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
      open_t mode = (open_t) ctx->gpr[1];
      if(mode == O_CLOSED){
        ctx->gpr[0] = 0;
        return;
      }
      for(int i = 0; i<inodeSize;i++){
        if(strcmp(name,fileList[i].name) == 0){
          fileList[i].open = (open_t) ctx->gpr[1];
          ctx->gpr[0] = (int)fileList[i].fd;
          return;
        }
      }
      ctx->gpr[0] = 0;
      break;
    }

    case 0x0e:{ //int close(int fd);
      int fd = (int) ctx->gpr[0];
      for(int i=0;i<inodeSize;i++){
        if( fd == fileList[i].fd && fileList[i].open != O_CLOSED){
          fileList[i].open = O_CLOSED;
          ctx->gpr[0] = 1;
          return;
        }
      }
      ctx->gpr[0] = 0;
      break;
    }
    case 0x0f:{ //int lseek(int fd);
      int fd = (int) ctx->gpr[0];
      int offset = (int) ctx->gpr[1];
      seek_t mode = ctx->gpr[2];
      int fileIndex = 0;
      for(int i=0;i<inodeSize;i++){
        if(fd == fileList[i].fd){
          //check file is actually open
          if(fileList[i].open != O_CLOSED)
            fileIndex = i;
          else{
            ctx->gpr[0] = 0;
            return;
          }
        }
      }

      switch(mode){
        case SEEK_L:{
          ctx->gpr[0] = leftSeek(fileIndex,offset);
          break;
        }
        case SEEK_R:{
          ctx->gpr[0] = rightSeek(fileIndex,offset);
          break;
        }
        case SEEK_END:{
          int j = 0;
          for(j=0;j<8;j++){
            if(fileList[fileIndex].blocks[j] == 0){
              break;
            }
          }
          if(j!=0){
            fileList[fileIndex].blockIndex = j-1;
          }
          else{
            fileList[fileIndex].blockIndex = 0;
          }
          fileList[fileIndex].blockLine  = 255;
          fileList[fileIndex].lineChar   = 15;
          break;
        }
        case SEEK_START:{
          fileList[fileIndex].blockIndex = 0;
          fileList[fileIndex].blockLine  = 0;
          fileList[fileIndex].lineChar   = 0;
          break;
        }
        default:{
          ctx->gpr[0] = 0;
          break;
        }
      }
      break;
    }

    default: {
      break;
    }
  }
  return;
}

int leftSeek(int index,int offset){
  int k=0; //no of positions moved in the file.
  while(offset!=0){
    int lineChar   = fileList[index].lineChar;
    int blockLine  = fileList[index].blockLine;
    int blockIndex = fileList[index].blockIndex;
    lineChar = (lineChar-1);
    if(lineChar < 0){
      lineChar = 15;
      blockLine = (blockLine-1);
      if(blockLine < 0){
        blockLine = 255;
        blockIndex = blockIndex-1;
        if(blockIndex < 0){
          //cant move more since file is done
          return k;
        }
        else{
          //you cane move further so do nothing
        }
      }
    }
    offset--;
    k++;
    fileList[index].lineChar   = lineChar;
    fileList[index].blockLine  = blockLine;
    fileList[index].blockIndex = blockIndex;
  }
  return k;
}

int rightSeek(int index,int offset){
  int k=0; //no of positions moved in the file.
  while(offset!=0){
    int lineChar   = fileList[index].lineChar;
    int blockLine  = fileList[index].blockLine;
    int blockIndex = fileList[index].blockIndex;
    lineChar = (lineChar+1)%16;
    if(lineChar == 0){
      blockLine = (blockLine+1)%256;
      if(blockLine == 0){
        blockIndex = blockIndex+1;
        if(blockIndex >=8 || fileList[index].blocks[blockIndex] == 0){
          //cant move more since file is done
          return k;
        }
        else{
          //you cane move further so do nothing
        }
      }
    }
    offset--;
    k++;
    fileList[index].lineChar   = lineChar;
    fileList[index].blockLine  = blockLine;
    fileList[index].blockIndex = blockIndex;
  }
  return k;
}

int writeFile(int id,char* x,int n){ //id=index of file in list
  file_t file = fileList[id];
  uint8_t* blocks     = file.blocks;
  uint32_t blockIndex = (uint32_t)file.blockIndex;
  uint32_t blockLine  = (uint32_t)file.blockLine;
  uint32_t lineChar   = (uint32_t)file.lineChar;
  uint32_t block      = blocks[blockIndex];
  uint32_t pointer    = 256*block+blockLine;
  uint8_t toWrite[16];
  uint32_t start = 0;
  disk_rd(pointer,toWrite,16);
  if( lineChar!=0 ){
    do{
      toWrite[lineChar] = (uint8_t) (*x);
      x++;
      lineChar=(lineChar+1)%16;
      start++;
      n--;
    }while(n>0 && lineChar%16!=0);
    disk_wr(pointer,toWrite,16);
    if(lineChar==0){
      blockLine=(blockLine+1)%256;
      if(blockLine==0){
        blockIndex+=1;
        if(blockIndex==8){
          //out of bounds of the file
          return start;
        }
        block = blocks[blockIndex];
        if(block==0){
          //allocate block;
          int ok = 0;
          for(int i=1;i<subBlockNo;i++){
            if(used[i]==0){
              ok = 1;
              block = i;
              blocks[blockIndex] = i;
              used[i] = 1;
              break;
            }
          }
          if(ok==0){
            //no more sub blocks can be allocated
            return start;
          }
          else{
            uint8_t inode[16];
            disk_rd(id,inode,16);
            for(int a=0;a<8;a++){
              inode[a] = fileList[id].blocks[a];
            }
            disk_wr(id,inode,16);
          }
        }
      }
      fileList[id].lineChar   = lineChar;
      fileList[id].blockIndex = blockIndex;
      fileList[id].blockLine  = blockLine;
    }
  }
  if(n!=0){
    while(n/16!=0){
      uint32_t pointer    = 256*block+blockLine;
      disk_rd(pointer,toWrite,16);
      do{
        toWrite[lineChar] = (uint8_t) (*x);
        x++;
        start++;
        lineChar=(lineChar+1)%16;
        n--;
      }while(n>0 && lineChar%16!=0);
      disk_wr(pointer,toWrite,16);
      if(lineChar==0){
        blockLine=(blockLine+1)%256;
        if(blockLine==0){
          blockIndex+=1;
          if(blockIndex==8){
            //out of bounds of the file
            return start;
          }
          block = blocks[blockIndex];
          if(block==0){
            //allocate block;
            int ok = 0;
            for(int i=1;i<subBlockNo;i++){
              if(used[i]==0){
                ok = 1;
                block = i;
                blocks[blockIndex] = i;
                used[i] = 1;
                break;
              }
            }
            if(ok==0){
              //no more sub blocks can be allocated
              return start;
            }
            else{
              uint8_t inode[16];
              disk_rd(id,inode,16);
              for(int a=0;a<8;a++){
                inode[a] = fileList[id].blocks[a];
              }
              disk_wr(id,inode,16);
            }
          }
        }
        fileList[id].lineChar   = lineChar;
        fileList[id].blockIndex = blockIndex;
        fileList[id].blockLine  = blockLine;
      }
    }

    if(n!=0){
      uint32_t pointer    = 256*block+blockLine;
      disk_rd(pointer,toWrite,16);
      while(n>0){
        toWrite[lineChar] = (uint8_t) (*x);
        start++;
        x++;
        lineChar=(lineChar+1)%16;
        n--;
      }
      fileList[id].lineChar = lineChar;
      disk_wr(pointer,toWrite,16);
    }
  }
  else{
    fileList[id].lineChar = lineChar;
  }

  return start;
}


int readFile(int id,char* x,int n){
  file_t file = fileList[id];
  uint8_t* blocks     = file.blocks;
  uint32_t blockIndex = (uint32_t)file.blockIndex;
  uint32_t blockLine  = (uint32_t)file.blockLine;
  uint32_t lineChar   = (uint32_t)file.lineChar;
  uint32_t block      = blocks[blockIndex];
  uint32_t pointer    = 256*block+blockLine;
  uint8_t toWrite[16];
  uint32_t start = 0;
  disk_rd(pointer,toWrite,16);
  if( lineChar!=0 ){
    do{
      x[start] = (char) toWrite[lineChar];
      start++;
      lineChar=(lineChar+1)%16;
      n--;
    }while(n>0 && lineChar%16!=0);
    if(lineChar==0){
      blockLine=(blockLine+1)%256;
      if(blockLine==0){
        blockIndex+=1;
        if(blockIndex==8){
          //out of bounds of the file
          return start;
        }
        block = blocks[blockIndex];
        if(block==0){
          return start;
        }
      }
      fileList[id].lineChar   = lineChar;
      fileList[id].blockIndex = blockIndex;
      fileList[id].blockLine  = blockLine;
    }
  }
  if(n!=0){
    while(n/16!=0){
      uint32_t pointer    = 256*block+blockLine;
      disk_rd(pointer,toWrite,16);
      do{
        x[start] = (char) toWrite[lineChar];
        start++;
        lineChar=(lineChar+1)%16;
        n--;
      }while(n>0 && lineChar%16!=0);
      if(lineChar==0){

        blockLine=(blockLine+1)%256;
        if(blockLine==0){
          blockIndex+=1;
          if(blockIndex==8){
            //out of bounds of the file
            return start;
          }
          block = blocks[blockIndex];
          if(block==0){
            //allocate block;
            return start;
          }
        }
        fileList[id].lineChar   = lineChar;
        fileList[id].blockIndex = blockIndex;
        fileList[id].blockLine  = blockLine;
      }
    }

    if(n!=0){
      uint32_t pointer    = 256*block+blockLine;
      disk_rd(pointer,toWrite,16);
      while(n>0){
        x[start] = (char) toWrite[lineChar];
        start++;
        lineChar=(lineChar+1)%16;
        n--;
      }
      fileList[id].lineChar = lineChar;
    }
  }
  else{
    fileList[id].lineChar = lineChar;
  }

  return start;
}
