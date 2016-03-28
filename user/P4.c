#include "P4.h"

void P4() {
  int i = makeChan(4,5);
  int j = makeChan(5,6);
  while(1){
    writeChan(j,"Sent from P4 to P5\n");
    char* res=(char*)readChan(i);
    printf(res);
  }
}

void (*entry_P4)() = &P4;
