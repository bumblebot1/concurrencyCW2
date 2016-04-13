#include "ConcDisk.h"

void ConcDisk() {
  /*creat("test");
  creat("fail");*/
  /*x = read(fd,y,4098);
  y[x] = '\0';
  printf("Finish %d\n",x );
  printf(y);*/
  int fd =open("test",O_RD);
  char y[400];
  y[0]='h';
  y[1]='i';
  y[2]='\0';
  y[3]='\n';
  printf(y);
  int x = read(fd,y,5);
  printf("%d This is from the second opening process\n",x);
  printf(y);
  while( 1 ) {
  }

  return;;
}

void (*entry_ConcDisk)() = &ConcDisk;
