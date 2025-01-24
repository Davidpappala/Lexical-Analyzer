/***************************************************************************************************************************************************
*Author         :DAVID PAPPALA
*Date           :02/09/2024
*File           :lexer.h
*Title          :Header file.
*Description    :This file contains all enums structures and function prototypes and macro definitions that are required for this project.
****************************************************************************************************************************************************/
#ifndef LEXER_H
#define LEXER_H
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX_KEYWORDS 20                //macro for keyword array size.
#define MAX_TOKEN_SIZE 100              //macro for token size.

extern int c1;                          //extern for counting braces.
extern int c2;                          //extern for counting the paranthesis.

typedef enum {                          //enum for token type
    KEYWORD,                            //for keyword token type.
    OPERATOR,                           //for token type of operator.
    SPECIAL_CHARACTER,                  //for token type of special  character.
    CONSTANT,                           //for token type of special character.
    IDENTIFIER,                         //for token type of identifier.
    UNKNOWN,                            //for token type of unknown token.
    END_OF_FILE                         //for token type of end of file.
} TokenType;



typedef struct                            //struct to store the token and token type
{
    char lexeme[MAX_TOKEN_SIZE];            //array of char to store the string.
    TokenType type;                         //enum member to store token type.
} Token;
//function prototype to initialise file
void initializeLexer(const char* filename);  
//function prototype to get next token           
Token getNextToken();  
//function to check whether the token is keyword or not                                
int isKeyword(const char* str);  
//function to check whether the token is operator or not                   
int isOperator(char ch);
//function prototype to check whether the token is special character or not.                             
int isSpecialCharacter(char ch);
//function to check whether the token is constant or not
int isConstant(const char* str);
//function to check whether the token is identifier or not                       
int isIdentifier(const char* str);
//function to print the tokens                      
void ptoken(Token*);                                    

#endif

