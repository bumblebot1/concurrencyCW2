#include "libc.h"
#include "stdarg.h"

void ps(){
  int procs[1000];
  for(int i=0;i<1000;i++){
    procs[i] = 0;
  }
  int r;
  asm volatile( "mov r0, %1 \n"
                "svc 0      \n"
                "mov %0, r0\n"
              : "=r" (r)
              : "r" (procs)
              : "r0");

  for(int j=0;j<1000;j++){
    if( procs[j] == 1)
      printf("Process with id %d is running\n",j);
  }
}

int write( int fd, void* x, int n ) {
  int r;

  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "mov r3, %3 \n"
                "svc #1     \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (fd), "r" (x), "r" (n)
              : "r0", "r1" );

  return r;
}

char* intToString(int x,char* toReturn,int* len){
  int n=0;
  char f[12];
  int j=0;
  if(x<=9&&x>=0){
    toReturn[0]=itox(x);
    *len=1;
    return toReturn;
  }
  if(x<0){
    x=-1*x;
    j=1;
    n=1;
  }
  while(x!=0){
    int a=x%10;
    x=x/10;
    f[n]=itox(a);
    n++;
  }
  if(j==1){
    toReturn[0]='-';
  }
  for(int i=n-1;i>=0;i--){
    toReturn[j++]=f[i];
  }
  *len=j;
  return toReturn;
}

void printf(char* str,...){
  char* x;
  unsigned int i;
  char* s;

  va_list arg;
  va_start(arg,str);

  int j;
  int n=0;

  for(j=0;x[j]!='\0';j++){
    if(n!='%')
      n++;
    else
      n=n+12;
  }

  n++;
  j=0;

  char toWrite[n+1];
  for(x=str;*x!='\0';x++){
    while( *x !='%'&& *x!='\0'){
      toWrite[j++]=*x;
      x++;
    }
    if(*x=='\0'){
      toWrite[j++]=*x;
      break;
    }
    x++;
    switch(*x){
      case 'd' : i = va_arg(arg,int);
                 char f[12];
                 intToString(i,f,&n);
                 for(int i=0;i<n;i++){
                  toWrite[j++]=f[i];
                 }
                 break;
    }
  }
  va_end(arg);

  write(0,toWrite,j);
}

int read( int fd, void* x, size_t n ){
  int r;

  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "mov r2, %3 \n"
                "svc #2     \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (fd), "r" (x), "r" (n)
              : "r0", "r1", "r2" );

  return r;
}

int readLine(int fd, void* x){
  int r;

  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "svc #3     \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (fd), "r" (x)
              : "r0", "r1");
  return r;

}

int fork(int pid,uint32_t wt){
  int r;

  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "svc #4     \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (pid), "r"(wt)
              : "r0");
  return r;
}

int exit(int pid){
  int r;

  asm volatile( "mov r0, %1 \n"
                "svc #5    \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (pid)
              : "r0");

  return r;
}

int makeChan(int pidWrite,int pidRead){
  int r;
  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "svc #6     \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (pidWrite), "r" (pidRead)
              : "r0");
  return r;
}

int writeChan(int id,void* value){
  int r;

  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "svc #7     \n"
              : "=r" (r)
              : "r" (id), "r" (value));

  return r;
}

int blockChan(int id){
  int r;

  asm volatile( "mov r0, %1 \n"
                "svc #9    \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (id)
              : "r0");

  return r;
}

void* readChan(int id){
  void* r;
  while(blockChan(id)){

  }

  asm volatile( "mov r0, %1 \n"
                "svc #8     \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (id)
              : "r0");

  return r;
}

int closeChan(int id){
  int r;

  asm volatile( "mov r0, %1 \n"
                "svc #10    \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (id)
              : "r0" );

  return r;
}

int creat(char* name){
  int r;

  asm volatile( "mov r0, %1 \n"
                "svc #11    \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (name)
              : "r0" );

  return r;
}

int unlink(char* name){
  int r;

  asm volatile( "mov r0, %1 \n"
                "svc #12    \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (name)
              : "r0" );

  return r;
}

int open(char* name,open_t mode){
  int r;

  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "svc #13    \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (name), "r" (mode)
              : "r0" );

  return r;
}

int close(int fd){
  int r;
  asm volatile( "mov r0, %1 \n"
                "svc #14    \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (fd)
              : "r0" );

  return r;
}
