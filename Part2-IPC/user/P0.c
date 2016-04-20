#include "P0.h"

void P0() {
  int a = makeChan(0,1);//right
  int t = 0;
  void* send;
  int k1 = 11;
  int k2 = 24;
  int k3 = 389;
  int k4 = 231;
  int k5 = 39;
  send = &k1;
  writeChan(a,send);
  send = &k2;
  writeChan(a,send);
  send = &k3;
  writeChan(a,send);
  send = &k4;
  writeChan(a,send);
  send = &k5;
  writeChan(a,send);
  while(1){}
}

void (*entry_P0)() = &P0;
