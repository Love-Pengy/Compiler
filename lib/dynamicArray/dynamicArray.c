#ifndef DYNAMICARRAY_H
    #include "./dynamicArray.h"
#endif
#ifndef STDLIB_H
    #include <stdlib.h>
#endif 
#ifndef STRING_H
    #include <string.h>
#endif

#define CHUNK_SIZE 50

struct listType{
    char *string;
    int size;
    int buffSize;
};

list createList(void){
    list output = malloc(sizeof(struct listType));
    output->string = malloc(sizeof(char) * (CHUNK_SIZE + 1));
    output->string[51] = '\0';
    output->size = 0;
    output->buffSize = 50;
    return(output);
}

void expandList(list expandee){
    char *newList = malloc(sizeof(char) * (expandee->buffSize + CHUNK_SIZE));
    strcpy(newList, expandee->string);
    free(expandee->string);
    expandee->string = newList;
}

void listCat(list dest, char *source){
    if((strlen(source) + dest->size) > dest->buffSize){
        expandList(dest);
    }
    else{
        dest->size = (dest->size + strlen(source));
        strcat(dest->string, source);
    }
}

void freeList(list goodbye){
    free(goodbye->string);
    free(goodbye);
}
