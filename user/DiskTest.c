#include "DiskTest.h"

void DiskTest() {
  int x;
  /*creat("test");
  creat("fail");*/
  int fd =open("test",O_RD);
  char y[4098];
  x = read(fd,y,4098);
  y[x] = '\0';
  printf("Finish %d\n",x );
  printf(y);
  while( 1 ) {
  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
