#ifndef LEXICAL_H
#define LEXICAL_H

#define RESET        "\x1b[0m"
#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define YELLOW       "\x1b[33m"
#define BLUE         "\x1b[34m"
#define MAGENTA      "\x1b[35m"
#define CYAN         "\x1b[36m"
#define WHITE        "\x1b[37m"

static char *keyword[] = {"int","float","char","double","if","else","for","while","do","register","static","auto","extern","void","volatile","struct","long","short","break","continue","switch","case","const","default","enum","goto","return","signed","sizeof","typedef","union","unsigned","\0"};

static char *operator1[] ={"++","--",">=","<=","==","!=","+=","-=","/+","*=","&=","|=","^=","%=","<<",">>","&&","||","->","\0"};

static char operator2[] = {'+','-','*','/','|','&','~','=','%','!','^','(',')','>','<','\0'};

static char symbol[] = {'{','}','[',']',',',':',';','?','@','#','$','\0'};


typedef struct 
{
    char * source_file;
    FILE * fptr_source;
}LexInfo;

typedef enum
{
    SUCCESS,
    FAILURE,
    TRUE,
    NUM
}Status; 

Status start(LexInfo *lInfo);

Status openfile(LexInfo *lInfo);

Status main_operation(LexInfo *lInfo);

Status check_opt(char ch);

Status str_constant(char *token);

Status char_constant(char *token);

Status is_constant(char *token);

Status is_operator(char *token,LexInfo *lInfo);

Status is_keyword(char *token);

Status is_identifier(char *str,char ch);

Status is_unknown(char *str);

#endif

