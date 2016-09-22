%{
        #include <stdio.h>
        #include <stdlib.h>
	#include "hash.h"
	#include "tree.h"

        int getLineNumber();
        int yyerror();
        int yylex();
%}

%type<node> program
%type<node> declaration
%type<node> datatype
%type<node> params
%type<node> params_non_empty
%type<node> init_literal_list
%type<node> init_literal
%type<node> declaration
%type<node> cmd
%type<node> print_list
%type<node> cmdlist
%type<node> cmdblock
%type<node> operator
%type<node> exp
%type<node> argument_list
%type<node> argument_list_non_empty
%type<node> identifier
%type<node> integer
%type<node> rootnode
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


%token<symbol> TK_IDENTIFIER 
%token<symbol> LIT_INTEGER   
%token<symbol> LIT_FALSE     
%token<symbol> LIT_TRUE      
%token<symbol> LIT_CHAR      
%token<symbol> LIT_STRING  
%token TOKEN_ERROR
%union{
	HASHCELL* symbol;
	TREENODE* node;
}


%%
rootnode
    : program {$$ = $1; printTree($1);}
    ;
program
    : declaration ';' program {$$ = addChild(TREE_DECLARATION, NULL, $1, $3, NULL, NULL);}
    |			      {$$ = NULL;}
    ;

datatype 
    : KW_INT		{ $$ = addChild(TREE_KW_INTEGER, NULL, NULL, NULL, NULL, NULL);}
    | KW_FLOAT		{ $$ = addChild(TREE_KW_FLOAT, NULL, NULL, NULL, NULL, NULL);}
    | KW_BOOL		{ $$ = addChild(TREE_KW_BOOL, NULL, NULL, NULL, NULL, NULL);}
    | KW_CHAR  		{ $$ = addChild(TREE_KW_CHAR, NULL, NULL, NULL, NULL, NULL);}
    ;

params
    : params_non_empty { $$ = $1;}
    |		       { $$ = NULL;}
    ;
params_non_empty
    : datatype identifier ',' params_non_empty { $$ = addChild(TREE_DEC_FUC_PARAM_HEAD, NULL, $1, $2, $4, NULL);}
    | datatype identifier		{ $$ = addChild(TREE_DEC_FUC_PARAM_TAIL, NULL, $1, $2, NULL, NULL);}
    ;
    
init_literal_list
    : init_literal { $$ = addChild(TREE_DEC_VAR_VEC_LIT_LIST_TAIL, NULL, $1, NULL, NULL, NULL);} 
    | init_literal init_literal_list { $$ = addChild(TREE_DEC_VAR_VEC_LIT_LIST_HEAD, NULL, $1, $2, NULL, NULL);}
    ;
    
init_literal
    : integer  { $$ = $1;} 
    | LIT_FALSE    { $$ = addChild(TREE_FALSE, $1, NULL, NULL, NULL, NULL);} 
    | LIT_TRUE     { $$ = addChild(TREE_TRUE, $1, NULL, NULL, NULL, NULL);} 
    | LIT_CHAR     { $$ = addChild(TREE_CHAR, $1, NULL, NULL, NULL, NULL);} 
    ;

integer
    : LIT_INTEGER { $$ = addChild(TREE_INTEGER, $1, NULL, NULL, NULL, NULL);} 
    ;
declaration
    : datatype identifier ':' init_literal { $$ = addChild(TREE_DECLARATION_SCALAR, NULL, $1, $2, $4, NULL);}
    | datatype identifier '[' integer ']' ':' init_literal_list { $$ = addChild(TREE_DECLARATION_VEC_LIT, NULL, $1, $2, $4, $7);}
    | datatype identifier '[' integer ']'			{ $$ = addChild(TREE_DECLARATION_VEC_NOLIT, NULL, $1, $2, $4, NULL);}
    | datatype identifier '(' params ')' cmdblock			{ $$ = addChild(TREE_DECLARATION_FUC, NULL,  $1, $2, $4, $6);}
    ;
        
identifier
    : TK_IDENTIFIER { $$ = addChild(TREE_IDENTIFIER, $1, NULL, NULL, NULL, NULL);} 
    ;
cmd
    : KW_READ identifier { $$ = addChild(TREE_CMD_READ, NULL, $2, NULL,NULL, NULL);}
    | KW_PRINT print_list { $$ = addChild(TREE_CMD_PRINT, NULL, $2, NULL,NULL, NULL);}
    | KW_RETURN exp	{ $$ = addChild(TREE_CMD_RETURN, NULL, $2, NULL,NULL, NULL);}
    | cmdblock		{ $$ = $1;}
    | identifier OPERATOR_ATTR exp { $$ = addChild(TREE_CMD_ATTR_VAR_SCALAR, NULL, $1, $3,NULL, NULL);}
    | identifier '[' integer ']' OPERATOR_ATTR exp { $$ = addChild(TREE_CMD_ATTR_VAR_VEC, NULL, $1, $3, $6, NULL);}
    | KW_IF '(' exp ')' KW_THEN cmd { $$ = addChild(TREE_CMD_IF, NULL, $3, $6, NULL, NULL);}
    | KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd { $$ = addChild(TREE_CMD_IF_ELSE, NULL, $3, $6, $8, NULL);}
    | KW_FOR '(' exp ')' cmd { $$ = addChild(TREE_CMD_FOR, NULL, $3, NULL, NULL, NULL);}
    | KW_FOR '(' identifier OPERATOR_ATTR exp KW_TO exp ')' cmd { $$ = addChild(TREE_CMD_FOR_TO, NULL, $3, $5, $7, $9);}
    | { $$ = NULL;}
    ; 
 
print_list
    : LIT_STRING print_list { $$ = addChild(TREE_CMD_PRINT_LIST_HEAD, NULL, addChild(TREE_STRING, $1,NULL,NULL,NULL,NULL), $2,NULL, NULL);}
    | exp print_list { $$ = addChild(TREE_CMD_PRINT_LIST_HEAD, NULL, $1, $2,NULL, NULL);}
    | LIT_STRING { $$ = addChild(TREE_CMD_PRINT_LIST_TAIL,NULL, addChild(TREE_STRING, $1,NULL,NULL,NULL,NULL), NULL,NULL, NULL);}
    | exp { $$ = addChild(TREE_CMD_PRINT_LIST_TAIL, NULL, $1, NULL,NULL, NULL);}
    ;

cmdlist
    : cmd ';' cmdlist { $$ = addChild(TREE_CMD_LIST_HEAD, NULL, $1, $3,NULL, NULL);}
    | cmd ';' { $$ = addChild(TREE_CMD_LIST_TAIL, NULL, $1, NULL,NULL, NULL);}
    ;
  
cmdblock
    : '{' cmdlist '}' { $$ = addChild(TREE_CMD_BLOCK, NULL, $2, NULL,NULL, NULL);}
    ;
operator
    : OPERATOR_LE	{ $$ = addChild(TREE_LE, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_GE	{ $$ = addChild(TREE_GE, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_EQ	{ $$ = addChild(TREE_EQ, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_NE  	{ $$ = addChild(TREE_NE, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_L 	{ $$ = addChild(TREE_L, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_G	{ $$ = addChild(TREE_G, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_AND  	{ $$ = addChild(TREE_AND, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_OR  	{ $$ = addChild(TREE_OR, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_MUL	{ $$ = addChild(TREE_MUL, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_DIV	{ $$ = addChild(TREE_DIV, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_SUB	{ $$ = addChild(TREE_SUB, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_ADD	{ $$ = addChild(TREE_ADD, NULL, NULL, NULL,NULL, NULL);}
    ;
    
exp
    : identifier {$$ = $1;}
    | identifier '[' integer ']' { $$ = addChild(TREE_EXP_VEC_INDEX, NULL, $1, $3,NULL, NULL);}
    | integer {$$ = $1;}
    | LIT_CHAR    { $$ = addChild(TREE_CHAR, $1, NULL, NULL,NULL, NULL);}
    | exp operator exp { $$ = addChild(TREE_EXP_OP_BINARY, NULL, $1, $2, $3, NULL);}
    | '('exp')' { $$ = addChild(TREE_EXP_BRACKET_ENCLOSURE, NULL, $2,NULL, NULL, NULL);}
    | identifier '(' argument_list ')'  { $$ = addChild(TREE_EXP_FUNC_CALL, NULL, $1,$3, NULL, NULL);}
    ;
argument_list
    : argument_list_non_empty { $$ = $1;}
    | { $$ = addChild(TREE_EXP_FUNC_CALL_ARG_LIST_TAIL, NULL, NULL,NULL, NULL, NULL);}
    ;
    
argument_list_non_empty
    : exp ',' argument_list { $$ = addChild(TREE_EXP_FUNC_CALL_ARG_LIST_HEAD, NULL, $1,$3, NULL, NULL);}
    | exp { $$ = addChild(TREE_EXP_FUNC_CALL_ARG_LIST_TAIL, NULL, $1,NULL, NULL, NULL);}
    ;
%%

int yyerror (const char *s) {
    fflush(stderr);
    fprintf(stderr,"ERROR: %s ---> Line: %d\n", s, getLineNumber()+1);
    exit(3);
}
