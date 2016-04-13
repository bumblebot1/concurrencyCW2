#include "DiskTest.h"

void DiskTest() {
  int x;
  /*creat("test");
  creat("fail");*/
  char* t = "gibsonasldsladlasd";
  int fd;// =open("test",O_RD);
  /*x = read(fd,y,4098);
  y[x] = '\0';
  printf("Finish %d\n",x );
  printf(y);*/
  printf("%d This is from the first opening process\n",fd);
  while( 1 ) {
  }

  return;;
}

void (*entry_DiskTest)() = &DiskTest;
