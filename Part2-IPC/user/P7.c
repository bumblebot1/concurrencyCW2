#include "P7.h"

void P7() {
  int a = makeChan(6,7);//left
  int t = 0;
  void* send;
  int next   = 0;
  for(int i=0;i<6;i++){
    next = *((int *) readChan(a));
    printf("%d\n",next);
  }
  printf("Pipeline sort finished!\n");
  while(1){}
}

void (*entry_P7)() = &P7;
