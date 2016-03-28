#include "Aristotle.h"

void Aristotle() {
  int a = makeChan(4,5);//right
  int b = makeChan(5,4);
  int e = makeChan(4,8);//left
  int d = makeChan(8,4);
  int x = 0;
  while(1){
    printf("Aristotle Hungry\n");
    x = (int) readChan(e);
    x = (int) readChan(a);
    printf("Aristotle eating\n");
    writeChan(b,(void*)1);
    writeChan(d,(void*)1);
    printf("Aristotle Thinking\n");
  }
}

void (*entry_Aristotle)() = &Aristotle;
