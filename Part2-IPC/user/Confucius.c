#include "Confucius.h"

void Confucius() {
  int a = makeChan(1,2);//right
  int b = makeChan(2,1);
  int c = makeChan(1,0);//left
  int d = makeChan(0,1);
  int x = 3;
  int y = 4;
  int t = 0;
  int z = 0;
  void* send;
  while(1){
    printf("Confucius Thinking\n");
    t = *((int*) readChan(b));
    z = *((int*) readChan(d));
    printf("Confucius eating %d %d\n",t,z);
    send = &x;
    writeChan(a,send);
    send = &y;
    writeChan(c,send);
  }
}

void (*entry_Confucius)() = &Confucius;
