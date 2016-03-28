#include "Voltaire.h"

void Voltaire() {
  int a = makeChan(8,4);//right
  int b = makeChan(4,8);
  int c = makeChan(8,7);//left
  int d = makeChan(7,8);
  int x = 0;
  while(1){
    printf("Voltaire Eating\n");
    writeChan(b,(void*)1);
    writeChan(d,(void*)1);
    printf("Voltaire Thinking\n");
    printf("Voltaire Hungry\n");
    x = (int) readChan(a);
    x = (int) readChan(c);
  }
}

void (*entry_Voltaire)() = &Voltaire;
