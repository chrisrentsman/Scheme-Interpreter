#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

int main() {

    printf("A parser for a subset of Scheme.\n");
    printf("Type in any Scheme expression and its\n");
    printf("\"parse tree\" will be printed out.\n");
    printf("Type Ctrl-c to quit.\n\n");

    while(1) {
        printf("scheme> ");
        S_Expression();
    }
}
