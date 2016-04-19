#include "P0.h"

void P0() {
  int a = makeChan(0,1);//right
  int b = makeChan(1,0);
  int t = 0;
  void* send;
  while(1){
    printf("P0 sending %d\n",t+1);
    t++;
    send = &t;
    writeChan(a,send);
    printf("P0 reading\n");
    t = *((int*) readChan(b));
  }
}

void (*entry_P0)() = &P0;
