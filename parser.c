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
#include "list.h"

/****************************************************************
 Data members
 ------------
 token: A string (character array) that houses the last token
        read in by the lexer.
 ****************************************************************/
static char token[20];

/****************************************************************
 Static Function Declarations
 ----------------------------
 Declaring functions for use later.
 ****************************************************************/
static void readToken();
static List closeExpression(List c, int depth);
static List readSExpression(int depth);

/****************************************************************
 S_Expression(): See parser.h for documentation.
 ***************************************************************/
List S_Expression() {
    startTokens(20);
    readToken();
    return readSExpression(0);
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
static List readSExpression(int depth) {
    List local, temp;

    if (strcmp(token, "(") == 0) {
        local = createList();
        readToken();
        setFirst(local, readSExpression(depth + 1));
        temp = local;

        while (strcmp(token, ")") != 0) {
            setRest(temp, createList());
            temp = getRest(temp);
            setFirst(temp, readSExpression(depth + 1));
        }
    
        setRest(temp, NULL);
        return closeExpression(local, depth);
    } else {
        local = createList();
        setSymbol(local, token);
        return closeExpression(local, depth);
    }
}

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
 Function: closeExpression(List c, int depth)
 ---------------------------------------------
 Private function that closes and returns an expression. If
 there is more to parse, also reads in the next token.
 ****************************************************************/
static List closeExpression(List c, int depth) {
    if (depth != 0) readToken();
    return c;
}
