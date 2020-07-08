#include "stdio.h"

#ifndef FILEDISTANCE_UTILITY_H
#define FILEDISTANCE_UTILITY_H

char *read_file(char *path);
void write_file(char *path,char *buffer,int size);
int minimum(int a, int b, int c);
long file_size(char *path);
void build_path(char* new,char *old,char *name);

#endif
