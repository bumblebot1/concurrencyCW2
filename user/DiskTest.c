#include "DiskTest.h"

void DiskTest() {
  uint32_t x = creat("naruto");
  printf("created fine!%d",x);
  if(x==1){

  }
  while( 1 ) {
  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
