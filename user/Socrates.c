#include "Socrates.h"

void Socrates() {
  int a = makeChan(7,8);//right
  int b = makeChan(8,7);
  int c = makeChan(7,6);//left
  int d = makeChan(6,7);
  int x = 0;
  while(1){
    x = (int) readChan(d);
    printf("Socrates eating\n");
    writeChan(a,(void*)1);
    writeChan(c,(void*)1);
    printf("Socrates Thinking\n");
    x = (int) readChan(b);
  }
}

void (*entry_Socrates)() = &Socrates;
