#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "list.h"

int main() {

    printf("A prototype evaluator for Scheme.\n");
    printf("Type Scheme expressions using quote,\n");
    printf("car, cdr, cons and symbol?.\n");
    printf("The function call (exit) quits.\n");

    while(1) {
        printf("\nscheme> ");
        List expression = S_Expression();
        printList(expression);
        printf("\n");
    }
}
