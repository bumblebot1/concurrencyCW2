#include "Descartes.h"

void Descartes() {
  int a = makeChan(6,7);//right
  int b = makeChan(7,6);
  int c = makeChan(6,5);//left
  int d = makeChan(5,6);
  int x = 0;
  while(1){
    x = (int) readChan(a);
    x = (int) readChan(c);
    printf("Descartes Eating\n");
    writeChan(b,(void*)1);
    writeChan(d,(void*)1);
    printf("Descartes Thinking\n");
    printf("Descartes Hungry\n");
  }
}

void (*entry_Descartes)() = &Descartes;
