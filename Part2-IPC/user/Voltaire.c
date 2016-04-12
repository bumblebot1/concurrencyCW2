#include "Voltaire.h"

void Voltaire() {
  int a = makeChan(4,0);//right
  int b = makeChan(0,4);
  int c = makeChan(4,3);//left
  int d = makeChan(3,4);
  int x = 0;
  while(1){
    printf("Voltaire Thinking\n");
    x = (int) readChan(b);
    x = (int) readChan(d);
    printf("Voltaire eating\n");
    writeChan(a,(void*)1);
    writeChan(c,(void*)1);
  }
}

void (*entry_Voltaire)() = &Voltaire;
