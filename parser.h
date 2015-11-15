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

/****************************************************************
 Function: S_Expression()
 ------------------------------------
 Recursively reads in a S expression and outputs that expression's
 parse tree. For example, if we had the expression below:

    (a (b c) d)

 This function would output:
    
    S_Expression
    (
      S_Expression
        a
      S_Expression
      (
        S_Expression
          b
        S_Expression
          c
      )
      S_Expression
        d
    )

 This represents the overall structure of the expression.
 */
void S_Expression();

#endif
