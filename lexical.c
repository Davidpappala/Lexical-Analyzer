#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"lexical.h"

// Function to start the lexical analysis process
Status start(LexInfo *lInfo)
{
    openfile(lInfo); // Open the source file
    main_operation(lInfo); // Perform the main lexical operations
}

// Function to open the source file
Status openfile(LexInfo *lInfo)
{
    lInfo->fptr_source = fopen(lInfo->source_file,"r"); // Open file in read mode
    if(lInfo->fptr_source==NULL) // Check if file is opened successfully
        printf("File not opened\n");
} 

// Main function to handle lexical analysis
Status main_operation(LexInfo *lInfo)
{
    int b1=0,b2=0,B1=0,B2=0; // Counters for parentheses and braces
    char token[100]; // Buffer for storing tokens
    char str[25]; // Buffer for string operations
    int i=0; // Token buffer index
    char ch = fgetc(lInfo->fptr_source); // Read the first character from the file
    char chr; // To store the previous character
    int a=0,flag=0; // Flags for operations and conditions
    
    while(ch != EOF) // Loop until end of file is reached
    {
        flag = 0; // Reset flag for each character

        // Count and check matching parentheses
        if(ch == '(') b1++;
        else if(ch == ')') b2++;
        else if(b1 != b2 && ch == '\n') // Error if closing parenthesis is missing
        {
            printf(RED"error : missing ) \n"RESET);
            exit(0);
        }
       
        // Count braces
        if(ch == '{') B1++;
        else if(ch == '}') B2++;

        if(a != 0) ch = fgetc(lInfo->fptr_source); // Read next character
        a = 1;

        // Handle preprocessor directives
        if(ch == '#')
        {
            fscanf(lInfo->fptr_source,"%[^\n]",str); // Read the line
            if(strstr(str,"include")!=NULL || strstr(str,"define")!=NULL || strstr(str,"if")!=NULL) // Ignore valid preprocessor directives
            {
                str[0]='\0'; // Reset the string
                continue;
            }
            else
            {
                fseek(lInfo->fptr_source,-(strlen(str)),SEEK_CUR); // Move file pointer back
                str[0]='\0'; // Reset the string
                printf("Special character\t\t:#\n");
                continue;
            }
        }

        // Handle comments
        if(ch == '/')
        {
            char comment[100];
            int ind = 0;
            char ch2 = fgetc(lInfo->fptr_source); // Read next character
            char ch3='\0';

            if(ch2 == '/') // Single-line comment
            {
                fscanf(lInfo->fptr_source,"%[^\n]",comment); // Skip the comment line
                continue;
            } 
            else if(ch2 == '*') // Multi-line comment
            {
                while(1)
                {
                    ch = fgetc(lInfo->fptr_source); // Read characters
                    if(ch == '/' && ch3 == '*') // Check for closing "*/"
                        break;
                    ch3 = ch;
                }
                continue;
            } 
            else 
                fseek(lInfo->fptr_source,-1,SEEK_CUR); // If not a comment, revert file pointer
        }

        // Handle identifiers, keywords, and numbers
        if(isalpha(ch) || ch == '_' || ch == '.' || (ch >= 48 && ch <= 57))
        {
            while(1)
            {
                if(isalpha(ch) || ch == '_' || ch == '.' || (ch >= 48 && ch <= 57))
                {
                    token[i++] = ch; // Build the token
                }
                else if(i > 0)
                {
                    token[i] = '\0'; // Null-terminate the token
                    i = 0;

                    // Check if token is a keyword, identifier, or number
                    int res = is_keyword(token);
                    if(res == SUCCESS)
                    {
                        printf(GREEN"Keyword\t\t\t:  %s\n"RESET, token);
                        break;
                    }
                    else if(res == TRUE)
                    {
                        printf(YELLOW"Identifier\t\t:  %s\n"RESET, token);
                        break;
                    }
                    else if(res == NUM)
                    {
                        printf(BLUE"Numeric constant\t:  %s\n"RESET, token);
                        break;
                    } 
                    else
                    {
                        printf(RED"error : unknown token found\t:  %s\n"RESET, token);
                        exit(0);
                    } 
                }
                ch = fgetc(lInfo->fptr_source); // Read next character
            }
        }

        // Handle character constants
        if(ch == 39)
        {
            token[i++] = ch; // Add single quote
            while(i < 3)
            {
                ch = fgetc(lInfo->fptr_source);
                token[i++] = ch;
            }
            token[i] = '\0'; // Null-terminate
            i = 0;
            int res = char_constant(token); // Validate character constant
            if(res == SUCCESS)
            {
                printf(CYAN"Character constant\t:  %s\n"RESET, token);
                continue;
            }
            else if(res == FAILURE)
            {
                printf(RED"Missing character ' \n"RESET);
                exit(0);
            }
        }

        // Handle string literals
        if(ch == '"')
        {
            int d = 1;
            while(1)
            {
                token[i++] = ch; // Add character to token
                if(d == 2) break; // End of string
                if(ch == '\n') // Error if newline occurs before closing quote
                {
                    printf(RED"error : Missing \" \n"RESET);
                    exit(0);
                } 
                ch = fgetc(lInfo->fptr_source); // Read next character
                if(ch == '"') d++;
            }
            token[i] = '\0'; // Null-terminate
            i = 0;
            printf(CYAN"String literal\t\t:  %s\n"RESET, token);
        } 

        // Handle special characters
        for(int m = 0; symbol[m] != '\0'; m++)
        {
            if(ch == symbol[m])
            {
                printf("Special character\t:  %c\n", ch);
                break;
            }
        }

        // Handle operators
        for(int i = 0; operator2[i] != '\0'; i++)
        {
            if(ch == operator2[i])
            {
                flag++;
                break;
            } 
        }
        if(flag == 1)
        {
            flag = 0;
            char c = fgetc(lInfo->fptr_source); // Read next character
            token[0] = ch;
            token[1] = c;
            token[2] = '\0'; // Form a two-character operator
            int res = is_operator(token, lInfo);
            if(res == SUCCESS)
            {
                printf(MAGENTA"Operator\t\t:  %s\n"RESET, token);
                continue;
            }
            else if(res == TRUE)
            {
                printf(MAGENTA"Operator\t\t:  %c\n"RESET, token[0]);
                fseek(lInfo->fptr_source, -1, SEEK_CUR); // Revert file pointer
            } 
        }    
        chr = ch; // Update previous character
    }

    // Check for unmatched braces
    if(B1 != B2)
        printf(RED"error : missing } \n"RESET);
} 

// Validate character constants
Status char_constant(char *token)
{
    if(strlen(token) > 3) // Too many characters
        return FAILURE;
    else if(token[0] == 39 && token[2] == 39) // Correct format
        return SUCCESS;
    else
        return FAILURE;
} 

// Check if a token is a keyword, identifier, or number
Status is_keyword(char *token)
{
    int flag = 0, error = 0;
    if(token[0] >= 48 && token[0] <= 57) // Token starts with a digit
    {
        if(token[1] == 'x' || token[1] == 'X') // Hexadecimal number
        {
            for(int i = 2; token[i] != '\0'; i++)
            {
                if((token[i] >= 65 && token[i] <= 70) || (token[i] >= 97 && token[i] <= 102) || (token[i] >= 48 && token[i] <= 57))
                    flag = 0;
                else
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 1)
                return FAILURE;
            else
                return NUM; 
        } 
        else if(token[0] == 48) // Octal number
        {
            for(int i = 1; token[i] != '\0'; i++)
            {
                if(token[i] >= '0' && token[i] <= '7')
                    flag = 0;
                else
                {
                    flag = 1;
                    break;
                } 
            } 
            if(flag == 1)
                return FAILURE;
            else
                return NUM; 
        } 
        else // Decimal number
        {
            for(int j = 1; token[j] != '\0'; j++)
            {
                if(isalpha(token[j]))
                {
                    flag = 1;
                    break;
                } 
            } 
            if(flag == 1)
                return FAILURE;
            else
                return NUM;
        }
    } 
    else
    {
        // Check if the token matches any keyword
        for(int i = 0; keyword[i] != "\0"; i++)
        {
            if(strcmp(token, keyword[i]) == 0)
            {
                flag = 1;
                break;
            } 
        } 
        if(flag == 1)
            return SUCCESS; 
        else 
            return TRUE;
    }
} 

// Check if a token is an operator
Status is_operator(char *token, LexInfo *lInfo)
{
    int flag = 0;
    for(int j = 0; operator1[j] != "\0"; j++)
    {
        if(strcmp(token, operator1[j]) == 0) // Match with two-character operators
        {
            flag++;
            break;
        }
    }
    if(flag == 1)
    {
        return SUCCESS;
    } 
    else
    {
        return TRUE;
    } 
} 

