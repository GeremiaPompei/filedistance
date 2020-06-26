#ifndef FILEDISTANCE_DISTANCE_H
#define FILEDISTANCE_DISTANCE_H

void time_distance_m(char *file1, char *file2, char *output);
int distance(char *contentf1, char *contentf2, char *output);
void calculate_distance(char *contentf1, char *contentf2, int **matrix);
void file_m_build(int **matrix, int sizef1, int sizef2, char *file1, char *file2, char *output);

#endif
