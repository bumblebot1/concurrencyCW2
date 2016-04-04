#include "DiskTest.h"

void DiskTest() {
  int x;
  x= creat("naruto");
  unlink("naruto");
  x= creat("gib");
  x=creat("test");
  x=open("gib",5);
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
