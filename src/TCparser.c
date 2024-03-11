#include <stdlib.h>
#ifndef TCLEXER_H
    #include "../include/TClexer.h"
#endif
#ifndef STRING_H
    #include <string.h>
#endif

token currentToken;

//make it so that it knows stuff exists
void toyCProgram(void);
void definition(void);
void type(void);
void functionDefinition(void);
void functionHeader(void);
void functionBody(void);
void formalParamList(void);
void statement(void);
void expressionStatement(void);
void breakStatement(void);
void compoundStatement(void);
void ifStatement(void);
void nullStatement(void);
void returnStatement(void);
void whileStatement(void);
void readStatement(void);
void writeStatement(void);
void newLineStatement(void);
void expression(void);
void relopExpression(void);
void simpleExpression(void);
void term(void);
void primary(void);
void functionCall(void);
void actualParameters(void);

void throwError(char expected){
    printf("%d :", getLineNum());
    printf("%s\n", getCurrentLine());

    for(int i = 0; i < getPos(); i++){
        printf(" ");
    }

    printf("^ '%c' expected\n", expected); 
    exit(EXIT_FAILURE);
}

void throwStateError(char *expected){
    printf("%d :", getLineNum());
    printf("%s\n", getCurrentLine());

    for(int i = 0; i < getPos(); i++){
        printf(" ");
    }

    printf("^ '%s' expected\n", expected); 
    exit(EXIT_FAILURE);
}

void accept(char terminal){
    if(terminal == currentToken->value){
        getLexeme();
    }
    else{
        throwError(terminal);
    }

}
void getNextToken(void){
    currentToken = getLexeme();
}

void entering(char *entereeLikeABee){
    if(debug_parser){
        printf("[PARSER] entering %s\n", entereeLikeABee);
    }
}

void exiting(char *exiteeLikeSomeTea){
    if(debug_parser){
        printf("[PARSER] exiting %s\n", exiteeLikeSomeTea);
    }
}

//think of this like A() its the state itself. The leaf is defined elsewhere
void toyCProgram(void){
    entering("toyCProgram");
    getNextToken();    
    definition();
    if(!strcmp(currentToken->lexeme, "EOF")){
        if(debug_parser){
            exiting("toyCProgram");
            printf("parse has been completed\n");
        }    
    }
    throwStateError("EOF");
}


void definition(void){
    entering("definition");
    type(); 
    getNextToken();
    if(!strcmp(currentToken->lexeme, "ID")){
        if(!strcmp(currenttoken->lexeme, "SEMICOLON")){
            
        }
        else{
            functionDefinition();
        }
    }
    else{
        throwStateError("ID");   
    }
    exiting("definition");
}

typeSynTree type(void){
    entering("type"); 
    if(!strcmp(currentToken->lexeme, "KEYWORD") && !strcmp(currentToken->value, "int")){
        getNextToken();    
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        getNextToken();
    }
    else{
        throwStateError("Int Or Char"); 
    }
    exiting("type");
}

void functionDefinition(void){
    entering("functionDefinition");  
    functionHeader();
    functionBody();
    exiting("functionDefinition");
}

void functionHeader(void){
    entering("functionHeader"); 
    accept('(');
    formalParamList();
    accept(')');
    exiting("functionHeader");
}

void functionBody(void){
    entering("functionBody");
    compoundStatement();
    exiting("functionBody");
}

void formalParamList(void){
    entering("formalParamList");
    type();
    if(!strcmp(currentToken->lexeme, "ID")){
        getNextToken();
    }
    else{
        throwStateError("ID");
    }
    while(!strcmp(currentToken->lexeme, "COMMA")){
        type();
        if(!strcmp(currentToken->lexeme, "ID")){
            getNextToken();
        }
    }
    exiting("formalParamList");
}

void statement(void){
    entering("statement");
    if(!strcmp(currentToken->lexeme, "KEYWORD")){
        if(!strcmp(currentToken->value, "break")){
            breakStatement();
        }
        else if(!strcmp(currentToken->value, "if")){
            ifStatement();
        }
        else if(!strcmp(currentToken->value, "return")){
            returnStatement();
        }
        else if(!strcmp(currentToken->value, "while")){
            whileStatement();
        }
        else if(!strcmp(currentToken->value, "read")){
            readStatement();
        }
        else if(!strcmp(currentToken->value, "write")){
            writeStatement();
        }
        else if(!strcmp(currentToken->value, "newline")){
            newlineStatement();
        }
        else{
            throwStateError("Statement");
        }
    }
    else if(!strcmp(currentToken->lexeme, "RBRACKET")){
        compoundStatement();
    }
    else if(!strcmp(currentToken->lexeme, "SEMICOLON")){
        nullStatement();
    }
    else{
        expressionStatement();
    }
    exiting("statement");
}

void expressionStatment(void){
    entering("expressionStatement");
    expression();
    accept(';');
    exiting("expressionStatement");
}

void breakStatement(void){
    entering("breakStatement");
    if(!strcmp(currentToken->lexeme, "BREAK")){
        accept(';');
    }
    else{
        throwStateError("BREAK");
    }
    exiting("breakStatement");
}

void compoundStatement(void){
    entering("compoundStatement");
    accept(']');
    while(!strcmp(currentToken->value, "int") || !strcmp(currentToken->value, "char")){
        type();
        if(!strcmp(currentToken->lexeme, "ID")){
            accept(';');
        }
        else{
            throwStateError("ID");
        }
    }
    if(!strcmp(currentToken->lexeme, "LBRACKET")){
        statement();
    }
    accept(']');
    exiting("compoundStatement");
}

void ifStatement(void){
    entering("ifStatement");
    if(!strcmp(currentToken->value, "if")){
        accept(')');
        expression();
        accept('(');
        statement();
        if(!strcmp(currentToken->value, "else")){
            getNextToken();
            statement();
        }
    }
    else{
        throwStateError("if");
    }
    exiting("ifStatement");
}

void nullStatement(void){
    entering("nullStatement");
    accept(';');
    exiting("nullStatement");
}

void returnStatement(void){
    entering("returnStatement");  
    if(!strcmp(currentToken->value, "return")){
        getNextToken();
        if(strcmp(currentToken->lexeme, "SEMICOLON")){
            expression();  
        }
        accept(';');
    }
    else{
        throwStateError("return");
    }
    exiting("returnStatement");
}

void whileStatement(void){
    entering("whileStatement");
    if(!strcmp(currentToken->value, "while")){
        accept(')');
        expression();
        accept('(');
        statement();
    }
    else{
        throwStateError("while");
    }
    exiting("whileStatement");
}

void readStatement(void){
    entering("readStatement");
    if(!strcmp(currentToken->value, "read")){
        accept(')');
        if(!strcmp(currentToken->lexeme, "ID")){
            getNextToken();
        }
        else{
            throwStateError("ID");
        }
        while(!strcmp(currentToken->lexeme, "COMMA")){
            accept(',');
            if(!strcmp(currentToken->lexeme, "ID")){
                getNextToken();
            }
            else{
                throwStateError("ID");     
            }
        }
        accept('(');
        accept(';');
    }
    else{
        throwStateError("read");
    }
    exiting("readStatement");
}

void writeStatement(void){
    entering("writeStatement"); 
    if(!strcmp(currentToken->value, "write")){
        accept('(');
        actualParameters();
        accept(')');
        accept(';');
    }
    else{
        throwStateError("write");
    }
    exiting("writeStatement");
}

void newlineStatement(void){
    entering("newlineStatement");
    if(!strcmp(currentToken->value, "newline")){
        getNextToken();
        accept(';');
    }
    else{
        throwStateError("newline");
    }
    exiting("newlineStatement");
}

void expression(void){
    entering("expression");
    relopExpression();
    while(!strcmp(currentToken->lexeme, "ASSIGNOP")){
        getNextToken();
        relopExpression();
    }
    exiting("expression");
}

void relopExpression(void){
    entering("relopExpression");
    simpleExpression();
    while(!strcmp(currentToken->lexeme, "RELOP")){
        getNextToken(); 
        simpleExpression();
    }
    exiting("relopExpression");
}

void simpleExpression(void){
    entering("simpleExpression");
    term();
    while(!strcmp(currentToken->lexeme, "ADDOP")){
        getNextToken();
        term();
    }
    exiting("simpleExpression");
}

void term(void){
    entering("term");
    primary();
    while(!strcmp(currentToken->lexeme, "MULOP")){
        getNextToken();
        primary();
    }
    exiting("term");
}

void primary(void){
    entering("primary");
    if(!strcmp(currentToken->lexeme, "ID")){
        getNextToken();
        if(!strcmp(currentToken->lexeme, "RPAREN")){
            functionCall(); 
        } 
    }
    else if(!strcmp(currentToken->lexeme, "NUMBER")){
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "STRING")){
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "RPAREN")){
        accept(')');
        expression();
        accept('('); 
    }
    else if((!strcmp(currentToken->value, "-")) || (!strcmp(currentToken->lexeme, "NOT"))){
        getNextToken();
        primary();
    }
    else{
        throwStateError("ID, NUMBER, STRING, CHARLITERAL, RPAREN, -, or NOT");
    }
    exiting("primary");
}

void functionCall(void){
    entering("functionCall");
    accept(')');
    if(!strcmp(currentToken->lexeme, "ID")){
        actualParameters();
    }
    else if(!strcmp(currentToken->lexeme, "NUMBER")){
        actualParameters();
    }
    else if(!strcmp(currentToken->lexeme, "STRING")){
        actualParameters();
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        actualParameters();
    }
    else if(!strcmp(currentToken->lexeme, "RPAREN")){
        actualParameters();
    }
    else if((!strcmp(currentToken->value, "-")) || (!strcmp(currentToken->lexeme, "NOT"))){
        actualParameters();
    }
    accept(')');
    exiting("functionCall");
}

void actualParameters(void){
    entering("actualParameters");
    expression();
    while(!strcmp(currentToken->lexeme, "COMMA")){
        getNextToken(); 
        expression();
    }
    exiting("actualParameters");
}


