#include "DiskTest.h"

void DiskTest() {
  int x;
  /*creat("test");
  creat("fail");*/
  creat("gib");

  int fd=open("gib",5);
  printf("opened fine!%d\n",fd);
  char* y = "alfabetagammapsik";
  printf("%d\n",strlen(y));
  for(int i =0;i<256*8;i++){
    x=write(fd,y,strlen(y));
  }
  printf("Result %d\n",x );
  while( 1 ) {
  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
