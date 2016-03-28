#include "P4.h"

void P4() {
  int i = makeChan(4,5);
  while(1){
    char* res=(char*)readChan(i);
    printf(res);
    res=(char*)readChan(i);
    printf(res);
  }
}

void (*entry_P4)() = &P4;
