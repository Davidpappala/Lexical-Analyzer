/*
 * NAME :David.P
 * DATE :02/09/24
 * DESCRIPTION : Developed a Lexical Analyzer to parse source code, identify and classify tokens (keywords, operators, literals, etc.), and detect syntax errors like mismatch			ed brackets or invalid tokens.
 */

#include<stdio.h>
#include<string.h>
#include"lexical.h"

// Main function to initialize the lexical analysis process
int main(int argc, char *argv[])
{
    // Check if the correct number of arguments is passed
    if(argc != 2)
    {
        printf("./a.out [file name]\n"); // Print usage message if incorrect
        return 0; // Exit the program
    }

    LexInfo lInfo; // Define a structure to hold lexical analysis information

    lInfo.source_file = argv[1]; // Assign the input file name to the structure

    printf("--------------------------------------------\n");

    start(&lInfo); // Start the lexical analysis process

    printf("--------------------------------------------\n");

    return 0; // Indicate successful execution
}

