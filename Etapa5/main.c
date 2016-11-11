#include <stdio.h>
#include "hash.h"
#include "tree.h"
#include "lex.yy.h"



int main(int argc, char** argv){
        initMe();
        FILE *file;
        if(argc < 2){
                printf("File not provided\n");
        	exit(1);
        }
        if((argc==2 && (file = fopen(argv[1], "r"))) ) {
		yyin = file;
		yyparse();
	}
	else {
                printf("Error opening the file\n");
		exit(2);
	}
        printf("Success!\n");
	exit(0);
}
