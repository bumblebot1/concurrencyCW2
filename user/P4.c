#include "P4.h"

void P4() {
  int i = makeChan(4,5);
  int j = makeChan(5,4);
  while(1){
    char* res=(char*)readChan(i);
    printf(res);
    res=(char*)readChan(i);
    printf(res);
    writeChan(j,"Sent from P3\n");

  }
}

void (*entry_P4)() = &P4;
