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
static List consHelper(List list, List environment);
static List appendHelper(List list, List environment);
static List isEqualHelper(List list, List environment);
static List assocHelper(List list, List environment);
static List defineSymbol(List key, List definition);
static List evalHelper(List list, List environment);

// Various control functions
static List userDefinedFunction(List list, List environment);
static List augmentEnvironment(List userParams, List params, List environment);
static List createKeyValuePair(List key, List value);
static void exitInterpreter();
static int internalIsSymbol(List list);
static List convertIntToList(int n);
static int convertToInt(List list);
static int initialized = 0;
static void initialize();

// Environment containing user defined vars
static List environment;

/****************************************************************
 Evaluation Function
 ----------------------------
 Functions used to evaluate both user-defined and standard
 functions. Includes initialization and definition.
 ****************************************************************/

/**
 * Function: eval(List list)
 * ------------------------------------
 * Evaluates an expression.
 */
List eval(List list) {
    if (!initialized) initialize();
    return evalHelper(list, environment);
}

/**
 * Function: initialize()
 * ------------------------------------
 * Initializes the environment of the current session.
 */
static void initialize() {
    environment = FALSE_LIST;
    initialized = 1;
}

/**
 * Function: evalHelper(List list, List localEnv)
 * ---------------------------------------------------
 * Evaluates an expression given an environment.
 */
static List evalHelper(List list, List localEnv) {
    List local = list;

    // symbol lookup
    if (list == TRUE_LIST) return TRUE_LIST;
    else if (list == FALSE_LIST) return FALSE_LIST;
    else if (isNumber(list, localEnv) == TRUE_LIST) return list;
    else if (internalIsSymbol(list)) return car(cdr(assoc(list, localEnv)));

    // get command of function
    char * command = getSymbol(car(list));

    // special exit function, two param functions, and recursion
    if (strcmp(command, "exit") == 0) exitInterpreter();
    else if (strcmp(command, "cons") == 0) return consHelper(list, localEnv);
    else if (strcmp(command, "append") == 0) return appendHelper(list, localEnv);
    else if (strcmp(command, "equal?") == 0 || strcmp(command, "=") == 0) return isEqualHelper(list, localEnv);
    else if (strcmp(command, "assoc") == 0) return assocHelper(list, localEnv);
    else if (strcmp(command, "define") == 0) return define(list, localEnv);
    else if (strcmp(command, "cond") == 0) return cond(cdr(list), localEnv);
    else if (strcmp(command, "environment") == 0) return environment;
    else if (strcmp(command, "length") == 0) return length(cdr(list), localEnv);
    else if (strcmp(command, "list") == 0) return paramList(cdr(list), localEnv);
    else if (strcmp(command, "+") == 0) return addList(cdr(list), localEnv);
    else if (strcmp(command, "*") == 0) return multiplyList(cdr(list), localEnv);
    else if (strcmp(command, "-") == 0) return subtractList(cdr(list), localEnv);
    else if (strcmp(command, "<") == 0) return lessThan(cdr(list), localEnv);
    else if (strcmp(command, ">") == 0) return greaterThan(cdr(list), localEnv);
    else if (strcmp(command, "AND") == 0) return and(cdr(list), localEnv);
    else if (strcmp(command, "OR") == 0) return or(cdr(list), localEnv);
    else if (strcmp(command, "quote") != 0) local = evalHelper(quote(list), localEnv);

    // single param functions and function look up
    if (strcmp(command, "quote") == 0) return quote(local);
    else if (strcmp(command, "car") == 0) return car(local);
    else if (strcmp(command, "cdr") == 0) return cdr(local);
    else if (strcmp(command, "cadr") == 0) return cadr(local);
    else if (strcmp(command, "caddr") == 0) return caddr(local);
    else if (strcmp(command, "cadddr") == 0) return cadddr(local);
    else if (strcmp(command, "caddddr") == 0) return caddddr(local);
    else if (strcmp(command, "last") == 0) return last(local);
    else if (strcmp(command, "null?") == 0 || strcmp(command, "NOT") == 0) return isNull(local);
    else if (strcmp(command, "list?") == 0) return isList(local);
    else if (strcmp(command, "number?") == 0) return isNumber(evalHelper(car(cdr(list)), localEnv), localEnv);
    else if (strcmp(command, "symbol?") == 0) return isSymbol(local);
    else return userDefinedFunction(list, localEnv);
}

/**
 * Function: userDefinedFunction(List list, List localEnv)
 * ----------------------------------------------------------
 * Evaluates a new user defined function given a list and
 * an local environment.
 */
static List userDefinedFunction(List list, List environment) {
    List pair = assoc(car(list), environment);
    List params = cdr(car(cdr(car(cdr(pair)))));
    List definition = car(cdr(cdr(car(cdr(pair)))));
    List userParams = cdr(list);
    List augmented = augmentEnvironment(userParams, params, environment);
    return evalHelper(definition, augmented);
}

/**
 * Function: augmentEnvironment(List userParams, 
 *                   List params, List environment)
 * ----------------------------------------------------------
 * Augments a given environment with new variables for user
 * defined functions.
 */
static List augmentEnvironment(List userParams, List params, List environment) {
    List newPairs = FALSE_LIST;
    List augmented = FALSE_LIST;

    // binds parameters to names
    while (userParams != FALSE_LIST) {
        List key = car(params);
        List value = evalHelper(car(userParams), environment);
        List pair = createKeyValuePair(key, value);
        if (newPairs == FALSE_LIST) newPairs = cons(pair, NULL);
        else newPairs = cons(pair, newPairs);
        params = cdr(params);
        userParams = cdr(userParams);
    }

    // adds to new environment
    while (newPairs != FALSE_LIST) {
        if (augmented == FALSE_LIST) augmented = cons(car(newPairs), environment);
        else augmented = cons(car(newPairs), augmented);
        newPairs = cdr(newPairs);
    }

    return augmented;
}

/**
 * Function: assocHelper(List list)
 * ---------------------------------------
 * Helps out the assoc function.
 */
static List assocHelper(List list, List environment) {
    List key = evalHelper(quote(list), environment);
    List reference = evalHelper(quote(cdr(list)), environment);
    return assoc(key, reference);
}

/**
 * Function: assoc(List key, List list)
 * ---------------------------------------
 * Checks a list of key value pairs for a certain key, and returns
 * the pair if it is found. Returns the null list otherwise.
 */
List assoc(List key, List list) {
    if (list == FALSE_LIST) return FALSE_LIST;
    else if (isEqual(key, car(car(list))) == TRUE_LIST) return car(list);
    else return assoc(key, cdr(list));
}

/**
 * Function: define(List list)
 * ---------------------------------------
 * Defines a new variable on the global environment. 
 */
List define(List list, List environment) {
    List key = car(cdr(list));
    List definition = evalHelper(car(cdr(cdr(list))), environment);

    if (isSymbol(key) == TRUE_LIST) return defineSymbol(key, definition);
    else if (isList(key) == TRUE_LIST) return defineSymbol(car(key), list);
}

/**
 * Function: defineSymbol(List key, List definition)
 * --------------------------------------------------
 * Defines a new variable on the global environment. 
 */
static List defineSymbol(List key, List definition) {
    List entry = createKeyValuePair(key, definition);
    if (environment == FALSE_LIST) environment = cons(entry, NULL);
    else environment = cons(entry, environment);
    return key;
}

/****************************************************************
 Data Functions
 ----------------------------
 Functions used to get data about an expression. This includes
 functions such as quote, car, and cdr.
 ****************************************************************/

/**
 * Function: quote(List list)
 * ------------------------------------
 * Returns the list.
 */
List quote(List list) {
    return car(cdr(list));
}

/**
 * Function: car(List list)
 * ---------------------------------------
 * Returns the first element of the list.
 */
List car(List list) {
    if (getFirst(list) != NULL) return getFirst(list);
    else return FALSE_LIST;
}

/**
 * Function: cdr(List list)
 * ---------------------------------------
 * Returns the rest of the elements of the list.
 */
List cdr(List list) {
    if (getRest(list) != NULL) return getRest(list);
    else return FALSE_LIST;
}

/**
 * Function: cadr(List list)
 * ---------------------------------------
 * Returns the second element of the list.
 */
List cadr(List list) {
    return car(cdr(list));
}

/**
 * Function: caddr(List list)
 * ---------------------------------------
 * Returns the third element of the list.
 */
List caddr(List list) {
    return car(cdr(cdr(list)));
}

/**
 * Function: cadddr(List list)
 * ---------------------------------------
 * Returns the fourth element of the list.
 */
List cadddr(List list) {
    return car(cdr(cdr(cdr(list))));
}

/**
 * Function: caddddr(List list)
 * ---------------------------------------
 * Returns the fifth element of the list.
 */
List caddddr(List list) {
    return car(cdr(cdr(cdr(cdr(list)))));
}

/**
 * Function: last(List list)
 * ---------------------------------------
 * Returns the last element of the list.
 */
List last(List list) {
    if (cdr(list) == FALSE_LIST) return car(list);
    else return last(cdr(list));
}

/**
 * Function: length(List list, List env)
 * ---------------------------------------
 * Returns the length of a list (number of elements).
 */
List length(List list, List env) {
    list = evalHelper(car(list), env);
    int length = 0;
    while (list != FALSE_LIST) {
        length++;
        list = cdr(list);
    }

    return convertIntToList(length);
}

/****************************************************************
 Math Functions
 ----------------------------
 Functions used to do math.
 ****************************************************************/

/**
 * Function: addList(List list)
 * ---------------------------------------
 * Adds a list of numbers together.
 */
List addList(List list, List env) {
    int sum = 0;  
    while (list != FALSE_LIST) {
        sum += convertToInt(evalHelper(car(list), env));
        list = cdr(list);
    }

    return convertIntToList(sum);
}

/**
 * Function: multiplyList(List list)
 * ---------------------------------------
 * Adds a list of numbers together.
 */
List multiplyList(List list, List env) {
    int product = 1;  
    while (list != FALSE_LIST) {
        product = product * convertToInt(evalHelper(car(list), env));
        list = cdr(list);
    }

    return convertIntToList(product);
}

/**
 * Function: subtractList(List list)
 * ---------------------------------------
 * Subtracts the cdr of the list from the car.
 */
List subtractList(List list, List env) {
    int start = convertToInt(evalHelper(car(list), env));
    int difference = start;
    list = cdr(list);

    while (list != FALSE_LIST) {
        difference -= convertToInt(evalHelper(car(list), env));
        list = cdr(list);
    }

    return convertIntToList(difference);
}

/****************************************************************
 Construction Functions
 ----------------------------
 Functions used to construct new lists. Includes cons, append.
 ****************************************************************/

/**
 * Function: consHelper(List list)
 * ---------------------------------------
 * Constructs a new list out of two lists. Parses a cons command.
 */
static List consHelper(List list, List env) {
    List list1 = evalHelper(quote(list), env);
    List list2 = evalHelper(quote(cdr(list)), env);

    if (list1 == FALSE_LIST && list2 == FALSE_LIST) return FALSE_LIST;
    else if (list1 == FALSE_LIST) return cons(list2, NULL);
    else if (list2 == FALSE_LIST) return cons(list1, NULL);
    else return cons(list1, list2);
} 

/**
 * Function: cons(List list1, List list2)
 * ---------------------------------------
 * Constructs a new list out of two lists.
 */
List cons(List list1, List list2) {
    List newList = createList();
    setFirst(newList, list1);
    setRest(newList, list2);
    return newList;
}

/**
 * Function: appendHelper(List list)
 * ---------------------------------------
 * Helps out with the append function.
 */
static List appendHelper(List list, List env) {
    List list1 = evalHelper(quote(list), env);
    List list2 = evalHelper(quote(cdr(list)), env);

    if (list1 == FALSE_LIST && list2 == FALSE_LIST) return FALSE_LIST;
    else if (list2 == FALSE_LIST) return append(list2, list1);
    else return append(list1, list2);
}

/**
 * Function: append(List list1, List list2)
 * ---------------------------------------
 * Appends one list to another.
 */
List append(List list1, List list2) {
    if (list1 == FALSE_LIST) return list2;
    return cons(car(list1), append((cdr(list1)), list2));
}

/**
 * Function: paramList(List list)
 * ---------------------------------------
 * Constructs a list out of all the parameters.
 */
List paramList(List list, List env) {
    List newList = createList(); 
    List temp = newList;

    while (list != FALSE_LIST) {
        List newAtom = evalHelper(car(list), env);
        setFirst(temp, newAtom);

        if (cdr(list) != FALSE_LIST) {
            setRest(temp, createList());
            temp = getRest(temp);
        }

        list = cdr(list);
    }

    return newList;
}

/****************************************************************
 Boolean Functions
 ----------------------------
 Functions used with booleans and conditionals. Includes methods
 like cond, symbol?, null?, and others.
 ****************************************************************/

/**
 * Function: cond(List conditional, List env)
 * -------------------------------------------
 * Given a set of conditions, returns the value of the
 * first true condition. Much like a switch statement.
 */
List cond(List conditional, List env) {
    if (conditional == FALSE_LIST) return FALSE_LIST;
    List first = car(conditional);
    List firstCond = car(first);

    if (evalHelper(firstCond, env) == TRUE_LIST) return evalHelper(car(cdr(first)), env);
    else return cond(cdr(conditional), env);
}

/**
 * Function: isEqualHelper(List list)
 * ---------------------------------------
 * Helps out with the isEqual function.
 */
static List isEqualHelper(List list, List env) {
    List list1 = evalHelper(quote(list), env);
    List list2 = evalHelper(quote(cdr(list)), env);
    return isEqual(list1, list2);
}

/**
 * Function: isEqual(List list1, List list2)
 * ---------------------------------------
 * Checks to see if two lists are equal.
 */
List isEqual(List list1, List list2) {

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

/**
 * Function: isNull(List list)
 * ---------------------------------------
 * Checks to see if a list is the empty list (also false list)
 */
List isNull(List list) {
    if (list == FALSE_LIST) return TRUE_LIST;
    else return FALSE_LIST;
}

/**v)
 * Function: isSymbol(List list)
 * ---------------------------------------
 * Checks to see if a list is a symbol.
 */
List isSymbol(List list) {
    if (internalIsSymbol(list)) return TRUE_LIST;
    else return FALSE_LIST;
}

/**
 * Function: isList(List list)
 * ---------------------------------------
 * Checks to see if a list is a List.
 */
List isList(List list) {
    if (isSymbol(list) == TRUE_LIST) return FALSE_LIST;
    else return TRUE_LIST;
}

/**
 * Function: isNumber(List list)
 * ---------------------------------------
 * Checks to see if a list is a Number.
 */
List isNumber(List list, List env) {
    if (isList(list) == TRUE_LIST) return FALSE_LIST;

    char * leftover;
    char * symbol = getSymbol(list);
    int num = strtol(symbol, &leftover, 10);
    int len = strlen(leftover);

    if (len == 0) return TRUE_LIST;
    else return FALSE_LIST;
}

/**
 * Function: lessThan(List list)
 * ---------------------------------------
 * Checks to see if a list is strictly increasing.
 */
List lessThan(List list, List env) {
    while (cdr(list) != FALSE_LIST) {
        int val1 = convertToInt(evalHelper(car(list), env));
        int val2 = convertToInt(evalHelper(cadr(list), env));
        
        if (val1 >= val2) return FALSE_LIST;
        else list = cdr(list);
    }

    return TRUE_LIST;
}

/**
 * Function: greaterThan(List list)
 * ---------------------------------------
 * Checks to see if a list is strictly decreasing.
 */
List greaterThan(List list, List env) {
    while (cdr(list) != FALSE_LIST) {
        int val1 = convertToInt(evalHelper(car(list), env));
        int val2 = convertToInt(evalHelper(cadr(list), env));
        
        if (val1 <= val2) return FALSE_LIST;
        else list = cdr(list);
    }

    return TRUE_LIST;
}

/**
 * Function: and(List list)
 * ---------------------------------------
 *  Checks to see if all elements of a list are true.
 */
List and(List list, List env) {
    while (list != FALSE_LIST) {
        if (evalHelper(car(list), env) == FALSE_LIST) return FALSE_LIST;
        else list = cdr(list);
    }

    return TRUE_LIST;
}

/**
 * Function: or(List list)
 * ---------------------------------------
 * Checks to see if at least one element is true.
 */
List or(List list, List env) {
    while (list != FALSE_LIST) {
        if (evalHelper(car(list), env) == TRUE_LIST) return TRUE_LIST;
        else list = cdr(list);
    }

    return FALSE_LIST;
}

/****************************************************************
 Print Functions
 ----------------------------
 Functions used to print out an expression or list.
 ****************************************************************/

/**
 * Function: printList(List list)
 * ------------------------------------
 * Prints out a list.
 */
void printList(List list) {
    if (getSymbol(list) != NULL) printSymbol(list);
    else printParenList(list); 
}

/**
 * Function: printRecursiveList(List list)
 * ------------------------------------
 * Private helper method that prints out the content of a list
 * through recursion.
 */
static void printRecursiveList(List list) {
    if (list == NULL) return;

    printList(getFirst(list));
    if (getRest(list) != NULL) printf(" "); 
    printRecursiveList(getRest(list));
}

/**
 * Function: printSymbol(List list)
 * ------------------------------------
 * Prints out a symbol.
 */
static void printSymbol(List list) {
    printf("%s", getSymbol(list));
    }

/**
 * Function: printParenList(List list)
 * ------------------------------------
 * Prints out a parenthesized list.
 */
static void printParenList(List list) {
    printf("("); 
    printRecursiveList(list);
    printf(")"); 
}

/****************************************************************
 Misc. Helper Functions
 ----------------------------
 Functions that accomplish something small to help out the
 rest of the interpreter.
 ****************************************************************/

/**
 * Function: createKeyValuePair(List key, List value)
 * ----------------------------------------------------------
 * Given a key and a value, creates a key value pair like below:
 *
 *  (key value)
 *
 */
static List createKeyValuePair(List key, List value) {
    List pair = createList(); 
    setFirst(pair, key);
    setRest(pair, createList());
    setFirst(getRest(pair), value);
    setRest(getRest(pair), NULL);
    return pair;
}

/**
 * Function: convertToInt(List list)
 * ---------------------------------------
 * Converts a list to an integer.
 */
static int convertToInt(List list) {
    char * leftover;
    char * symbol = getSymbol(list);
    int num = strtol(symbol, &leftover, 10);
    return num;
}

/**
 * Function: convertIntToList(List list)
 * ---------------------------------------
 * Converts an integer to a list.
 */
static List convertIntToList(int n) {
    char string[256];
    sprintf(string, "%i", n);
    List number = createList();
    setSymbol(number, string);
    return number;
}

/**
 * Function: internalIsSymbol(List list)
 * ---------------------------------------
 * Checks to see if a symbol is a symbol. Returns a boolean.
 */
int internalIsSymbol(List list) {
    return getSymbol(list) != NULL;
}

/**
 * Function: ExitInterpreter()
 * ----------------------------
 * Exits the interpreter.
 */
static void exitInterpreter() {
    printf("Have a nice day!\n\n");
    exit(1);
}
