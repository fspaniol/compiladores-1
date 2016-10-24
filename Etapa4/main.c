#include <stdio.h>
#include "hash.h"
#include "tree.h"
#include "lex.yy.h"



int main(int argc, char** argv){
        initMe();
        FILE *file;
        if(argc < 2){
        	printf("Arquivo não informado\n");
        	exit(1);
        }
        if((argc==2 && (file = fopen(argv[1], "r"))) ) {
		yyin = file;
		yyparse();
	}
	else {
		printf("Erro na abertura do arquivo!\n");
		exit(2);
	}
	printf("Compilação feita com sucesso!\n");
	exit(0);
}
