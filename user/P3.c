#include "P3.h"

void P3() {
  int i = makeChan(4,5);
  int j = makeChan(5,4);
  while(1){
    writeChan(i,"hello\n");
    writeChan(i," Bye\n");
    char* res = (char*)readChan(j);
    printf(res);
  }

}

void (*entry_P3)() = &P3;
