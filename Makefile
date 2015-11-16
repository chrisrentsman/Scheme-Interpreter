
#To run, put this file together with lexer.h, and lexer.c
#in the same directory. Run "make". Then the executable
#is "schemer," which just takes a line of input and
#breaks it up into tokens.

scheme: parsetester.o parser.o lexer.o list.o
	gcc -o scheme parsetester.o parser.o lexer.o list.o

parsetester.o: parsetester.c
	gcc -c parsetester.c

parser.o: parser.c
	gcc -c parser.c

lexer.o: lexer.c
	gcc -c lexer.c

list.o: list.c
	gcc -c list.c

clean:
	rm -f *~ *.o *.a scheme

#^^^^^^This space must be a TAB!!.

