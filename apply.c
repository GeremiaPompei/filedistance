#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "apply.h"

void apply_m(char *input, char *filem, char *output){
    int i;
    char *contentinput,*contentfilem;
    contentinput = read_file(input);
    contentfilem = read_file(filem);
    int size = (strlen(contentinput) + 2);
    char *contentoutput = malloc(size + strlen(contentfilem) / 7);
    ADS *ads = malloc(strlen(contentfilem));
    ADS *pads = ads;
    buffer_to_ads(contentfilem, ads);
    int countCO=0, countI=0;
    int flag=0;
    for(i = 0;i<size;i++){
        if(ads->num == i){
            if(strcmp(ads->command, "ADD") == 0) {
                contentoutput[countCO] = ads->byte;
                size++;
                countI--;
            }else if(strcmp(ads->command, "SET") == 0) {
                contentoutput[countCO] = ads->byte;
            }else {
                contentoutput[countCO] = contentinput[countI - 1];
                flag=1;
                while (ads->num == i && (ads + 1)->num == i){
                    ads++;
                    size--;
                    countI++;
                }
                i--;
            }
            ads++;
        }else {
            if(flag == 1)
                flag=0;
            else
                contentoutput[countCO] = contentinput[countI - 1];
        }
        countI++;
        countCO++;
    }
    write_file(output, contentoutput, size);
    free(contentfilem);
    free(contentinput);
    free(contentoutput);
    free(pads);
}

void buffer_to_ads(char *buffer, ADS *ads){
    char tmp[256];
    int i = 0;
    while (buffer[i] != '\0') {
        i = take_token(buffer, ads->command, i);
        i = take_token(buffer, tmp, i);
        ads->num = atoi(tmp);
        if (ads->command != "DEL") {
            i = take_token(buffer, tmp, i);
            ads->byte = (unsigned char)atoi(tmp);
        }
        ads++;
    }
}

int take_token(char* buffer, char *token, int index){
    char tmp[256];
    int i=0;
    while (buffer[index] != ',' && buffer[index] != '\n' && buffer[index] != '\0') {
        tmp[i]=buffer[index];
        i++;
        index++;
    }
    strcpy(token, tmp);
    index++;
    return index;
}
