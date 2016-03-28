#include "Confucius.h"

void Confucius() {
  int i = makeChan(4,5);
  int j = makeChan(6,4);
  while(1){
    printf("Confucius\n");
  }
}

void (*entry_Confucius)() = &Confucius;
