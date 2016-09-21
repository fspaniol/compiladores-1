#include <stdio.h>

int main(int argc, char** argv){
        initMe();
	FILE *file;
	if(argc==2 && (file = fopen(argv[1], "r"))){
		yyin = file;
		/*int identifier = -1;
		while(isRunning()){
			identifier = yylex();
			/*switch(identifier){							
				case KW_INT: 		
							printf("int ");
					 		break;
				case KW_FLOAT:		
							printf("float ");
							break;
				case KW_BOOL: 		
							printf("bool ");
							break;
				case KW_CHAR: 
							printf("char ");
							break;								
				case KW_IF: 
							printf("if ");
							break;
				case KW_THEN: 
							printf("then ");
							break;
				case KW_ELSE: 
							printf("else");
							break;
				case KW_FOR: 
							printf("for ");
							break;								
				case KW_READ: 
							printf("read ");
							break;
				case KW_RETURN: 
							printf("return ");
							break;
				case KW_PRINT: 
							printf("print ");
							break;
		        case LIT_TRUE: 
					printf("true ");
					break;                                                        
		        case LIT_FALSE: 
					printf("false ");
					break; 
		        case TK_IDENTIFIER: 
					printf("var %s", yytext);
					break;
		        case LIT_INTEGER:
		                                printf("integer literal %s", yytext);
		                                break;
		        case TOKEN_ERROR:       
		                                printf("token error %s",yytext);
		                                break;
		        case LIT_STRING:
		                                printf("string literal %s",yytext);
		                                break;
			}*/
		
	
		yyparse();
		printf("Numero de linhas: %d \n",getLineNumber());	
	}
	else
		printf("ERRO NO ABRIMENTO DO ARQUIVO!");
}
