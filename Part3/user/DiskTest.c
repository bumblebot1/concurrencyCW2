#include "DiskTest.h"

void DiskTest() {
  int x;
  /*creat("test");
  creat("fail");*/
  char* t = "gibsonasldsladlasd";
  for(int i=0;i<125;i++)
    unlink("test");
  while(creat("new")!=0){

  }
  int fd =open("test",O_RDWR);
  char y[4098];
  /*x = read(fd,y,4098);
  y[x] = '\0';
  printf("Finish %d\n",x );
  printf(y);*/
  for(int i=0;i<256;i++){
    write(fd,"flightworthiness",16);
  }
  printf("%d\n",write(fd,t,strlen(t)));
  while( 1 ) {
  }

  return;;
}

void (*entry_DiskTest)() = &DiskTest;
