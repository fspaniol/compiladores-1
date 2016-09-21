%{
        #include <stdio.h>
        #include <stdlib.h>
	#include "hash.c"

        int getLineNumber();
        int yyerror();
        int yylex();
%}
%token KW_INT        
%token KW_FLOAT      
%token KW_BOOL       
%token KW_CHAR       
%token KW_IF         
%token KW_THEN       
%token KW_ELSE       
%token KW_FOR     
%token KW_TO
%token KW_READ       
%token KW_RETURN     
%token KW_PRINT      

%token OPERATOR_LE   
%token OPERATOR_GE   
%token OPERATOR_EQ   
%token OPERATOR_NE   
%token OPERATOR_AND  
%token OPERATOR_OR  
%token OPERATOR_L
%token OPERATOR_G

%token OPERATOR_ATTR
%token OPERATOR_MUL
%token OPERATOR_DIV
%token OPERATOR_SUB
%token OPERATOR_ADD


%token TK_IDENTIFIER 
%token LIT_INTEGER   
%token LIT_FALSE     
%token LIT_TRUE      
%token LIT_CHAR      
%token LIT_STRING  
%token TOKEN_ERROR
%union{
	HASHCELL* symbol;
}
%%
program
    : declaration ';' program
    |
    ;

datatype 
    : KW_INT       
    | KW_FLOAT      
    | KW_BOOL       
    | KW_CHAR  
    ;

params
    : params_non_empty
    |
    ;
params_non_empty
    : datatype TK_IDENTIFIER ',' params
    | datatype TK_IDENTIFIER
    ;
    
init_literal_list
    : init_literal
    | init_literal init_literal_list
    ;
    
init_literal
    : LIT_INTEGER   
    | LIT_FALSE     
    | LIT_TRUE      
    | LIT_CHAR      
    ;
                
        
declaration
    : datatype TK_IDENTIFIER ':' init_literal
    | datatype TK_IDENTIFIER '[' LIT_INTEGER ']' ':' init_literal_list
    | datatype TK_IDENTIFIER '[' LIT_INTEGER ']'
    | datatype TK_IDENTIFIER '(' params ')' cmdblock
    ;
        
        
cmd
    : KW_READ TK_IDENTIFIER
    | KW_PRINT print_list
    | KW_RETURN exp
    | cmdblock
    | TK_IDENTIFIER OPERATOR_ATTR exp
    | TK_IDENTIFIER '[' LIT_INTEGER ']' OPERATOR_ATTR exp
    | KW_IF '(' exp ')' KW_THEN cmd
    | KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd
    | KW_FOR '(' exp ')' cmd
    | KW_FOR '(' TK_IDENTIFIER OPERATOR_ATTR exp KW_TO exp ')' cmd
    |
    ; 
 
print_list
    : LIT_STRING print_list
    | exp print_list
    | LIT_STRING
    | exp
    ;

cmdlist
    : cmd ';' cmdlist
    | cmd ';'
    ;
  
cmdblock
    : '{' cmdlist '}'
    ;
operator
    : OPERATOR_LE   
    | OPERATOR_GE   
    | OPERATOR_EQ   
    | OPERATOR_NE  
    | OPERATOR_L
    | OPERATOR_G
    | OPERATOR_AND  
    | OPERATOR_OR  
    | OPERATOR_MUL
    | OPERATOR_DIV
    | OPERATOR_SUB
    | OPERATOR_ADD
    ;
    
exp
    : TK_IDENTIFIER
    | TK_IDENTIFIER '[' LIT_INTEGER ']'
    | LIT_INTEGER
    | LIT_CHAR
    | exp operator exp
    | '('exp')'
    | TK_IDENTIFIER '(' argument_list ')'
    ;
argument_list
    : argument_list_non_empty
    | 
    ;
    
argument_list_non_empty
    : exp ',' argument_list
    | exp
    ;
%%

int yyerror (const char *s) {
    fflush(stderr);
    fprintf(stderr,"ERROR: %s ---> Line: %d\n", s, getLineNumber()+1);
    exit(3);
}
