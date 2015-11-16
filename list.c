/****************************************************************
 File: list.c
 -------------
 Implements the interface defined in list.h.
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct list {
    char * symbol; 
    struct list * first;
    struct list * rest;
};
typedef struct list *List;

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

void setFirst(List source, List sink) {
    source->first = sink;
}

List getFirst(List source) {
    return source->first;
}

void setRest(List source, List sink) {
    source->rest = sink;
}

List getRest(List source) {
    return source->rest;
}

void setSymbol(List source, char * symbol) {
    source->symbol = (char *) malloc(sizeof(symbol));
    strcpy(source->symbol, symbol);
}

char * getSymbol(List source) {
    return source->symbol;
}
