#include "P11.h"

void P11() {
  int a = makeChan(10,11);//left
  int t = 0;
  void* send;
  int next   = 0;
  for(int i=0;i<10;i++){
    next = *((int *) readChan(a));
    printf("%d\n",next);
  }
  printf("Pipeline sort finished!\n");
  while(1){}
}

void (*entry_P11)() = &P11;
