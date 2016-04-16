#include "Voltaire.h"

void Voltaire() {
  int a = makeChan(4,0);//right
  int b = makeChan(0,4);
  int c = makeChan(4,3);//left
  int d = makeChan(3,4);
  int x = 9;
  int y = 10;
  int t = 0;
  int z = 0;
  void* send;
  while(1){
    printf("Voltaire Thinking\n");
    t = *((int*) readChan(b));
    z = *((int*) readChan(d));
    printf("Voltaire eating %d %d \n",t,z);
    send = &x;
    writeChan(a,send);
    send = &y;
    writeChan(c,send);
  }
}

void (*entry_Voltaire)() = &Voltaire;
