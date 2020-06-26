#include <string.h>
#include <stdlib.h>
#include "utility.h"

void write_file(char *path,char *buffer,int size){
    FILE *file = fopen(path,"w");
    if(file==NULL)
        exit(1);
    fwrite(buffer,sizeof(char),size,file);
    //fclose(file);
}

char *read_file(char *path){
    FILE *file = fopen(path,"r");
    if(file==NULL)
        exit(1);
    long size = file_size(file);
    char *buffer = malloc(size);
    fread(buffer, sizeof(char), size,file);
    //fclose(file);
    return buffer;
}

long file_size(FILE *file){
    long size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
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
