%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "tree.h"
#include "y.tab.h"

int running = 1;
int lines = 0;

int isRunning(void);
int getLineNumber(void);
void initMe(void);
int yyerror();
%}


%x COMENTARIO
%x STRING

%option nounput
%option noinput

%%
int				{return KW_INT;}
float 			        {return KW_FLOAT;}
bool 				{return KW_BOOL;}
char     			{return KW_CHAR;}
if				{return KW_IF;}
then 				{return KW_THEN;}
else				{return KW_ELSE;}
for 				{return KW_FOR;}
to				{return KW_TO;}
read 				{return KW_READ;}
return 				{return KW_RETURN;}
print 				{return KW_PRINT;}
TRUE 				{return LIT_TRUE;}
FALSE 				{return LIT_FALSE;}
"="				{return OPERATOR_ATTR;}
"*"				{return OPERATOR_MUL;}
"/"				{return OPERATOR_DIV;}
"-"				{return OPERATOR_SUB;}
"+"				{return OPERATOR_ADD;}
"<"				{return OPERATOR_L;}
">"				{return OPERATOR_G;}
"<="				{return OPERATOR_LE;}
">="				{return OPERATOR_GE;}
"=="				{return OPERATOR_EQ;}	
"!="				{return OPERATOR_NE;}
"&&"				{return OPERATOR_AND;}
"||"				{return OPERATOR_OR;}					



[A-Za-z_][A-Za-z_0-9]*		{yylval.symbol = addHash(yytext, SYMBOL_IDENTIFIER);return TK_IDENTIFIER;}
[0-9]*				{yylval.symbol = addHash(yytext, SYMBOL_LIT_INT);return LIT_INTEGER;}
\'.\'				{yylval.symbol = addHash(yytext, SYMBOL_LIT_CHAR);return LIT_CHAR;} 
[,;:\(\)\[\]\{\}+\-*/<>=!&$]   	{return yytext[0];}	
[ \t\f\v]				
\n 				{lines++;}
"//".*				
"/*"				{BEGIN(COMENTARIO);}

\"([^\"\n\\]|\\.)*\"      { yylval.symbol = addHash(yytext, LIT_STRING); return LIT_STRING;}

.				{return TOKEN_ERROR;}

<COMENTARIO>"*/"	{BEGIN(INITIAL);}
<COMENTARIO>\n 		{lines++;} 
<COMENTARIO>.*	



%%

int yywrap(){
	running = 0;
	return 1;
}

int isRunning(void){
	return running;
}

int getLineNumber(void){
	return lines;
}
void initMe(void) {
}

