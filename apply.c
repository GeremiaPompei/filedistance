#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "utility.h"
#include "apply.h"

void apply_m(char *input, char *filem, char *output){
    int size = -1, *psize = &size;
    ADS *ads = NULL, *pads = ads, **ppads = &ads;
    char *contentinput = NULL,*contentfilem = NULL, *contentoutput = NULL;
    contentinput = read_file(input);
    contentfilem = read_file(filem);
    size = strlen(contentinput) + 2;
    assert(contentoutput = malloc(strlen(contentfilem) / 9 + size));
    assert(ads = malloc(strlen(contentfilem) / 9 * sizeof(ADS)));
    buffer_to_ads(contentfilem, ads);
    apply_functions(psize,ppads,contentinput,contentoutput);
    write_file(output, contentoutput, size);
    free(contentfilem);
    free(contentinput);
    free(contentoutput);
    free(pads);
}

void apply_functions(int *size,ADS **ads,char *contentinput,char *contentoutput) {
    int i = -1, *pi = &i, countCO = 0, *pcountCO = &countCO, countI = 0, *pcountI = &countI, flag=0, *pflag = &flag;
    for(i = 0;i < *size;i++){
        if((*ads)->num == i){
            ads_function(ads,contentinput,contentoutput,size,pcountI,pcountCO,pflag,pi);
        }else {
            oldstr_function(contentinput,contentoutput,pcountI,pcountCO,pflag);
        }
        countI++;
        countCO++;
    }
}

void ads_function(ADS **ads,char *contentinput,char *contentoutput,int *size,int *countI,int *countCO,int *flag, int *i){
    if(strcmp((*ads)->command, "ADD") == 0) {
        contentoutput[*countCO] = (*ads)->byte;
        (*size)++;
        (*countI)--;
    }else if(strcmp((*ads)->command, "SET") == 0) {
        contentoutput[*countCO] = (*ads)->byte;
    }else {
        contentoutput[*countCO] = contentinput[*countI - 1];
        (*flag) = 1;
        while ((*ads)->num == *i && (*ads + 1)->num == *i){
            (*ads)++;
            (*size)--;
            (*countI)++;
        }
        (*i)--;
    }
    (*ads)++;
}

void oldstr_function(char *contentinput,char *contentoutput,int *countI,int *countCO,int *flag) {
    if(*flag == 1)
        *flag=0;
    else if(*countI >=1)
        contentoutput[*countCO] = contentinput[*countI - 1];
    else (*countCO)--;
}

void buffer_to_ads(char *buffer, ADS *ads){
    char tmp[5];
    int i = 0;
    while (buffer[i] != '\0') {
        i = take_token(buffer, ads->command, i,3);
        i = take_token(buffer, tmp, i,4);
        ads->num = atoi(tmp);
        if (ads->command != "DEL") {
            i = take_token(buffer, tmp, i,1);
            ads->byte = (unsigned char)tmp[0];
        }
        i++;
        ads++;
    }
}

int take_token(char* buffer, char *token, int index, int limit){
    char tmp[5] = "\0";
    int i=0;
    while (i<limit) {
        tmp[i]=buffer[index];
        i++;
        index++;
    }
    strcpy(token, tmp);
    return index;
}
