#include "Voltaire.h"

void Voltaire() {
  int a = makeChan(8,4);//right
  int b = makeChan(4,8);
  int c = makeChan(8,7);//left
  int d = makeChan(7,8);
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
