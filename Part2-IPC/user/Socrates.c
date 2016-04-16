#include "Socrates.h"

void Socrates() {
  int a = makeChan(3,4);//right
  int b = makeChan(4,3);
  int c = makeChan(3,2);//left
  int d = makeChan(2,3);
  int x = 7;
  int y = 8;
  void* send;
  int t = 0;
  int z = 0;
  while(1){
    t = *((int*) readChan(d));
    printf("Socrates eating %d %d\n",t,z);
    send = &x;
    writeChan(a,send);
    send = &y;
    writeChan(c,send);
    printf("Socrates Thinking\n");
    z = *((int*) readChan(b));
  }
}

void (*entry_Socrates)() = &Socrates;
