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
static int initialized = 0;

/****************************************************************
 Static Function Declarations
 ----------------------------
 Declaring functions for use later.
 ****************************************************************/
static void readToken();
static List closeExpression(List c, int depth);
static List readSExpression(int depth);
static void initialize();

/****************************************************************
 S_Expression(): See parser.h for documentation.
 ***************************************************************/
List S_Expression() {
    if (initialized == 0) initialize();
    readToken();
    return readSExpression(0);
}

/****************************************************************
 initialize(): Initializes the parser and makes constant lists.
 ***************************************************************/
static void initialize() {
    initialized = 1;
    startTokens(20);

    TRUE_LIST = createList();
    setSymbol(TRUE_LIST, "#t");

    FALSE_LIST = createList();
    setSymbol(FALSE_LIST, "()");
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
    } else if (strcmp(token, "#f") == 0 || strcmp(token, "()") == 0) {
        return closeExpression(FALSE_LIST, depth);
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
