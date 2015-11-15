/****************************************************************
 File: cell.c
 -------------
 Implements the interface defined in cell.h.
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

/**
 *  Cell Data Structure
 */
struct cell {
    char * symbol; 
    struct cell * first;
    struct cell * rest;
};

/**
 *  Creates a new cell and returns it.
 */
Cell createCell() {
    Cell cell = (Cell) malloc(sizeof(Cell));
    if (cell == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    cell->symbol = NULL;
    cell->first = NULL;
    cell->rest = NULL;
    return cell;
}
