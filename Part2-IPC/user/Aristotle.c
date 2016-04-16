#include "Aristotle.h"

void Aristotle() {
  int a = makeChan(0,1);//right
  int b = makeChan(1,0);
  int c = makeChan(0,4);//left
  int d = makeChan(4,0);
  int x = 1;
  int y = 2;
  int t = 0;
  int z = 0;
  void* send;
  while(1){
    printf("Aristotle eating %d %d\n",t,z);
    send = &x;
    writeChan(a,send);
    send = &y;
    writeChan(c,send);
    printf("Aristotle Thinking\n");
    t = *((int*) readChan(b));
    z = *((int*) readChan(d));
  }
}

void (*entry_Aristotle)() = &Aristotle;
