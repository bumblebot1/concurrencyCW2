#include "P1.h"

void P1() {
  int a = makeChan(1,0);//left
  int b = makeChan(0,1);
  int t = 0;
  void* send;
  while(1){
    printf("P1 reading\n");
    t = *((int*) readChan(b));
    printf("P1 sending %d\n",t+1);
    t++;
    send = &t;
    writeChan(a,send);
  }
}

void (*entry_P1)() = &P1;
