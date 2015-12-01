/****************************************************************
 File: list_utils.list
 ------------------
 This file implements the interface given in list_utils.h.
 ***************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list_utils.h"
#include "list.h"
#include "parser.h"

/****************************************************************
 Static Function Declarations
 ----------------------------
 Declaring functions for use later.
 ****************************************************************/
static void printRecursiveList(List list);
static void printSymbol(List list);
static void printParenList(List list);
static List consHelper(List list);
static void exitInterpreter();
static int internalIsSymbol(List list);

/****************************************************************
 Function: eval(List list)
 ------------------------------------
 Evaluates a new list.
 ****************************************************************/
List eval(List list) {
    List local = list;
    if (internalIsSymbol(list)) return list;

    char * command = getSymbol(car(list));
    if (strcmp(command, "exit") == 0) exitInterpreter();
    else if (strcmp(command, "cons") == 0) return consHelper(list);
    else if (strcmp(command, "quote") != 0) local = eval(quote(list));

    if (strcmp(command, "quote") == 0) return quote(local);
    else if (strcmp(command, "car") == 0) return car(local);
    else if (strcmp(command, "cdr") == 0) return cdr(local);
    else if (strcmp(command, "symbol?") == 0) return isSymbol(local);
}

/****************************************************************
 ExitInterpreter(): Exits the interpreter.
 ****************************************************************/
static void exitInterpreter() {
    printf("Have a nice day!\n\n");
    exit(1);
}

/****************************************************************
 Function: quote(List list)
 ------------------------------------
 Returns the list.
 ****************************************************************/
List quote(List list) {
    return car(cdr(list));
}

/****************************************************************
 Function: car(List list)
 ---------------------------------------
 Returns the first element of the list.
 ****************************************************************/
List car(List list) {
    if (getFirst(list) != NULL) return getFirst(list);
    else return FALSE_LIST;
}

/****************************************************************
 Function: cdr(List list)
 ---------------------------------------
 Returns the rest of the elements of the list.
 ****************************************************************/
List cdr(List list) {
    if (getRest(list) != NULL) return getRest(list);
    else return FALSE_LIST;
}

/****************************************************************
 Function: consHelper(List list)
 ---------------------------------------
 Constructs a new list out of two lists. Parses a cons command.
 ****************************************************************/
static List consHelper(List list) {
    List list1 = eval(quote(list));
    List list2 = eval(quote(cdr(list)));

    if (list1 == FALSE_LIST && list2 == FALSE_LIST) return FALSE_LIST;
    else if (list1 == FALSE_LIST) return cons(list2, NULL);
    else if (list2 == FALSE_LIST) return cons(list1, NULL);
    else return cons(list1, list2);
}

/****************************************************************
 Function: cons(List list1, List list2)
 ---------------------------------------
 Constructs a new list out of two lists.
 ****************************************************************/
List cons(List list1, List list2) {
    List newList = createList();
    setFirst(newList, list1);
    setRest(newList, list2);
    return newList;
}

/****************************************************************
 Function: isSymbol(List list)
 ---------------------------------------
 Checks to see if a symbol is a symbol.
 ****************************************************************/
int internalIsSymbol(List list) {
    return getSymbol(list) != NULL;
}

/****************************************************************
 Function: isSymbol(List list)
 ---------------------------------------
 Checks to see if a list is a symbol.
 ****************************************************************/
List isSymbol(List list) {
    if (internalIsSymbol(list)) return TRUE_LIST;
    else return FALSE_LIST;
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
