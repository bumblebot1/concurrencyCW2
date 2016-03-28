#include "Socrates.h"

void Socrates() {
  int a = makeChan(7,8);//right
  int b = makeChan(8,7);
  int c = makeChan(7,6);//left
  int d = makeChan(6,7);
  int x = 0;
  while(1){
    x = (int) readChan(a);
    x = (int) readChan(c);
    printf("Socrates Eating\n");
    writeChan(b,(void*)1);
    writeChan(d,(void*)1);
    printf("Socrates Thinking\n");
    printf("Socrates Hungry\n");
  }
}

void (*entry_Socrates)() = &Socrates;
