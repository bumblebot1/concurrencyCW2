#include "Confucius.h"

void Confucius() {
  int a = makeChan(5,6);//right
  int b = makeChan(6,5);
  int c = makeChan(5,4);//left
  int d = makeChan(4,5);
  int x = 0;
  while(1){
    printf("Confucius Thinking\n");
    x = (int) readChan(d);
    x = (int) readChan(b);
    printf("Confucius eating\n");
    writeChan(a,(void*)1);
    writeChan(c,(void*)1);

  }
}

void (*entry_Confucius)() = &Confucius;
