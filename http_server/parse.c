#include <string.h>
#include "parse.h"

int parse_begin(char **place, char *request){
    
    *place = strchr(request, '?');
    if (*place == NULL) return -1; 

    *place = *place + 1; //skip the ?
    return 0;
}

int parse_next(char **place, char **param, char **value){ 
    char *tmp;

    if (*place == NULL) return -1; 
    
    tmp = strpbrk(*place, "=");

    if (tmp == NULL) return -1; 

    *tmp   = 0;
    *param = *place;
    *value = tmp + 1;

    tmp = strpbrk(*value , "& "); //Find next one
    if (tmp == NULL){
        *place = NULL;
        return 0;
    }

    *tmp   = 0;
    *place = tmp + 1;

    return 0;
}

