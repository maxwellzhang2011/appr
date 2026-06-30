#include "../depend/split.h"
#include <stdlib.h>
#include <string.h>

unsigned int split(char ***out, char *in){
    char *buffer;
    *out = (char**)malloc(sizeof(char*));
    unsigned int size = 0, outi=0, i=0;
    while(i < strlen(in)){
        if(in[i]==' ' && size > 0){
            buffer = malloc(size+1);
            strncpy(buffer, in+i-size, size);
            buffer[size] = '\0';
            (*out)[outi] = buffer;
            outi++;
            *out = (char**)realloc(*out, (outi+1)*sizeof(char*));
            size = 0;
            i++;
            continue;
        }
        size++;
        i++;
    }
    if(size>0){
        buffer = malloc(size+1);
        strncpy(buffer, in+i-size, size);
        buffer[size] = '\0';
        (*out)[outi] = buffer;
        outi++;
    }
    *out = (char**)realloc(*out, (outi+1)*sizeof(char*));
    (*out)[outi] = NULL;
    outi++;
    return outi;
}
