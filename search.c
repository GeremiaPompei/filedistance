#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "utility.h"
#include "distance.h"
#include "search.h"

void search(char *inputfile, char *dir, int limit){
    int *index = 0;
    char *contentif = read_file(inputfile);
    int size = store_paths(NULL,dir , inputfile,&index);
    char **paths = malloc_matrix(size,sizeof(char *) * size,sizeof(char ) * 256);
    index = 0;
    store_paths(paths, dir , inputfile, &index);
    if(limit==NULL)
        search_one(inputfile,size,paths,contentif);
    else
        search_all(inputfile,size,paths,contentif,limit);
    free(contentif);
    free_matrix(paths,size);
}

void search_one(char *inputfile, int size, char **paths, char *contentif){
    int i= -1,MIN = -1;
    char *buffer = malloc(256 * (size+1) * sizeof(char ));
    for(i = 0;i<size; i++) {
        char *contenttmpf = read_file(paths[i]);
        int n = distance(contentif, contenttmpf, NULL);
        if ((n <= MIN || MIN == -1) && strcmp(inputfile, paths[i]) != 0) {
            if(n==MIN){
                char tmp[256];
                sprintf(tmp,"%d %s\n",MIN,paths[i]);
                strcat(buffer,tmp);
            } else {
                MIN = n;
                sprintf(buffer,"%d %s\n",MIN,paths[i]);
            }
        }
        free(contenttmpf);
    }
    printf("%s",buffer);
    free(buffer);
}

void search_all(char *inputfile, int size, char **paths, char *contentif, int limit){
    int i = -1;
    D_PATH **dpath = malloc_matrix(size,sizeof(D_PATH*) * size, sizeof(D_PATH));
    for(i = 0; i < size; i++)
        dpath[i]->distance = 0;
    for(i = 0;i<size; i++) {
        char *file_path = read_file(paths[i]);
        int n = distance(contentif, file_path, NULL);
        if ((n <= limit) && strcmp(inputfile, paths[i]) != 0) {
            dpath[i]->distance = n;
            strcpy(dpath[i]->path,paths[i]);
        }
        free(file_path);
    }
    bubblesort(dpath,size);
    print_dpaths(dpath,size);
    free_matrix(dpath,size);
}

void print_dpaths(D_PATH **dpath,int size){
    for (int i = 0; i < size; i++) {
        if(dpath[i]->distance != 0) {
            printf("%d %s\n", dpath[i]->distance, dpath[i]->path);
        }
    }
}

int store_paths(char **paths, char *path, char *inputfile,int *index){
    struct dirent *dirent;
    char new[256];
    DIR *dir = opendir(path);
    while ((dirent = readdir(dir)) != NULL) {
        build_path(new, path, dirent->d_name);
        if((dirent->d_name)[0] != '.' && strcmp(inputfile, new) != 0){
            if(dirent->d_type == 4){
                store_paths(paths, new, inputfile, index);
            }else{
                if(paths != NULL)
                    strcpy(paths[*index], new);
                (*index)++;
            }
        }
    }
    closedir(dir);
    return *index;
}

void bubblesort(D_PATH **dpath, int size){
    int i, j;
    for(i = 0; i < size - 1; i++)
        for (j = size - 1; j > i; j--)
            if (dpath[j]->distance < dpath[j-1]->distance)
                _switch(&(dpath[j]), &(dpath[j - 1]));
}

void _switch(D_PATH **a, D_PATH **b){
    D_PATH temp;
    temp = **a;
    **a = **b;
    **b = temp;
}
