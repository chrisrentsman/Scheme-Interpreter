/****************************************************************
 File: list.c
 -------------
 Implements the interface defined in list.h.
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/****************************************************************
 Data type: List
 ---------------
 Defines the list struct, which completes the List data type.
 ***************************************************************/
struct conscell {
    char * symbol; 
    struct conscell * first;
    struct conscell * rest;
};

/****************************************************************
 Function: createList()
 -----------------------
 Creates and returns a new list.
 ***************************************************************/
List createList() {
    List list = (List) malloc(sizeof(List));
    if (list == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    list->symbol = NULL;
    list->first = NULL;
    list->rest = NULL;
    return list;
}

List copyList(List from) {
    List list = (List) malloc(sizeof(from));
    if (list == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }
    memcpy(list, from, sizeof(from));
    return list;
}

/****************************************************************
 Function: setFirst(List source, List sink)
 -------------------------------------------
 Sets the first instance variable of a source list.
 ***************************************************************/
void setFirst(List source, List sink) {
    source->first = sink;
}

/****************************************************************
 Function: getFirst(List source)
 -------------------------------------------
 Gets the first instance variable of a list.
 ***************************************************************/
List getFirst(List source) {
    return source->first;
}

/****************************************************************
 Function: setRest(List source, List sink)
 -------------------------------------------
 Sets the rest instance variable of a source list.
 ***************************************************************/
void setRest(List source, List sink) {
    source->rest = sink;
}

/****************************************************************
 Function: getLast(List source)
 -------------------------------------------
 Gets the rest instance variable of a list.
 ***************************************************************/
List getRest(List source) {
    return source->rest;
}

/****************************************************************
 Function: setSymbol(List source, char * symbol)
 ------------------------------------------------
 Sets the symbol instance variable of a list.
 ***************************************************************/
void setSymbol(List source, char * symbol) {
    source->symbol = (char *) malloc(sizeof(symbol));
    strcpy(source->symbol, symbol);
}

/****************************************************************
 Function: getSymbol(List source)
 ------------------------------------------------
 Gets the symbol instance variable of a list.
 ***************************************************************/
char * getSymbol(List source) {
    return source->symbol;
}
