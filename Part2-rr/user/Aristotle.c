#include "Aristotle.h"

void Aristotle() {
  int a = makeChan(4,5);//right
  int b = makeChan(5,4);
  int c = makeChan(4,8);//left
  int d = makeChan(8,4);
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
