#include "P4.h"

void P4() {
  int a = makeChan(3,4);//left
  int t = 0;
  void* send;
  int next   = 0;
  for(int i=0;i<3;i++){
    next = *((int *) readChan(a));
    printf("%d\n",next);
  }
  while(1){}
}

void (*entry_P4)() = &P4;
