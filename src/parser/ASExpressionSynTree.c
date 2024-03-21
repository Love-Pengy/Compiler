//B. Frazier 3/21/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../include/parser/ASsynTree.h"
#endif

#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif

#ifndef STDIO
    #define STDIO
    #include <stdio.h>
#endif

#ifndef STRING
    #define STRING
    #include <string.h>
#endif

struct expressionStatementTreeType{
    enum expressionType type;
    union{  
        char * number;
        char * id;
        char * charLit;
        char * string;
        functionCallTree funcC;
        expressionStatementTree exp;
        minusTree min;
        notTree not;
    };
};


expressionStatementTree createExpressionStatementTree(enum expressionType t, void* val){
    expressionStatementTree est = malloc(sizeof(struct expressionStatementTreeType));
    switch(t){
        case Number:
            est->number = malloc(sizeof(char) * strlen((char*)val) + 1);
            strcpy(est->number, (char*)val);
            break;
        case ID:
            est->id = malloc(sizeof(char) * strlen((char*)val) + 1);
            strcpy(est->id, (char*)val);
            break;
        case CharLiteral:
            est->charLit = malloc(sizeof(char) * strlen((char*)val) + 1);
            strcpy(est->charLit, (char*)val);
            break;
        case StringLiteral:
            est->string = malloc(sizeof(char) * strlen((char*)val) + 1);
            strcpy(est->string, (char*)val);
            break;
        case funcCall:
            est->funcC = (functionCallTree)val;
            break;
        case Expr:
            est->exp = (expressionStatementTree)val;
            break;
        case Minus:
            est->min = (minusTree)val;
            break;
        case Not:
            est->not = (notTree)val;
            break;
        default:
            printf("internal error\n");
            break;
    }
    return(est);
}

list expressionTreeToString(expressionTree exprT){
    list string = createList();
    listCat(string, "Expression(");
    switch(exprT->Type){
        case Number:
            listCat(string, exprT->number);
            break;
        case ID:
            listCat(string, exprT->id);
            break;
        case CharLiteral:
            listCat(string, exprT->charLit);
            break;
        case StringLiteral:
            listCat(string, exprT->string);
            break;
        case funcCall:
            listCat(string, exprT->funcC);
            break;
        case Expr:
            listCat(string, exprT->exp);
            break;
        case Minus:
            listCat(string, exprT->min);
            break;
        case Not:
            listCat(string, exprT->not);
            break;
        default:
            printf("internal error\n");
            break;
    }
    listCat(string, ")\n");
    return(string);
}

