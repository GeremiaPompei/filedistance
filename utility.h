#include "stdio.h"

#ifndef FILEDISTANCE_UTILITY_H
#define FILEDISTANCE_UTILITY_H

void **malloc_matrix(int sizefor, int size1, int size2);
void free_matrix(void **matrix, int size);
char *read_file(char *path);
void write_file(char *path,char *buffer,int size);
void write_matrix(char *path,char **buffer,int size);
int minimum(int a, int b, int c);
long file_size(char *path);
void read_string_from_file(char *buffer, int size, FILE *file);
void build_path(char* new, char *old, char *name);

#endif
