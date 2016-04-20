#include "P5.h"

void P5() {
  int a = makeChan(4,5);//left
  int t = 0;
  void* send;
  int next   = 0;
  for(int i=0;i<4;i++){
    next = *((int *) readChan(a));
    printf("%d\n",next);
  }
  while(1){}
}

void (*entry_P5)() = &P5;
