#include "P8.h"

void P8() {
  int a = makeChan(7,8);//left
  int t = 0;
  void* send;
  int next   = 0;
  for(int i=0;i<7;i++){
    next = *((int *) readChan(a));
    printf("%d\n",next);
  }
  printf("Pipeline sort finished!\n");
  while(1){}
}

void (*entry_P8)() = &P8;
