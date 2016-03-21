#ifndef __LIBC_H
#define __LIBC_H

#include <stddef.h>
#include <stdint.h>
#include "PL011.h"
// writes n characters to the fileDescriptor
int write( int fd, void* x, int n);

// read n bytes from emulated UART into x
int read ( int fd, void* x, size_t n);

//readline from the emulated UART into x
int readLine (int fd, void* x);

// writes the given string to console and also replaces % with given arguments(in particular only ints)
void printf(char* str,...);

int fork();
#endif
