#include "Descartes.h"

void Descartes() {
  int a = makeChan(2,3);//right
  int b = makeChan(3,2);
  int c = makeChan(2,1);//left
  int d = makeChan(1,2);
  int x = 5;
  int y = 6;
  int t = 0;
  int z = 0;
  void* send;
  while(1){
    printf("Descartes eating %d %d\n",t,z);
    send = &x;
    writeChan(a,send);
    send = &y;
    writeChan(c,send);
    printf("Descartes Thinking\n");
    t = *((int*) readChan(b));
    z = *((int*) readChan(d));
  }
}

void (*entry_Descartes)() = &Descartes;
