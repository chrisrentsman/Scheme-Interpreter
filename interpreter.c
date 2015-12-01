#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "list.h"
#include "list_utils.h"

int main() {
    printf("\nA prototype evaluator for Scheme.\n");
    printf("Type Scheme expressions using quote,\n");
    printf("car, cdr, cons and symbol?.\n");
    printf("The function call (exit) quits.\n");

    while(1) {
        printf("\nscheme> ");
        List expression = S_Expression();
        printList(eval(expression));
	printf("\n");
    }
}
