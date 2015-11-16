/****************************************************************
 File: parser.h
 ----------------
 The interface for the recursive descent parser for Scheme.
 Reads in a list from standard input and outputs the
 parse tree for it.
 ***************************************************************/
#ifndef PARSER
#define PARSER
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/****************************************************************
 Function: S_Expression()
 ------------------------------------
 Recursively reads in a S expression and outputs that expression's
 parse tree. For example, if we had the expression below:
 */
List S_Expression();

/****************************************************************
 Function: printList()
 ------------------------------------
 Given a list, prints it out.
 */
void printList(List l);

#endif
