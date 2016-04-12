#include "Socrates.h"

void Socrates() {
  int a = makeChan(3,4);//right
  int b = makeChan(4,3);
  int c = makeChan(3,2);//left
  int d = makeChan(2,3);
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
