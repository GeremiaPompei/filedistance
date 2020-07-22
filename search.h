#include <dirent.h>

#ifndef FILEDISTANCE_SEARCH_H
#define FILEDISTANCE_SEARCH_H

typedef struct DISTANCE_PATH {
    unsigned int distance;
    char path[256];
}D_PATH;

void search(char *inputfile, char *dir, int limit);
void search_one(char *inputfile, int size, char **paths, char *contentif);
void search_all(char *inputfile, int size, char **paths, char *contentif, int limit);
void print_dpaths(D_PATH **dpath,int size);
void visit_in_depth(char *path, char *inputfile, int *index, char **paths);
void bubblesort(D_PATH **dpath, int size);
void _switch(D_PATH **a, D_PATH **b);

#endif
