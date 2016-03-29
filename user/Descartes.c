#include "Descartes.h"

void Descartes() {
  int a = makeChan(6,7);//right
  int b = makeChan(7,6);
  int c = makeChan(6,5);//left
  int d = makeChan(5,6);
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
