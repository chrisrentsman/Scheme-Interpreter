/****************************************************************
 File: list_utils.list
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
static void printRecursiveList(List list);
static void printSymbol(List list);
static void printParenList(List list);

/****************************************************************
 Function: eval(List list)
 ------------------------------------
 Evaluates a new list.
 ****************************************************************/
List eval(List list) {
    if (list == NULL) return;

    return list;
}

/****************************************************************
 Function: quote(List list)
 ------------------------------------
 Returns the list.
 ****************************************************************/
List quote(List list) {
    return list;
}

/****************************************************************
 Function: car(List list)
 ---------------------------------------
 Returns the first element of the list.
 ****************************************************************/
List car(List list) {
    return getFirst(list);
}

/****************************************************************
 Function: cdr(List list)
 ---------------------------------------
 Returns the rest of the elements of the list.
 ****************************************************************/
List cdr(List list) {
    return getRest(list);
}

/****************************************************************
 Function: isSymbol(List list)
 ---------------------------------------
 Checks to see if a symbol is a symbol.
 ****************************************************************/
int isSymbol(List list) {
    return (getSymbol(list) != NULL) ? 1 : 0;  
}

/****************************************************************
 Function: printList(List list)
 ------------------------------------
 Prints out a list.
 ****************************************************************/
void printList(List list) {
    if (getSymbol(list) != NULL) printSymbol(list);
    else printParenList(list); 
}

/****************************************************************
 Function: printRecursiveList(List list)
 ------------------------------------
 Private helper method that prints out the content of a list
 through recursion.
 ****************************************************************/
static void printRecursiveList(List list) {
    if (list == NULL) return;

    printList(getFirst(list));
    if (getRest(list) != NULL) printf(" "); 
    printRecursiveList(getRest(list));
}

/****************************************************************
 Function: printSymbol(List list)
 ------------------------------------
 Prints out a symbol.
 ****************************************************************/
static void printSymbol(List list) {
    printf("%s", getSymbol(list));
}

/****************************************************************
 Function: printParenList(List list)
 ------------------------------------
 Prints out a parenthesized list.
 ****************************************************************/
static void printParenList(List list) {
    printf("("); 
    printRecursiveList(list);
    printf(")"); 
}
