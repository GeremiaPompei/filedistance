#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>
#include "utility.h"
#include "distance.h"
#include "search.h"

void search(char *inputfile, char *dir, int limit){
    int *index = 0;
    char **paths = NULL;
    char *contentif = read_file(inputfile);
    visit_in_depth(dir, inputfile, &index, NULL);
    int size = index;
    assert(paths = malloc(sizeof(char *) * size));
    index = 0;
    visit_in_depth(dir, inputfile, &index, paths);
    if(limit==NULL)
        search_one(inputfile,size,paths,contentif);
    else
        search_all(inputfile,size,paths,contentif,limit);
    free(contentif);
    free_matrix(paths,size);
}

void search_one(char *inputfile, int size, char **paths, char *contentif){
    int i= -1,MIN = -1;
    char *buffer = NULL;
    assert(buffer= malloc(256 * (size+1) * sizeof(char )));
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
    for(i = 0;i < size; i++) {
        char *file_path = read_file(paths[i]);
        int n = distance(contentif, file_path, NULL);
        dpath[i]->distance = -1;
        if ((n <= limit) && strcmp(inputfile, paths[i]) != 0) {
            dpath[i]->distance = n;
            dpath[i]->path = paths[i];
        }
        free(file_path);
    }
    bubblesort(dpath,size);
    print_dpaths(dpath,size);
    free_matrix(dpath,size);
}

void print_dpaths(D_PATH **dpath,int size){
    for (int i = 0; i < size; i++)
        if(dpath[i]->distance != -1)
            printf("%d %s\n", dpath[i]->distance, dpath[i]->path);
}

void visit_in_depth(char *path, char *inputfile, int *index, char **paths){
    struct dirent *dirent = NULL;
    DIR *dir = NULL;
    assert(dir = opendir(path));
    while ((dirent = readdir(dir)) != NULL) {
        char *new[strlen(path) + strlen(dirent->d_name)];
        build_path(new, path, dirent->d_name);
        if((dirent->d_name)[0] != '.' && strcmp(inputfile, new) != 0){
            if(dirent->d_type == 4){
                visit_in_depth(new, inputfile, index, paths);
            }else{
                if(paths != NULL) {
                    assert(paths[*index] = malloc((strlen(new) + 1) * sizeof(char )));
                    strcpy(paths[*index], new);
                }
                (*index)++;
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
