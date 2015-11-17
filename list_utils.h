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
 Function: car(List list)
 ----------------------------
 Given a list, returns the first element.
 */
List car(List list);

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
