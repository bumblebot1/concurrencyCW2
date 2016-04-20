#include "P6.h"

void P6() {
  int a = makeChan(5,6);//left
  int b = makeChan(6,7);
  int t = 0;
  void* send;
  int val = 0;
  int next   = 0;
  int lowest = *((int*) readChan(a));
  for(int i=0;i<5;i++){
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

void (*entry_P6)() = &P6;
