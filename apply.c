#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "apply.h"

void apply_m(char *input, char *filem, char *output){
    int i = 0, size = 0;
    int countCO=0, countI=0;
    int flag=0;
    ADS *ads = NULL, *pads = NULL;
    char *contentinput = NULL,*contentfilem = NULL, *contentoutput = NULL;
    contentinput = read_file(input);
    contentfilem = read_file(filem);
    size = strlen(contentinput);
    contentoutput = malloc(size + strlen(contentfilem) / 8);
    ads = malloc(strlen(contentfilem) / 8 * sizeof(ADS));
    pads = ads;
    buffer_to_ads(contentfilem, ads);
    for(i = 0;i<size+2;i++){
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
            else if(countI >=1)
                contentoutput[countCO] = contentinput[countI - 1];
            else countCO--;
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
