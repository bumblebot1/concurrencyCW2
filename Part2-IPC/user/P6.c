#include "P6.h"

void P6() {
  int a = makeChan(5,6);//left
  int t = 0;
  void* send;
  int next   = 0;
  for(int i=0;i<5;i++){
    next = *((int *) readChan(a));
    printf("%d\n",next);
  }
  while(1){}
}

void (*entry_P6)() = &P6;
