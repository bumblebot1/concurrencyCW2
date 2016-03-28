#include "Aristotle.h"

void Aristotle() {
  int i = makeChan(4,5);
  int j = makeChan(5,6);
  while(1){
    printf("Aristotle\n");
  }
}

void (*entry_Aristotle)() = &Aristotle;
