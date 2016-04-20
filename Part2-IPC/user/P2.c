#include "P2.h"

void P2() {
  int a = makeChan(1,2);//left
  int b = makeChan(2,3);
  int t = 0;
  void* send;
  int val = 0;
  int next   = 0;
  int lowest = *((int*) readChan(a));
  for(int i=0;i<3;i++){
    next = *((int *) readChan(a));
    if(next>=lowest){
      val = next;
      send = &val;
    }
    else{
      val = lowest;
      lowest = next;
      send = &val;
    }
    writeChan(b,send);
  }
  int valfin = lowest;
  send = &valfin;
  writeChan(b,send);
  while(1){}
}

void (*entry_P2)() = &P2;
