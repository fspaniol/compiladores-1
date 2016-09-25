etapa3: y.tab.o lex.yy.o main.o tree.o hash.o
	gcc -o etapa3 y.tab.o lex.yy.o main.o tree.o hash.o

main.o: main.c lex.yy.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

tree.o: tree.c
	gcc -c tree.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c: y.tab.h
	yacc parser.y

y.tab.h: parser.y
	yacc -d parser.y -v

tgz: clean
	tar cvzf etapa3.tgz .

clean:
	rm -rf etapa3 etapa3.tgz *.o lex.yy.* y.tab.* y.output *~