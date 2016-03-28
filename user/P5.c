#include "P5.h"

void P5() {
  int i = makeChan(5,6);
  int j = makeChan(6,4);
  while(1){
    writeChan(j,"Sent from P5 to P3\n");
    char* res=(char*)readChan(i);
    printf(res);
  }
}

void (*entry_P5)() = &P5;
