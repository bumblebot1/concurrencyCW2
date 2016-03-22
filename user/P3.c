#include "P3.h"

void P3() {
  char* x = "hello world, I'm P3\n";

  while( 1 ) {
    write( 0, x, 20 );
  }
}

void (*entry_P3)() = &P3;
