#ifndef __LIBC_H
#define __LIBC_H

#include <stddef.h>
#include <stdint.h>

// write a single character to the fileDescriptor
int writeChar( int fd, char x);

// write an integer to the fileDescriptor
int writeInt( int fd, int x);

// read n bytes from emulated UART into x
int read ( int fd, void* x, size_t n);

void printf(char* str,...);

#endif
