#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "utility.h"
#include "distance.h"

void time_distance_m(char *file1, char *file2, char *output){
    char *contentf1 = NULL, *contentf2 = NULL;
    int dist = -1;
    double time = -1;
    clock_t clock1 = NULL,clock2 = NULL;
    contentf1 = read_file(file1);
    contentf2 = read_file(file2);
    clock1 = clock();
    dist = distance(contentf1, contentf2, output);
    clock2 = clock();
    time = (double)(clock2 - clock1) / CLOCKS_PER_SEC;
    printf("EDIT DISTANCE: %d\nTIME: %3f\n", dist, time);
    free(contentf1);
    free(contentf2);
}

int distance(char *contentf1, char *contentf2, char *output) {
    int distance = -1, sizef1 = -1, sizef2 = -1;
    int **matrix = NULL;
    sizef1 = strlen(contentf1);
    sizef2 = strlen(contentf2);
    matrix = malloc_matrix(sizef1 + 1,(sizef1 + 1) * sizeof(int*),(sizef2 + 1) * sizeof(int));
    calculate_distance(contentf1, contentf2, matrix);
    distance = matrix[sizef1][sizef2];
    if(output != NULL)
        file_m_build(matrix, sizef1, sizef2, contentf1, contentf2, output);
    free_matrix(matrix,sizef1 + 1);
    return distance;
}

void calculate_distance(char *contentf1, char *contentf2, int **matrix){
    int sizef1 = strlen(contentf1);
    int sizef2 = strlen(contentf2);
    int i, j;
    for(i = 0; i <= sizef1; i++)
        matrix[i][0] = i;
    for(j = 1; j <= sizef2; j++)
        matrix[0][j] = j;
    for(i = 1; i <= sizef1; i++) {
        for(j = 1; j <= sizef2; j++) {
            if(contentf1[i - 1] != contentf2[j - 1]) {
                int k = minimum(
                        matrix[i][j - 1],
                        matrix[i - 1][j],
                        matrix[i - 1][j - 1]
                );
                matrix[i][j] = k + 1;
            } else {
                matrix[i][j] = matrix[i - 1][j - 1];
            }
        }
    }
}

void file_m_build(int **matrix, int sizef1, int sizef2, char *file1, char *file2, char *output){
    int i;
    int size = matrix[sizef1][sizef2] + 1;
    int *psizef1 = &sizef1, *psizef2 = &sizef2;
    char **instructions = malloc_matrix(size + 1,sizeof(char *) * (size + 1),sizeof(char ) * 8);
    FILE *file = NULL;
    assert(file = fopen(output,"w"));
    middle_instructions(matrix,instructions,psizef1,psizef2,file1,file2);
    final_instructions(matrix,instructions,psizef1,psizef2,file1,file2);
    for (i = 1;i<size;i++)
        fprintf(file, "%s", instructions[i]);
    fclose(file);
    free_matrix(instructions,size + 1);
}

void middle_instructions(int **matrix, char **instructions, int *sizef1, int *sizef2,char *file1, char *file2) {
    while(*sizef1 > 0 && *sizef2 > 0){
        int k = minimum(matrix[*sizef1 - 1][*sizef2 - 1], matrix[*sizef1 - 1][*sizef2], matrix[*sizef1][*sizef2 - 1]);
        if (file1[*sizef1 - 1] != file2[*sizef2 - 1]){
            if(k==matrix[*sizef1 - 1][*sizef2 - 1]){
                sprintf(instructions[matrix[*sizef1][*sizef2]], "SET%4d%1c\n", *sizef2, file2[*sizef2 - 1]);
            }else if(k==matrix[*sizef1][*sizef2 - 1]){
                sprintf(instructions[matrix[*sizef1][*sizef2]], "ADD%4d%1c\n", *sizef2, file2[*sizef2 - 1]);
                (*sizef1)++;
            }else if(k==matrix[*sizef1 - 1][*sizef2]){
                sprintf(instructions[matrix[*sizef1][*sizef2]], "DEL%4d%1c\n", *sizef2, ' ');
                (*sizef2)++;
            }
        }
        (*sizef1)--;
        (*sizef2)--;
    }
}

void final_instructions(int **matrix, char **instructions, int *sizef1, int *sizef2,char *file1, char *file2) {
    while(*sizef2 > 0){
        if(file1[*sizef1 - 1] != file2[*sizef2 - 1])
            sprintf(instructions[matrix[*sizef1][*sizef2]], "ADD%4d%1c\n", *sizef2, file2[*sizef2 - 1]);
        (*sizef2)--;
    }
    while(*sizef1 > 0){
        if(file1[*sizef1 - 1] != file2[*sizef2 - 1])
            sprintf(instructions[matrix[*sizef1][*sizef2]], "DEL%4d%1c\n", *sizef2, ' ');
        (*sizef1)--;
    }
}
