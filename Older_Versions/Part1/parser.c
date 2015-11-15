/****************************************************************
 File: parser.c
 -------------
 This file implements the interface given in parser.h.
 ***************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"

/****************************************************************
 Data members
 ------------
 token: A string (character array) that houses the last token
        read in by the lexer.
 ****************************************************************/
static char token[20];

/****************************************************************
 Function: readToken()
 ---------------------
 Private function to make code more understandable. Reads in
 a token using the lexer's getToken() method and applies that
 token's value to the token variable above.
 ****************************************************************/
static void readToken() {
    strcpy(token, getToken());
}

/****************************************************************
 Function: printSpaces(int num)
 ------------------------------
 Private function that takes in an integer and prints out
 that many spaces without causing a new line. Helpful for
 representing the different levels and depths within the
 parse tree.
 ****************************************************************/
static void printSpaces(int num) {
    int i;
    for (i = 0; i < num; i++) {
        printf(" ");
    }
}

/****************************************************************
 Function: printSpaces(int depth)
 --------------------------------
 Closes the current expression, either by reading in the next
 token to analyze, or by ending the entire expression
 altogether if the current depth of the expression is 0 (the
 starting point).
 ****************************************************************/
static void closeExpression(int depth) {
    if (depth == 0) {
        printf("\n");
    } else {
        readToken();
    }
}

/****************************************************************
 Function: readSExpression(int depth)
 ------------------------------------
 Private recursive helper method that reads in data from the
 user and prints out the parse tree for the user provided S
 expression. It keeps track of the depth of the recursion to
 provide the correct number of spaces for each level within
 the parse tree.
 ****************************************************************/
static void readSExpression(int depth) {
    printSpaces(depth);
    printf("S_Expression\n");

    if (strcmp(token, "(") == 0) {
        printSpaces(depth);
        printf("(\n"); 

        readToken();
        readSExpression(depth + 2);
        while (strcmp(token, ")") != 0) {
            readSExpression(depth + 2);
        }

        printSpaces(depth);
        printf(")\n");
        closeExpression(depth);
    } else {
        printSpaces(depth + 2);
        printf("%s\n", token); 
        closeExpression(depth);
    }
}


/****************************************************************
 S_Expression(): See parser.h for documentation.
 ***************************************************************/
void S_Expression() {
    startTokens(20);
    readToken();
    readSExpression(0);
}

