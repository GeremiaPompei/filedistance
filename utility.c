#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "utility.h"

void **malloc_matrix(int sizefor, int size1, int size2){
    int i = -1;
    void **matrix = malloc(size1);
    for(i = 0; i < sizefor; i++)
        matrix[i] = malloc(size2);
    return matrix;
}

void free_matrix(void **matrix, int size){
    int i = -1;
    for(i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

void write_file(char *path,char *buffer,int size){
    FILE *file = fopen(path,"w");
    if(file==NULL) exit(1);
    fwrite(buffer,sizeof(char ),size,file);
    fclose(file);
}

char *read_file(char *path){
    int size = -1;
    char *buffer = NULL;
    FILE *file = fopen(path,"r");
    if(file==NULL) exit(1);
    size = file_size(path);
    buffer = malloc(size);
    read_string_from_file(buffer,size,file);
    fclose(file);
    return buffer;
}

void read_string_from_file(char *buffer, int size, FILE *file){
    int i = -1;
    for (i=0;i<size;i++)
        buffer[i] = fgetc(file);
    buffer[i]='\0';
}

long file_size(char *path){
    int size = -1;
    struct stat *st = malloc(sizeof(struct stat));
    if(st == NULL) exit(1);
    stat(path,st);
    size = st->st_size;
    free(st);
    return size;
}

int minimum(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

void build_path(char* new,char *old,char *name){
    strcpy(new,old);
    strcat(new,"/");
    strcat(new,name);
}
