#include <stdio.h>
#include "hash.h"
#include "tree.h"
#include "lex.yy.h"

int main(int argc, char** argv){
        initMe();
	FILE *file, *out;
	if (argc < 3) {
		printf("Um dos arquivos não foi informado.\n");
		exit(2);
	}
	if(((file = fopen(argv[1], "r"))) && (argc == 3 && (out = fopen(argv[2], "w")))) {
		yyin = file;
		definirOutput(out);
		yyparse();
		printf("Numero de linhas: %d \n",getLineNumber());	
	}
	else {
		printf("Erro na abertura do arquivo!\n");
		exit(1);
	}
	exit(0);
}
