#include "P4.h"

void P4() {
  char* x = "hello world, I'm P4\n";

  while( 1 ) {
    write( 0, x, 20 );
  }
}

void (*entry_P4)() = &P4;