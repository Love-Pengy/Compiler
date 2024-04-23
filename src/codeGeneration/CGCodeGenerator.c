#include "../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include <string.h>
#include "../../include/cmdLine/TCglobals.h"
#include "../../include/parser/TCparser.h"

char* getClassname(char* input){
    char* copy = malloc(sizeof(char) * (strlen(inputFileName)+ 1));
    copy[0] = '\0';
    strcpy(copy, input);
    char* cut = strtok(copy, "/");
    char* last = NULL;
    while(cut != NULL){
        last = cut;
        cut = strtok(NULL, "/");
    }       
    return(last);
}

//traverse the AST and convert each part to its respective instructions
//for each tree implement a "generate code" function the implements its respective template
void generateJasminCode(programTree program){ 
    char* original = malloc(sizeof(char) * (strlen(inputFileName)+ 1));
    original[0] = '\0';
    strcpy(original, inputFileName);
    char* cut = strtok(original, ".");
    char* last = NULL;
    while(cut != NULL){
        last = cut;
        cut = strtok(NULL, ".");
    }       
    char* newInputFile = NULL;

    FILE* fptr;

    if(outputFileName == NULL){
        if(strlen(last) == strlen(inputFileName)){
            newInputFile = malloc(sizeof(char) * (strlen(inputFileName) + 2));
            newInputFile[0] = '\0';
            strcpy(newInputFile, inputFileName);

            javaClassname = malloc(sizeof(char) * (strlen(newInputFile) + 1));
            javaClassname[0] = '\0';
            javaClassname = getClassname(newInputFile);
            strcat(newInputFile, ".j");
        }
        else if((inputFileName[0] == '.') && (strlen(last) == (strlen(inputFileName)-1))){ 
            newInputFile = malloc(sizeof(char) * (strlen(inputFileName) + 2));
            newInputFile[0] = '\0';
            strcpy(newInputFile, inputFileName);

            javaClassname = malloc(sizeof(char) * (strlen(newInputFile) + 1));
            javaClassname[0] = '\0';
            javaClassname = getClassname(newInputFile);

            strcat(newInputFile, ".j");
        }
        else{
            int extSize = strlen(last); 
            newInputFile = malloc(sizeof(char) * ((strlen(inputFileName) - extSize) + 2));
            newInputFile[0] = '\0';
            
            for(int i = 0; i < (strlen(inputFileName) - (extSize+1)); i++){
                newInputFile[i] = inputFileName[i];
                newInputFile[i+1] = '\0';
            }

            javaClassname = malloc(sizeof(char) * (strlen(newInputFile) + 1));
            javaClassname[0] = '\0';
            javaClassname = getClassname(newInputFile);

            strcat(newInputFile, ".j");
        }
        fptr = fopen(newInputFile, "w");
    }
    else{
        fptr = fopen(outputFileName, "w"); 
    }

    generateProgramTree(program, fptr);
}

