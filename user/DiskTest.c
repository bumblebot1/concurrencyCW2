#include "DiskTest.h"

void DiskTest() {
  int x;
  /*creat("test");
  creat("fail");
  creat("gib");
*/
  int fd=open("gib",5);
  printf("opened fine!%d\n",fd);
  char* y = "accommodationists";
  printf("%d\n",strlen(y));
  for(int i =0;i<256;i++){
    x=write(fd,y,strlen(y));
  }
  if(x==1){

  }
  while( 1 ) {
  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
