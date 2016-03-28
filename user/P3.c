#include "P3.h"

void P3() {
  int i = makeChan(4,5);
  while(1){
    writeChan(i,"hello\n");
    writeChan(i," Bye\n");
  }

}

void (*entry_P3)() = &P3;
