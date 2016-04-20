#include "P0.h"

void P0() {
  int a = makeChan(0,1);//right
  int t = 0;
  void* send;
  int k[10] = {11,24,389,231,39,1239,75,245,37,48};
  for(int i = 0; i<10; i++){
    send = k+i;
    writeChan(a,send);
  }
  while(1){}
}

void (*entry_P0)() = &P0;
