#include "DiskTest.h"

void DiskTest() {
  int x;
  /*creat("test");
  creat("fail");*/
  int fd =open("test",O_RDWR);
  char y[4098];
  /*x = read(fd,y,4098);
  y[x] = '\0';
  printf("Finish %d\n",x );
  printf(y);*/
  write(fd,"hello",5);
  x = lseek(fd,210000,SEEK_L);
  printf("%d\n",x);
  x = read(fd,y,2);
  y[x] = '\0';
  printf(y);
  printf("%d\n",x);
  while( 1 ) {
  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
