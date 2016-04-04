#ifndef __LIBC_H
#define __LIBC_H

#include <stddef.h>
#include <stdint.h>
#include "PL011.h"

void ps();

// writes n characters to the fileDescriptor
int write ( int fd, void* x, int n);

// read n bytes from emulated UART into x
int read ( int fd, void* x, size_t n);

//readline from the emulated UART into x
int readLine (int fd, void* x);

// writes the given string to console and also replaces % with given arguments(in particular only ints)
void printf (char* str,...);

int fork (int pid, uint32_t wt);

int exit (int pid);

int makeChan(int pidWrite,int pidRead);

int writeChan(int id,void* value);

void* readChan(int id);

int closeChan(int id);

int creat(char* name);

int unlink(char* name);

int open(char* name,int mode);

int close(int fd);
#endif
