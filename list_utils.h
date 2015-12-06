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

List isEqual(List list1, List list2);

/****************************************************************
 Function: car(List list)
 ----------------------------
 Given a list, returns the first element.
 */
List car(List list);

/****************************************************************
 Function: isSymbol(List list)
 ---------------------------------------
 Checks to see if a list is a symbol.
 */
List isSymbol(List list);

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
