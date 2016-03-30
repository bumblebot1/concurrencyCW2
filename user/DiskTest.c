#include "DiskTest.h"

void DiskTest() {

  while( 1 ) {
    // test whether each x for 2^8 < x < 2^24 is prime or not
    uint32_t x = creat("test");
    printf("did smth\n");
  }

  return;
}

void (*entry_DiskTest)() = &DiskTest;
