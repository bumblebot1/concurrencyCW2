#include "Sh.h"

void Sh() {
  char str[1000];
  while( 1 ) {
    int x = read(1,str,3);
    write(0,str,3);
    printf(" %d\n",x);
  }
}

void (*entry_Sh)() = &Sh;
