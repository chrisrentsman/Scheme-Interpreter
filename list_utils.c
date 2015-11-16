/****************************************************************
 File: list_utils.c
 ------------------
 This file implements the interface given in list_utils.h.
 ***************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "list_utils.h"
#include "list.h"

/****************************************************************
 Static Function Declarations
 ----------------------------
 Declaring functions for use later.
 ****************************************************************/
static void printRecursiveList(List c);
static void printSymbol(List c);
static void printParenList(List c);

/****************************************************************
 Function: printList(List c)
 ------------------------------------
 Prints out a list.
 ****************************************************************/
void printList(List c) {
    if (getSymbol(c) != NULL) printSymbol(c);
    else printParenList(c); 
}

/****************************************************************
 Function: printRecursiveList(List c)
 ------------------------------------
 Private helper method that prints out the content of a list
 through recursion.
 ****************************************************************/
static void printRecursiveList(List c) {
    if (c == NULL) return;

    printList(getFirst(c));
    if (getRest(c) != NULL) printf(" "); 
    printRecursiveList(getRest(c));
}

/****************************************************************
 Function: printSymbol(List c)
 ------------------------------------
 Prints out a symbol.
 ****************************************************************/
static void printSymbol(List c) {
    printf("%s", getSymbol(c));
}

/****************************************************************
 Function: printParenList(List c)
 ------------------------------------
 Prints out a parenthesized list.
 ****************************************************************/
static void printParenList(List c) {
    printf("("); 
    printRecursiveList(c);
    printf(")"); 
}
