#include "DiskTest.h"

void DiskTest() {
  int x;
  /*creat("test");
  creat("fail");*/
  int fd =open("test",O_RDWR);
  char y[4098];
  char* test="BAI GYPSANE!";
  /*x = read(fd,y,4098);
  y[x] = '\0';
  printf("Finish %d\n",x );
  printf(y);*/
  write(fd,"hello",5);
  x = lseek(fd,2529,SEEK_R);
  printf("%d\n",x);
  x = write(fd,test,strlen(test));
  printf("%d\n",x);
  x = lseek(fd,strlen(test),SEEK_L);
  x = read(fd,y,strlen(test));
  y[x] = '\0';
  printf(y);
  printf("%d\n",x);
  while( 1 ) {
  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
