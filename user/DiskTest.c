#include "DiskTest.h"

void DiskTest() {
  int x;
  /*creat("test");
  creat("fail");*/
  int fd =open("test",O_WR);
  char* y = "blues";
  for(int i =0;i<=3;i++){
    x = write(fd,y,strlen(y));
    printf("Result %d\n",x );
  }
  printf("Finish %d\n",x );
  while( 1 ) {
  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
