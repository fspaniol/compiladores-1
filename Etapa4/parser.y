%{
        #include <stdio.h>
        #include <stdlib.h>
	#include "hash.h"
	#include "tree.h"
	#include "semantic.h"
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

%left OPERATOR_LE OPERATOR_GE OPERATOR_NE OPERATOR_L OPERATOR_G
%left OPERATOR_AND OPERATOR_OR
%left OPERATOR_MUL OPERATOR_DIV
%left OPERATOR_SUB OPERATOR_ADD
%right OPERATOR_EQ

%nonassoc IF_SIMPLE
%nonassoc KW_ELSE

%left '('
%left '['

%nonassoc EXPRESSION

%%
rootnode
    : program {$$ = $1; semanticAnalyser(createNode(TREE_DECLARATION, NULL, $1, NULL, NULL, NULL));}
    ;
program
    : declaration ';' program {$$ = createNode(TREE_DECLARATION, NULL, $1, $3, NULL, NULL);}
    |			      {$$ = NULL;}
    ;

datatype
    : KW_INT		{ $$ = createNode(TREE_KW_INTEGER, NULL, NULL, NULL, NULL, NULL);}
    | KW_FLOAT		{ $$ = createNode(TREE_KW_FLOAT, NULL, NULL, NULL, NULL, NULL);}
    | KW_BOOL		{ $$ = createNode(TREE_KW_BOOL, NULL, NULL, NULL, NULL, NULL);}
    | KW_CHAR  		{ $$ = createNode(TREE_KW_CHAR, NULL, NULL, NULL, NULL, NULL);}
    ;

params
    : params_non_empty { $$ = $1;}
    |		       { $$ = NULL;}
    ;
params_non_empty
    : datatype identifier ',' params_non_empty { $$ = createNode(TREE_DEC_FUC_PARAM_HEAD, NULL, $1, $2, $4, NULL);}
    | datatype identifier		{ $$ = createNode(TREE_DEC_FUC_PARAM_TAIL, NULL, $1, $2, NULL, NULL);}
    ;

init_literal_list
    : init_literal { $$ = createNode(TREE_DEC_VAR_VEC_LIT_LIST_TAIL, NULL, $1, NULL, NULL, NULL);}
    | init_literal init_literal_list { $$ = createNode(TREE_DEC_VAR_VEC_LIT_LIST_HEAD, NULL, $1, $2, NULL, NULL);}
    ;

init_literal
    : integer  { $$ = $1;}
    | LIT_FALSE    { $$ = createNode(TREE_FALSE, $1, NULL, NULL, NULL, NULL);}
    | LIT_TRUE     { $$ = createNode(TREE_TRUE, $1, NULL, NULL, NULL, NULL);}
    | LIT_CHAR     { $$ = createNode(TREE_CHAR, $1, NULL, NULL, NULL, NULL);}
    ;

integer
    : LIT_INTEGER { $$ = createNode(TREE_INTEGER, $1, NULL, NULL, NULL, NULL);}
    ;
declaration
    : datatype identifier ':' init_literal { $$ = createNode(TREE_DECLARATION_SCALAR, NULL, $1, $2, $4, NULL);}
    | datatype identifier '[' integer ']' ':' init_literal_list { $$ = createNode(TREE_DECLARATION_VEC_LIT, NULL, $1, $2, $4, $7);}
    | datatype identifier '[' integer ']'			{ $$ = createNode(TREE_DECLARATION_VEC_NOLIT, NULL, $1, $2, $4, NULL);}
    | datatype identifier '(' params ')' cmdblock		{ $$ = createNode(TREE_DECLARATION_FUC, NULL,  $1, $2, $4, $6);}
    ;

identifier
    : TK_IDENTIFIER { $$ = createNode(TREE_IDENTIFIER, $1, NULL, NULL, NULL, NULL);}
    ;
cmd
    : KW_READ identifier { $$ = createNode(TREE_CMD_READ, NULL, $2, NULL,NULL, NULL);}
    | KW_PRINT print_list { $$ = createNode(TREE_CMD_PRINT, NULL, $2, NULL,NULL, NULL);}
    | KW_RETURN exp	{ $$ = createNode(TREE_CMD_RETURN, NULL, $2, NULL,NULL, NULL);}
    | cmdblock		{ $$ = $1;}
    | identifier OPERATOR_ATTR exp { $$ = createNode(TREE_CMD_ATTR_VAR_SCALAR, NULL, $1, $3,NULL, NULL);}
    | identifier '[' exp ']' OPERATOR_ATTR exp { $$ = createNode(TREE_CMD_ATTR_VAR_VEC, NULL, $1, $3, $6, NULL);}
    | KW_IF '(' exp ')' KW_THEN cmd { $$ = createNode(TREE_CMD_IF, NULL, $3, $6, NULL, NULL);}
    | KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd { $$ = createNode(TREE_CMD_IF_ELSE, NULL, $3, $6, $8, NULL);}
    | KW_FOR '(' exp ')' cmd { $$ = createNode(TREE_CMD_FOR, NULL, $3, $5, NULL, NULL);}
    | KW_FOR '(' identifier OPERATOR_ATTR exp KW_TO exp ')' cmd { $$ = createNode(TREE_CMD_FOR_TO, NULL, $3, $5, $7, $9);}
    | { $$ = NULL;}
    ;

print_list
    : LIT_STRING print_list { $$ = createNode(TREE_CMD_PRINT_LIST_HEAD, NULL, createNode(TREE_STRING, $1,NULL,NULL,NULL,NULL), $2,NULL, NULL);}
    | exp print_list { $$ = createNode(TREE_CMD_PRINT_LIST_HEAD, NULL, $1, $2,NULL, NULL);}
    | LIT_STRING { $$ = createNode(TREE_CMD_PRINT_LIST_TAIL,NULL, createNode(TREE_STRING, $1,NULL,NULL,NULL,NULL), NULL,NULL, NULL);}
    | exp { $$ = createNode(TREE_CMD_PRINT_LIST_TAIL, NULL, $1, NULL,NULL, NULL);}
    ;

cmdlist
    : cmd ';' cmdlist { $$ = createNode(TREE_CMD_LIST_HEAD, NULL, $1, $3,NULL, NULL);}
    | cmd ';' { $$ = createNode(TREE_CMD_LIST_TAIL, NULL, $1, NULL,NULL, NULL);}
    ;

cmdblock
    : '{' cmdlist '}' { $$ = createNode(TREE_CMD_BLOCK, NULL, $2, NULL,NULL, NULL);}
    ;
operator
    : OPERATOR_LE	{ $$ = createNode(TREE_LE, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_GE	{ $$ = createNode(TREE_GE, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_EQ	{ $$ = createNode(TREE_EQ, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_NE  	{ $$ = createNode(TREE_NE, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_L 	{ $$ = createNode(TREE_L, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_G	{ $$ = createNode(TREE_G, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_AND  { $$ = createNode(TREE_AND, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_OR  	{ $$ = createNode(TREE_OR, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_MUL	{ $$ = createNode(TREE_MUL, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_DIV	{ $$ = createNode(TREE_DIV, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_SUB	{ $$ = createNode(TREE_SUB, NULL, NULL, NULL,NULL, NULL);}
    | OPERATOR_ADD	{ $$ = createNode(TREE_ADD, NULL, NULL, NULL,NULL, NULL);}
    ;

exp
    : identifier {$$ = $1;}
    | identifier '[' exp ']' { $$ = createNode(TREE_EXP_VEC_INDEX, NULL, $1, $3,NULL, NULL);}
    | integer {$$ = $1;}
    | LIT_CHAR    { $$ = createNode(TREE_CHAR, $1, NULL, NULL,NULL, NULL);}
    | exp operator exp { $$ = createNode(TREE_EXP_OP_BINARY, NULL, $1, $2, $3, NULL);} %prec EXPRESSION
    | '('exp')' { $$ = createNode(TREE_EXP_BRACKET_ENCLOSURE, NULL, $2,NULL, NULL, NULL);}
    | identifier '(' argument_list ')'  { $$ = createNode(TREE_EXP_FUNC_CALL, NULL, $1,$3, NULL, NULL);}
    ;
argument_list
    : argument_list_non_empty { $$ = $1;}
    | { $$ = NULL;}
    ;

argument_list_non_empty
    : exp ',' argument_list { $$ = createNode(TREE_EXP_FUNC_CALL_ARG_LIST_HEAD, NULL, $1,$3, NULL, NULL);}
    | exp { $$ = createNode(TREE_EXP_FUNC_CALL_ARG_LIST_TAIL, NULL, $1,NULL, NULL, NULL);}
    ;
%%
int yyerror (const char *s) {
    fflush(stderr);
    fprintf(stderr,"ERROR: %s ---> Line: %d\n", s, getLineNumber());
    exit(3);
}
