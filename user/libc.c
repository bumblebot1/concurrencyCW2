#include "libc.h"
#include "stdarg.h"

int writeChar( int fd, char x ) {
  int r;

  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "svc #1     \n"
                "mov %0, r0 \n" 
              : "=r" (r) 
              : "r" (fd), "r" (x)
              : "r0", "r1" );

  return r;
}

int writeInt(int fd, int x){
  int r;

  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "svc #2     \n"
                "mov %0, r0 \n" 
              : "=r" (r) 
              : "r" (fd), "r" (x)
              : "r0", "r1");
  return r;
}

void printf(char* str,...){
  char* x;
  unsigned int i;
  char* s;
  
  va_list arg;
  va_start(arg,str);
  
  int j;
  
  for(x=str;*x!='\0';x++){
    while( *x !='%'&& *x!='\0'){
      writeChar(0,*x);
      x++;
    }
    if(*x=='\0')
      break;
    x++;
    switch(*x){
      case 'd' : i = va_arg(arg,int);
                 writeInt(0,i);
                 break;
    }
  }
  
  va_end(arg);
}


int read( int fd, void* x, size_t n ){
  int r;
  
  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "mov r2, %3 \n"
                "svc #3     \n"
                "mov %0, r0 \n" 
              : "=r" (r) 
              : "r" (fd), "r" (x), "r" (n) 
              : "r0", "r1", "r2" );

  return r;
  
}
