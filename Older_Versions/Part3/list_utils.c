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

// Helps in printing a list.
static void printRecursiveList(List list);
static void printSymbol(List list);
static void printParenList(List list);

// Helps with multivariable functions
static List consHelper(List list);
static List appendHelper(List list);
static List isEqualHelper(List list);
static List assocHelper(List list);

// Various control functions
static void exitInterpreter();
static int internalIsSymbol(List list);
static int initialized = 0;
static void initialize();

// Environment containing user defined vars
static List environment;

/****************************************************************
 Function: initialize()
 ------------------------------------
 Initializes the environment of the current session.
 ****************************************************************/
static void initialize() {
    environment = FALSE_LIST;
    initialized = 1;
}

/****************************************************************
 Function: eval(List list)
 ------------------------------------
 Evaluates a new list.
 ****************************************************************/
List eval(List list) {
    if (!initialized) initialize();
    List local = list;

    // symbol lookup
    if (list == TRUE_LIST) return TRUE_LIST;
    else if (list == FALSE_LIST) return FALSE_LIST;
    else if (internalIsSymbol(list)) return car(cdr(assoc(list, environment)));

    // get command of function
    char * command = getSymbol(car(list));

    // special exit function, two param functions, and recursion
    if (strcmp(command, "exit") == 0) exitInterpreter();
    else if (strcmp(command, "cons") == 0) return consHelper(list);
    else if (strcmp(command, "append") == 0) return appendHelper(list);
    else if (strcmp(command, "equal?") == 0) return isEqualHelper(list);
    else if (strcmp(command, "assoc") == 0) return assocHelper(list);
    else if (strcmp(command, "define") == 0) return define(list);
    else if (strcmp(command, "cond") == 0) return cond(cdr(list));
    else if (strcmp(command, "quote") != 0) local = eval(quote(list));

    // single param functions and function look up
    if (strcmp(command, "quote") == 0) return quote(local);
    else if (strcmp(command, "car") == 0) return car(local);
    else if (strcmp(command, "cdr") == 0) return cdr(local);
    else if (strcmp(command, "null?") == 0) return isNull(local);
    else if (strcmp(command, "symbol?") == 0) return isSymbol(local);
    else return car(cdr(assoc(car(list), environment)));
    
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
 Function: assocHelper(List list)
 ---------------------------------------
 Helps out the assoc function.
 ****************************************************************/
static List assocHelper(List list) {
    List key = eval(quote(list));
    List reference = eval(quote(cdr(list)));
    return assoc(key, reference);
}

List cond(List conditional) {
    if (conditional == FALSE_LIST) return FALSE_LIST;
    List first = car(conditional);
    List firstCond = car(first);

    if (eval(firstCond) == TRUE_LIST) return eval(car(cdr(first)));
    else return cond(cdr(conditional));
}

/****************************************************************
 Function: assoc(List key, List list)
 ---------------------------------------
 Checks a list of key value pairs for a certain key, and returns
 the pair if it is found. Returns the null list otherwise.
 ****************************************************************/
List assoc(List key, List list) {
    if (list == FALSE_LIST) return FALSE_LIST;
    else if (isEqual(key, car(car(list))) == TRUE_LIST) return car(list);
    else return assoc(key, cdr(list));
}

/****************************************************************
 Function: define(List list)
 ---------------------------------------
 Defines a new variable on the global environment. 
 ****************************************************************/
List define(List list) {
    List key = car(cdr(list));
    List definition = eval(car(cdr(cdr(list))));

    // constructs the entry
    List entry = createList();
    setFirst(entry, key);
    setRest(entry, createList());

    List rest = getRest(entry);
    setFirst(rest, definition);
    setRest(rest, NULL);

    // adds entry to global environment
    if (environment == FALSE_LIST) environment = cons(entry, NULL);
    else environment = cons(entry, environment);
    return key;
}

/****************************************************************
 Function: isEqualHelper(List list)
 ---------------------------------------
 Helps out with the isEqual function.
 ****************************************************************/
static List isEqualHelper(List list) {
    List list1 = eval(quote(list));
    List list2 = eval(quote(cdr(list)));
    return isEqual(list1, list2);
}

/****************************************************************
 Function: isEqual(List list1, List list2)
 ---------------------------------------
 Checks to see if two lists are equal.
 ****************************************************************/
List isEqual(List list1, List list2) {

    // TODO: Refactor

    if (isSymbol(list1) != isSymbol(list2)) {
        return FALSE_LIST;
    } else if (isSymbol(list1) == TRUE_LIST && isSymbol(list2) == TRUE_LIST)  {
        if (strcmp(getSymbol(list1), getSymbol(list2)) == 0) {
            return TRUE_LIST;
        } else {
            return FALSE_LIST;   
        } 
    }

    if (isEqual(car(list1), car(list2)) == TRUE_LIST &&
        isEqual(cdr(list1), cdr(list2)) == TRUE_LIST) return TRUE_LIST;
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
 Function: appendHelper(List list)
 ---------------------------------------
 Helps out with the append function.
 ****************************************************************/
static List appendHelper(List list) {
    List list1 = eval(quote(list));
    List list2 = eval(quote(cdr(list)));

    if (list1 == FALSE_LIST && list2 == FALSE_LIST) return FALSE_LIST;
    else if (list2 == FALSE_LIST) return append(list2, list1);
    else return append(list1, list2);
}

/****************************************************************
 Function: append(List list1, List list2)
 ---------------------------------------
 Appends one list to another.
 ****************************************************************/
List append(List list1, List list2) {
    if (list1 == FALSE_LIST) return list2;
    return cons(car(list1), append((cdr(list1)), list2));
}

/****************************************************************
 Function: isNull(List list)
 ---------------------------------------
 Checks to see if a list is the empty list (also false list)
 ****************************************************************/
List isNull(List list) {
    if (list == FALSE_LIST) return TRUE_LIST;
    else return FALSE_LIST;
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
