#include "Confucius.h"

void Confucius() {
  int a = makeChan(1,2);//right
  int b = makeChan(2,1);
  int c = makeChan(1,0);//left
  int d = makeChan(0,1);
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
