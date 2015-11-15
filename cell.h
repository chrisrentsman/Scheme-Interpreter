/****************************************************************
 File: cell.h
 -------------
 Contains the interface the cell structure. The cell structure
 is one of the primary building blocks within Scheme. Cells
 can either point at two more cells, or contain a string.
 ****************************************************************/

#ifndef CELL
#define CELL
#include <stdio.h>
#include <stdlib.h>

/**
 *  Data Type: Cell
 *  ---------------
 *  Declares a cell in the following way:
 *
 *      Cell c;
 */
struct cell;
typedef struct cell * Cell;

/**
 *  Function: createCell()
 *  ----------------------
 *  Creates a new Cell and returns it, as in:
 *
 *      Cell c = createCell();
 */
Cell createCell();

#endif
