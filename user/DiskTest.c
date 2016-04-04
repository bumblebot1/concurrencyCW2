#include "DiskTest.h"

void DiskTest() {
  int x=open("naruto",5);
  printf("created fine!%d\n",x);
  x=close(102);
  printf("created fine!%d\n",x);
  if(x==1){

  }
  while( 1 ) {
  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
