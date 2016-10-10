#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa: lex.yy.c y.tab.o main.o hash.o tree.o semantic.o
	gcc -o etapa3 lex.yy.c y.tab.c main.o hash.o tree.o

lex.yy.c: scanner.l 
	lex --header-file=lex.yy.h  scanner.l

y.tab.o: y.tab.c
	gcc -c y.tab.c $(CFLAGS)
y.tab.c: parser.y
	yacc -v -d parser.y

main.o: main.c lex.yy.c
	gcc -c main.c
tree.o: tree.c
	gcc -c tree.c
hash.o: hash.c
	gcc -c hash.c
semantic.o: semantic.c
	gcc -c semantic.c
tgz: clean
	tar cvzf  ../etapa4.tgz . --exclude-vcs

clean:
	@rm *.yy.* etapa3 y.*.* y.* *.o || true
