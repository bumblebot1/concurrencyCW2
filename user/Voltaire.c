#include "Voltaire.h"

void Voltaire() {
  int i = makeChan(4,5);
  int j = makeChan(5,6);
  while(1){
    printf("Voltaire\n");
  }
}

void (*entry_Voltaire)() = &Voltaire;
