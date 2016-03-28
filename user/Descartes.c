#include "Descartes.h"

void Descartes() {
  int i = makeChan(5,6);
  int j = makeChan(6,4);
  while(1){
    printf("Descartes\n");
  }
}

void (*entry_Descartes)() = &Descartes;
