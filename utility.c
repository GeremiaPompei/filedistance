#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>
#include "utility.h"

void **malloc_matrix(int sizefor, int size1, int size2){
    int i = -1;
    void **matrix = NULL;
    assert(matrix = malloc(size1));
    for(i = 0; i < sizefor; i++)
        assert(matrix[i] = malloc(size2));
    return matrix;
}

void free_matrix(void **matrix, int size){
    int i = -1;
    for(i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

void write_file(char *path,char *buffer,int size){
    FILE *file = NULL;
    assert(file = fopen(path,"w"));
    fwrite(buffer,sizeof(char ),size,file);
    fclose(file);
}

void write_matrix(char *path,char **buffer,int size){
    int i = -1;
    FILE *file = NULL;
    assert(file = fopen(path,"w"));
    for (i = 1;i<=size;i++)
        fprintf(file,"%s",buffer[i]);
    fclose(file);
}

char *read_file(char *path){
    long size = -1;
    FILE *file = NULL;
    char *buffer = NULL;
    assert(file = fopen(path,"r"));
    size = file_size(path);
    assert(buffer = malloc(size + 1));
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
    struct stat *st = NULL;
    assert(st = malloc(sizeof(struct stat)));
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

void build_path(char* new, char *old, char *name){
    int n = strlen(old) - 1;
    strcpy(new,old);
    if(old[n] != '/')
        strcat(new,"/");
    strcat(new,name);
}
