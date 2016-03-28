#include "Socrates.h"

void Socrates() {
  int i = makeChan(4,5);
  int j = makeChan(6,4);
  while(1){
    printf("Socrates\n");
  }
}

void (*entry_Socrates)() = &Socrates;
