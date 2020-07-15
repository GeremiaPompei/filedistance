#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "utility.h"
#include "distance.h"
#include "search.h"

void search_all(char *inputfile, char *dir, int limit){
    int i;
    int size = count_files(dir);
    char *contentif = read_file(inputfile);
    char **paths = (char **)malloc(sizeof(char *) * size);
    for(i = 0; i < size; i++)
        paths [i] = (char *) malloc(sizeof(char ) * 256);
    D_PATH **dpath = (D_PATH**)malloc(sizeof(D_PATH*) * size);
    for(i = 0; i < size; i++) {
        dpath[i] = (D_PATH *) malloc(sizeof(D_PATH));
        dpath[i]->distance = 0;
    }
    store_paths(paths, dir);
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
    for (i = 0; i < size; i++) {
        if(dpath[i]->distance != 0) {
            printf("%d %s\n", dpath[i]->distance, dpath[i]->path);
        }
    }
    free(contentif);
    for(i = 0; i < size; i++)
        free(paths[i]);
    free(paths);
    for(i = 0; i < size; i++)
        free(dpath[i]);
    free(dpath);
}

void search(char *inputfile, char *dir){
    int i;
    char tmp[256];
    int size = count_files(dir);
    char **paths = (char**)malloc(sizeof(char *) * size);
    for(i = 0; i < size; i++)
        paths[i] = (char*) malloc(sizeof(char ) * 256);
    int MIN = -1;
    char *buffer = malloc(256 * size);
    char *contentif = read_file(inputfile);
    store_paths(paths, dir);
    for(i = 0;i<size; i++) {
        char *contenttmpf = read_file(paths[i]);
        int n = distance(contentif, contenttmpf, NULL);
        if ((n <= MIN || MIN == -1) && strcmp(inputfile, paths[i]) != 0) {
            if(n==MIN){
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
    for(i = 0; i < size; i++)
        free(paths[i]);
    free(paths);
    free(contentif);
    free(buffer);
}

int count_files(char *path){
    int size=0;
    DIR *dir;
    struct dirent *dirent;
    char new[256];
    dir = opendir(path);
    while ((dirent = readdir(dir)) != NULL) {
        build_path(new, path, dirent->d_name);
        if((dirent->d_name)[0] != '.'){
            if(dirent->d_type == 4)
                size+=count_files(new);
            else
                size++;
        }
    }
    closedir(dir);
    return size;
}

void store_paths(char **paths, char *path){
    DIR *dir;
    struct dirent *dirent;
    char new[256];
    dir = opendir(path);
    while ((dirent = readdir(dir)) != NULL) {
        build_path(new, path, dirent->d_name);
        if((dirent->d_name)[0] != '.'){
            if(dirent->d_type == 4){
                store_paths(paths, new);
            }else{
                while(strcmp(*paths, "\0") != 0)
                    paths++;
                strcpy(*paths, new);
            }
        }
    }
    closedir(dir);
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
