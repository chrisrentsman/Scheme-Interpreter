/****************************************************************
 File: list.h
 -------------
 Contains the interface the list structure. The list structure
 is one of the primary building blocks within Scheme. Lists
 can either point at two more lists, or contain a string.
 ****************************************************************/

#ifndef CELL
#define CELL
#include <stdio.h>
#include <stdlib.h>

/**
 *  Data Type: List
 *  ---------------
 *  Declares a list in the following way:
 *
 *      List c;
 */
struct list;
typedef struct list * List;

/**
 *  Function: createList()
 *  ----------------------
 *  Creates a new List and returns it, as in:
 *
 *      List c = createList();
 */
List createList();

void setFirst(List source, List sink);
List getFirst(List source);
void setRest(List source, List sink);
List getRest(List source);
void setSymbol(List source, char * symbol);
char * getSymbol(List source);

#endif
