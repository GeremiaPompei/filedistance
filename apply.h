#ifndef FILEDISTANCE_APPLY_H
#define FILEDISTANCE_APPLY_H

typedef struct ADD_DEL_SET {
    char command[3];
    unsigned int num;
    unsigned char byte;
}ADS;

void apply_m(char *input, char *filem, char *output);
void apply_functions(int *size,ADS **ads,char *contentinput,char *contentoutput);
void ads_function(ADS **ads,char *contentinput,char *contentoutput,int *size,int *countI,int *countCO,int *flag, int *i);
void oldstr_function(char *contentinput,char *contentoutput,int *countI,int *countCO,int *flag);
void buffer_to_ads(char *buffer, ADS *ads);
int take_token(char* buffer, char *token, int index,int limit);

#endif
