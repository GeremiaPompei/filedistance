#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "distance.h"
#include "apply.h"
#include "search.h"

int main(int argc, char **argv) {
    if (argc != 4 && argc != 5) {
        printf("Wrong number of parameters (expected 4 or 5 are: %d)!\n", argc);
        return -1;
    }
    if(argc==4){
        if(strcmp(argv[1],"distance")==0){
            time_distance_m(argv[2],argv[3],NULL);
            return 0;
        }else if(strcmp(argv[1],"search")==0){
            search(argv[2],argv[3],NULL);
            return 0;
        }
    }
    if(argc==5){
        if(strcmp(argv[1],"distance")==0){
            time_distance_m(argv[2],argv[3],argv[4]);
            return 0;
        }else if(strcmp(argv[1],"apply")==0){
            apply_m(argv[2],argv[3],argv[4]);
            return 0;
        } else if(strcmp(argv[1],"searchall")==0) {
            search(argv[2], argv[3], atoi(argv[4]));
            return 0;
        }
    }
    return -1;
}
