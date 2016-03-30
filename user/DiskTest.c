#include "DiskTest.h"

void DiskTest() {
  uint32_t x = 0;

  while( 1 ) {
    // test whether each x for 2^8 < x < 2^24 is prime or not
    printf("Testing disk\n");

  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
