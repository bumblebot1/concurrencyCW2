#include "Confucius.h"

void Confucius() {
  int a = makeChan(5,6);//right
  int b = makeChan(6,5);
  int c = makeChan(5,4);//left
  int d = makeChan(4,5);
  int x = 0;
  while(1){
    x = (int) readChan(a);
    x = (int) readChan(c);
    printf("Confucius Eating\n");
    writeChan(b,(void*)1);
    writeChan(d,(void*)1);
    printf("Confucius Thinking\n");
    printf("Confucius Hungry\n");
  }
}

void (*entry_Confucius)() = &Confucius;
