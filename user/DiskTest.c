#include "DiskTest.h"

void DiskTest() {
  int x;
  /*creat("test");
  creat("fail");*/
  int fd =open("test",O_RDWR);
  /*char y[4098];
  x = read(fd,y,4098);
  y[x] = '\0';
  printf("Finish %d\n",x );
  printf(y);*/
  write(fd,"hello",5);
  lseek(fd,15,SEEK_END);
  char y[100];
  x = read(fd,y,7);
  y[x]='\0';
  printf("READ ");
  printf(y);
  printf("\n");
  lseek(fd,15,SEEK_START);
  x = read(fd,y,16);
  y[x] = '\0';
  printf(y);
  while( 1 ) {
  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
