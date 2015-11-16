/**********************************************************************
 File: list.h
 -------------
 Contains the interface the list structure. The list structure
 is one of the primary building blocks within Scheme. Lists
 can either point at two more lists, or contain a string.
 *********************************************************************/

#ifndef CELL
#define CELL
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************
 *  Data Type: List
 *  ---------------
 *  Declares a list in the following way:
 *
 *      List c;
 */
struct conscell;
typedef struct conscell * List;

/**********************************************************************
 *  Function: createList()
 *  ----------------------
 *  Creates a new List and returns it, as in:
 *
 *      List c = createList();
 */
List createList();

/**********************************************************************
 *  Functions: setFirst(List source, List sink), getFirst(List source)
 *  ------------------------------------------------------------------
 *  Sets and retrieves the first element of a list.
 */
void setFirst(List source, List sink);
List getFirst(List source);

/**********************************************************************
 *  Functions: setRest(List source, List sink), getRest(List source)
 *  ------------------------------------------------------------------
 *  Sets and retrieves the rest of the list.
 */
void setRest(List source, List sink);
List getRest(List source);

/**********************************************************************
 *  Functions: setSymbol(List source, char * symbol), getSymbol(List source)
 *  ------------------------------------------------------------------
 *  Sets and retrieves the symbol of a list.
 */
void setSymbol(List source, char * symbol);
char * getSymbol(List source);

#endif
