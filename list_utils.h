/****************************************************************
 File: list_utils.h
 ------------------
 Commonly used Scheme functions are defined in this file.
 ***************************************************************/

#ifndef LIST_UTILS
#define LIST_UTILS

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/****************************************************************
 Function: eval(List list)
 ----------------------------
 Given a list, evaluates it.
 */
List eval(List list);

/****************************************************************
 Function: quote(List list)
 ----------------------------
 Given a list, returns it.
 */
List quote(List list);

/****************************************************************
 Function: cons(List list1, List list2)
 ---------------------------------------
 Constructs a new list out of two lists.
 */
List cons(List list1, List list2);

/****************************************************************
 Function: cond(List list)
 ---------------------------------------
 Evaluates a conditional.
 */
List cond(List conditional, List env);

/****************************************************************
 Function: and(List list)
 ---------------------------------------
 Returns true if all elements of a list are true, false otherwise.
 */
List and(List list, List env);

/****************************************************************
 Function: or(List list)
 ---------------------------------------
 Returns true if at least one element of a list is true.
 */
List or(List list, List env);

/****************************************************************
 Function: length(List list)
 ---------------------------------------
 Returns the length of the list.
 */
List length(List list, List env);

/****************************************************************
 Function: addList(List list)
 ---------------------------------------
 Adds a list of numbers together.
 */
List addList(List list, List env);

/****************************************************************
 Function: multiplyList(List list)
 ---------------------------------------
 Multiplies a list of numbers together.
 */
List multiplyList(List list, List env);

/****************************************************************
 Function: subtractList(List list)
 ---------------------------------------
 Subtracts the cdr of a list from the car.
 */
List subtractList(List list, List env);

/****************************************************************
 Function: lessThan(List list)
 ---------------------------------------
 Checks to see if a list is strictly increasing.
 */
List lessThan(List list, List env);

/****************************************************************
 Function: greaterThan(List list)
 ---------------------------------------
 Checks to see if a list is strictly decreasing.
 */
List greaterThan(List list, List env);

/****************************************************************
 Function: append(List list1, List list2)
 ---------------------------------------
 Appends one list to another
 */
List append(List list1, List list2);

/****************************************************************
 Function: isNull(list)
 ---------------------------------------
 Checks to see if a list is equal to the null list.
 */
List isNull(List list);

/****************************************************************
 Function: define(List list)
 ---------------------------------------
 Defines a new variable in the global environment.
 */
List define(List list, List env);

/****************************************************************
 Function: isEqual(List list1, List list2)
 ---------------------------------------
 Checks to see if tw lists are equal.
 */
List isEqual(List list1, List list2);

/****************************************************************
 Function: assoc(List key, List list)
 ---------------------------------------
 Returns the associated pair given a key.
 */
List assoc(List key, List list);

/****************************************************************
 Function: car(List list)
 ----------------------------
 Given a list, returns the first element.
 */
List car(List list);

/***************************************************************
 Function: cadr(List list)
 ---------------------------------------
 Returns the second element of the list.
 */
List cadr(List list);

/***************************************************************
 Function: caddr(List list)
 ---------------------------------------
 Returns the third element of the list.
 */
List caddr(List list);

/***************************************************************
 Function: cadddr(List list)
 ---------------------------------------
 Returns the fourth element of the list.
 */
List cadddr(List list);

/***************************************************************
 Function: caddddr(List list)
 ---------------------------------------
 Returns the fifth element of the list.
 */
List caddddr(List list);

/****************************************************************
 Function: last(List list)
 ---------------------------------------
 Returns the last element of the list.
 */
List last(List list);

/****************************************************************
 Function: paramList(List list)
 ---------------------------------------
 Constructs a list out of all the parameters.
 */
List paramList(List list, List env);

/****************************************************************
 Function: isSymbol(List list)
 ---------------------------------------
 Checks to see if a list is a symbol.
 */
List isSymbol(List list);

/****************************************************************
 Function: isList(List list)
 ---------------------------------------
 Checks to see if a list is a list.
 */
List isList(List list);

/****************************************************************
 Function: isNumber(List list)
 ---------------------------------------
 Checks to see if a list is a number.
 */
List isNumber(List list, List env);

/****************************************************************
 Function: cdr(List list)
 ----------------------------
 Given a list, returns everything but the first element.
 */
List cdr(List list);

/****************************************************************
 Function: printList(List list)
 ----------------------------
 Given a list, prints it out.
 */
void printList(List list);

#endif
