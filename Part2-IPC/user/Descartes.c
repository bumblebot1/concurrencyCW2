#include "Descartes.h"

void Descartes() {
  int a = makeChan(2,3);//right
  int b = makeChan(3,2);
  int c = makeChan(2,1);//left
  int d = makeChan(1,2);
  int x = 0;
  while(1){
    printf("Descartes eating\n");
    writeChan(a,(void*)1);
    writeChan(c,(void*)1);
    printf("Descartes Thinking\n");
    x = (int) readChan(d);
    x = (int) readChan(b);
  }
}

void (*entry_Descartes)() = &Descartes;
