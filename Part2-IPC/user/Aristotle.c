#include "Aristotle.h"

void Aristotle() {
  int a = makeChan(0,1);//right
  int b = makeChan(1,0);
  int c = makeChan(0,4);//left
  int d = makeChan(4,0);
  int x = 0;
  while(1){
    printf("Aristotle eating\n");
    writeChan(a,(void*)1);
    writeChan(c,(void*)1);
    printf("Aristotle Thinking\n");
    x = (int) readChan(d);
    x = (int) readChan(b);
  }
}

void (*entry_Aristotle)() = &Aristotle;
