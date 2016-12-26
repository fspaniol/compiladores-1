/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
        #include <stdio.h>
        #include <stdlib.h>
    #include "hash.h"
    #include "tree.h"
    #include "semantic.h"
        int getLineNumber();
        int yyerror();
        int yylex();
#line 66 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
    HASHCELL* symbol;
    TREENODE* node;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 42 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_INT 257
#define KW_FLOAT 258
#define KW_BOOL 259
#define KW_CHAR 260
#define KW_IF 261
#define KW_THEN 262
#define KW_ELSE 263
#define KW_FOR 264
#define KW_TO 265
#define KW_READ 266
#define KW_RETURN 267
#define KW_PRINT 268
#define OPERATOR_LE 269
#define OPERATOR_GE 270
#define OPERATOR_EQ 271
#define OPERATOR_NE 272
#define OPERATOR_AND 273
#define OPERATOR_OR 274
#define OPERATOR_L 275
#define OPERATOR_G 276
#define OPERATOR_ATTR 277
#define OPERATOR_MUL 278
#define OPERATOR_DIV 279
#define OPERATOR_SUB 280
#define OPERATOR_ADD 281
#define TK_IDENTIFIER 282
#define LIT_INTEGER 283
#define LIT_FALSE 284
#define LIT_TRUE 285
#define LIT_CHAR 286
#define LIT_STRING 287
#define TOKEN_ERROR 288
#define IF_SIMPLE 289
#define EXPRESSION 290
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    3,    3,    3,    3,    4,    4,    5,
    5,    6,    6,    7,    7,    7,    7,   17,    2,    2,
    2,    2,   16,    8,    8,    8,    8,    8,    8,    8,
    8,    8,    8,    8,    9,    9,    9,    9,   10,   10,
   11,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   14,   14,   15,   15,
};
static const YYINT yylen[] = {                            2,
    1,    3,    0,    1,    1,    1,    1,    1,    0,    4,
    2,    1,    2,    1,    1,    1,    1,    1,    4,    7,
    5,    6,    1,    2,    2,    2,    1,    3,    6,    6,
    8,    5,    9,    0,    2,    2,    1,    1,    3,    2,
    3,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    4,    1,    1,    3,    3,    4,
    1,    1,    1,    0,    3,    1,
};
static const YYINT yydefred[] = {                         0,
    4,    5,    6,    7,    0,    1,    0,    0,    0,   23,
    0,    2,    0,    0,    0,    0,    0,    8,   18,    0,
   15,   16,   17,   19,   14,    0,    0,    0,    0,    0,
   22,    0,   10,    0,    0,    0,    0,    0,    0,    0,
   27,    0,   20,    0,    0,    0,   24,   61,   62,   57,
    0,    0,    0,   56,    0,   25,    0,    0,   41,    0,
    0,   13,    0,    0,    0,    0,   42,   43,   44,   45,
   48,   49,   46,   47,   50,   51,   52,   53,    0,    0,
    0,   35,   36,   39,    0,    0,    0,    0,    0,   59,
   58,    0,    0,   63,    0,    0,    0,   32,    0,    0,
   60,   55,    0,    0,    0,   65,    0,    0,    0,   31,
    0,   33,
};
static const YYINT yydgoto[] = {                          5,
    6,    7,    8,   17,   18,   43,   44,   39,   56,   40,
   41,   79,   57,   93,   94,   53,   54,
};
static const YYINT yysindex[] = {                      -213,
    0,    0,    0,    0,    0,    0,  -46, -266, -213,    0,
  -28,    0, -213, -256, -211, -266,  -13,    0,    0,  -62,
    0,    0,    0,    0,    0,  -11,  -82,  -10, -213, -114,
    0, -211,    0,    9,   13, -266,   -3,  -34,   -8,  -71,
    0,  -80,    0, -211,   -3,   -3,    0,    0,    0,    0,
   -3, -109,  -23,    0,  -34,    0,  -40, -114,    0,   -3,
   -3,    0,   15,   28,  -20,   41,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   -3,   -3,
   -3,    0,    0,    0, -109,  -85, -202, -114,   -3,    0,
    0,   80,   20,    0,  -53, -215, -114,    0, -144,   -3,
    0,    0,   -3, -198,   -3,    0, -109, -114,   54,    0,
 -114,    0,
};
static const YYINT yyrindex[] = {                        66,
    0,    0,    0,    0,    0,    0,    0,    0,   66,    0,
    0,    0,   36,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   39,    0,   26,    0,   27,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   29,    0,    0,    0,    0,    0,    0,
    0,  -58,   -9,    0,  -57,    0,  -56,  -49,    0,    0,
    0,    0,    0,    0,   67,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   46,
    0,    0,    0,    0,  -55,    0,    0,  -54,    0,    0,
    0,   48,    0,    0,    0,    0,  -54,    0,    0,   46,
    0,    0,    0,   32,    0,    0,  -52,  -54,    0,    0,
  -54,    0,
};
static const YYINT yygindex[] = {                         0,
   83,    0,    5,    0,   68,   52,   84,  -18,  -36,   40,
   73,    0,  -22,    1,    0,    6,   11,
};
#define YYTABLESIZE 361
static const YYINT yytable[] = {                         51,
   26,   37,   38,   28,   34,   51,   29,   96,   30,   34,
   61,   13,    9,   11,   52,   10,   80,   16,   82,   80,
   83,   26,   63,   64,   20,   25,   19,   27,   66,   15,
   28,   54,   29,   16,   54,   42,   51,   85,   86,  102,
   30,   47,   25,    1,    2,    3,    4,   32,   45,   54,
   58,   65,   46,   59,   25,   87,   91,   92,   95,   97,
  101,  103,   14,   42,  108,    3,   99,   81,   88,   98,
   81,   19,   21,   22,   23,   40,    9,   92,  104,   11,
  107,   90,  109,   54,   21,   34,   64,   12,   66,  110,
   30,   12,  112,   42,  111,   62,   33,   84,   24,   31,
  106,    0,   42,    0,    0,    0,    0,   54,    0,    0,
    0,    0,    0,   42,    0,    0,   42,    0,    0,    0,
  105,    0,    0,  100,   67,   68,   69,   70,   71,   72,
   73,   74,    0,   75,   76,   77,   78,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   34,    0,    0,   35,
    0,   36,   37,   38,    0,    0,    0,    0,    0,   67,
   68,   69,   70,   71,   72,   73,   74,   10,   75,   76,
   77,   78,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   67,   68,   69,   70,   71,   72,   73,
   74,    0,   75,   76,   77,   78,   60,    0,    0,    0,
    0,    0,    0,    0,   26,   37,   38,   28,   34,    0,
   29,    0,    0,    0,    0,   67,   68,   69,   70,   71,
   72,   73,   74,    0,   75,   76,   77,   78,   67,   68,
   69,   70,   71,   72,   73,   74,    0,   75,   76,   77,
   78,   10,   19,   48,   49,   50,   55,   10,   19,   48,
   49,   50,   55,   54,    0,   54,   89,    0,    0,   54,
   54,   54,   54,   54,   54,   54,   54,    0,   54,   54,
   54,   54,   54,   54,   54,   54,   54,   54,   10,   19,
   48,   49,   50,   67,   68,   69,   70,   71,   72,   73,
   74,    0,   75,   76,   77,   78,   67,   68,   69,   70,
   71,   72,   73,   74,    0,   75,   76,   77,   78,   67,
   68,   69,   70,   71,   72,   73,   74,    0,   75,   76,
   77,   78,   67,   68,   69,   70,   71,   72,   73,   74,
    0,   75,   76,   77,   78,   54,   54,   54,   54,   54,
   54,   54,   54,    0,   54,   54,   54,   54,   67,   68,
   69,   70,   71,   72,   73,   74,    0,   75,   76,   77,
   78,
};
static const YYINT yycheck[] = {                         40,
   59,   59,   59,   59,   59,   40,   59,   93,  123,   59,
   91,   40,   59,    8,   37,  282,   40,   13,   55,   40,
   57,   16,   45,   46,   14,   15,  283,   41,   51,   58,
   93,   41,   44,   29,   44,   30,   40,   60,   61,   93,
  123,   36,   32,  257,  258,  259,  260,   58,   40,   59,
   59,   46,   40,  125,   44,   41,   79,   80,   81,  262,
   41,  277,   91,   58,  263,    0,   89,   91,   41,   88,
   91,  283,  284,  285,  286,  125,   41,  100,   97,   41,
  103,   41,  105,   93,   59,   59,   41,   59,   41,  108,
   59,    9,  111,   88,   41,   44,   29,   58,   15,   27,
  100,   -1,   97,   -1,   -1,   -1,   -1,   41,   -1,   -1,
   -1,   -1,   -1,  108,   -1,   -1,  111,   -1,   -1,   -1,
  265,   -1,   -1,   44,  269,  270,  271,  272,  273,  274,
  275,  276,   -1,  278,  279,  280,  281,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  261,   -1,   -1,  264,
   -1,  266,  267,  268,   -1,   -1,   -1,   -1,   -1,  269,
  270,  271,  272,  273,  274,  275,  276,  282,  278,  279,
  280,  281,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  269,  270,  271,  272,  273,  274,  275,
  276,   -1,  278,  279,  280,  281,  277,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  263,  263,  263,  263,  263,   -1,
  263,   -1,   -1,   -1,   -1,  269,  270,  271,  272,  273,
  274,  275,  276,   -1,  278,  279,  280,  281,  269,  270,
  271,  272,  273,  274,  275,  276,   -1,  278,  279,  280,
  281,  282,  283,  284,  285,  286,  287,  282,  283,  284,
  285,  286,  287,  263,   -1,  265,  277,   -1,   -1,  269,
  270,  271,  272,  273,  274,  275,  276,   -1,  278,  279,
  280,  281,  282,  283,  284,  285,  286,  287,  282,  283,
  284,  285,  286,  269,  270,  271,  272,  273,  274,  275,
  276,   -1,  278,  279,  280,  281,  269,  270,  271,  272,
  273,  274,  275,  276,   -1,  278,  279,  280,  281,  269,
  270,  271,  272,  273,  274,  275,  276,   -1,  278,  279,
  280,  281,  269,  270,  271,  272,  273,  274,  275,  276,
   -1,  278,  279,  280,  281,  269,  270,  271,  272,  273,
  274,  275,  276,   -1,  278,  279,  280,  281,  269,  270,
  271,  272,  273,  274,  275,  276,   -1,  278,  279,  280,
  281,
};
#define YYFINAL 5
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#define YYUNDFTOKEN 310
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'",0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"KW_INT","KW_FLOAT","KW_BOOL","KW_CHAR","KW_IF","KW_THEN","KW_ELSE","KW_FOR",
"KW_TO","KW_READ","KW_RETURN","KW_PRINT","OPERATOR_LE","OPERATOR_GE",
"OPERATOR_EQ","OPERATOR_NE","OPERATOR_AND","OPERATOR_OR","OPERATOR_L",
"OPERATOR_G","OPERATOR_ATTR","OPERATOR_MUL","OPERATOR_DIV","OPERATOR_SUB",
"OPERATOR_ADD","TK_IDENTIFIER","LIT_INTEGER","LIT_FALSE","LIT_TRUE","LIT_CHAR",
"LIT_STRING","TOKEN_ERROR","IF_SIMPLE","EXPRESSION",0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : rootnode",
"rootnode : program",
"program : declaration ';' program",
"program :",
"datatype : KW_INT",
"datatype : KW_FLOAT",
"datatype : KW_BOOL",
"datatype : KW_CHAR",
"params : params_non_empty",
"params :",
"params_non_empty : datatype identifier ',' params_non_empty",
"params_non_empty : datatype identifier",
"init_literal_list : init_literal",
"init_literal_list : init_literal init_literal_list",
"init_literal : integer",
"init_literal : LIT_FALSE",
"init_literal : LIT_TRUE",
"init_literal : LIT_CHAR",
"integer : LIT_INTEGER",
"declaration : datatype identifier ':' init_literal",
"declaration : datatype identifier '[' integer ']' ':' init_literal_list",
"declaration : datatype identifier '[' integer ']'",
"declaration : datatype identifier '(' params ')' cmdblock",
"identifier : TK_IDENTIFIER",
"cmd : KW_READ identifier",
"cmd : KW_PRINT print_list",
"cmd : KW_RETURN exp",
"cmd : cmdblock",
"cmd : identifier OPERATOR_ATTR exp",
"cmd : identifier '[' exp ']' OPERATOR_ATTR exp",
"cmd : KW_IF '(' exp ')' KW_THEN cmd",
"cmd : KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd",
"cmd : KW_FOR '(' exp ')' cmd",
"cmd : KW_FOR '(' identifier OPERATOR_ATTR exp KW_TO exp ')' cmd",
"cmd :",
"print_list : LIT_STRING print_list",
"print_list : exp print_list",
"print_list : LIT_STRING",
"print_list : exp",
"cmdlist : cmd ';' cmdlist",
"cmdlist : cmd ';'",
"cmdblock : '{' cmdlist '}'",
"operator : OPERATOR_LE",
"operator : OPERATOR_GE",
"operator : OPERATOR_EQ",
"operator : OPERATOR_NE",
"operator : OPERATOR_L",
"operator : OPERATOR_G",
"operator : OPERATOR_AND",
"operator : OPERATOR_OR",
"operator : OPERATOR_MUL",
"operator : OPERATOR_DIV",
"operator : OPERATOR_SUB",
"operator : OPERATOR_ADD",
"exp : identifier",
"exp : identifier '[' exp ']'",
"exp : integer",
"exp : LIT_CHAR",
"exp : exp operator exp",
"exp : '(' exp ')'",
"exp : identifier '(' argument_list ')'",
"exp : LIT_FALSE",
"exp : LIT_TRUE",
"argument_list : argument_list_non_empty",
"argument_list :",
"argument_list_non_empty : exp ',' argument_list",
"argument_list_non_empty : exp",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 200 "parser.y"
int yyerror (const char *s) {
    fflush(stderr);
    fprintf(stderr,"ERROR: %s ---> Line: %d\n", s, getLineNumber());
    exit(3);
}
#line 394 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 87 "parser.y"
	{yyval.node = yystack.l_mark[0].node; semanticAnalyser(createNode(TREE_DECLARATION, NULL, yystack.l_mark[0].node, NULL, NULL, NULL));}
break;
case 2:
#line 90 "parser.y"
	{yyval.node = createNode(TREE_DECLARATION, NULL, yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL);}
break;
case 3:
#line 91 "parser.y"
	{yyval.node = NULL;}
break;
case 4:
#line 95 "parser.y"
	{ yyval.node = createNode(TREE_KW_INTEGER, NULL, NULL, NULL, NULL, NULL);}
break;
case 5:
#line 96 "parser.y"
	{ yyval.node = createNode(TREE_KW_FLOAT, NULL, NULL, NULL, NULL, NULL);}
break;
case 6:
#line 97 "parser.y"
	{ yyval.node = createNode(TREE_KW_BOOL, NULL, NULL, NULL, NULL, NULL);}
break;
case 7:
#line 98 "parser.y"
	{ yyval.node = createNode(TREE_KW_CHAR, NULL, NULL, NULL, NULL, NULL);}
break;
case 8:
#line 102 "parser.y"
	{ yyval.node = yystack.l_mark[0].node;}
break;
case 9:
#line 103 "parser.y"
	{ yyval.node = NULL;}
break;
case 10:
#line 106 "parser.y"
	{ yyval.node = createNode(TREE_DEC_FUC_PARAM_HEAD, NULL, yystack.l_mark[-3].node, yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL);}
break;
case 11:
#line 107 "parser.y"
	{ yyval.node = createNode(TREE_DEC_FUC_PARAM_TAIL, NULL, yystack.l_mark[-1].node, yystack.l_mark[0].node, NULL, NULL);}
break;
case 12:
#line 111 "parser.y"
	{ yyval.node = createNode(TREE_DEC_VAR_VEC_LIT_LIST_TAIL, NULL, yystack.l_mark[0].node, NULL, NULL, NULL);}
break;
case 13:
#line 112 "parser.y"
	{ yyval.node = createNode(TREE_DEC_VAR_VEC_LIT_LIST_HEAD, NULL, yystack.l_mark[-1].node, yystack.l_mark[0].node, NULL, NULL);}
break;
case 14:
#line 116 "parser.y"
	{ yyval.node = yystack.l_mark[0].node;}
break;
case 15:
#line 117 "parser.y"
	{ yyval.node = createNode(TREE_FALSE, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 16:
#line 118 "parser.y"
	{ yyval.node = createNode(TREE_TRUE, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 17:
#line 119 "parser.y"
	{ yyval.node = createNode(TREE_CHAR, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 18:
#line 123 "parser.y"
	{ yyval.node = createNode(TREE_INTEGER, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 19:
#line 126 "parser.y"
	{ yyval.node = createNode(TREE_DECLARATION_SCALAR, NULL, yystack.l_mark[-3].node, yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL);}
break;
case 20:
#line 127 "parser.y"
	{ yyval.node = createNode(TREE_DECLARATION_VEC_LIT, NULL, yystack.l_mark[-6].node, yystack.l_mark[-5].node, yystack.l_mark[-3].node, yystack.l_mark[0].node);}
break;
case 21:
#line 128 "parser.y"
	{ yyval.node = createNode(TREE_DECLARATION_VEC_NOLIT, NULL, yystack.l_mark[-4].node, yystack.l_mark[-3].node, yystack.l_mark[-1].node, NULL);}
break;
case 22:
#line 129 "parser.y"
	{ yyval.node = createNode(TREE_DECLARATION_FUC, NULL,  yystack.l_mark[-5].node, yystack.l_mark[-4].node, yystack.l_mark[-2].node, yystack.l_mark[0].node);}
break;
case 23:
#line 133 "parser.y"
	{ yyval.node = createNode(TREE_IDENTIFIER, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 24:
#line 136 "parser.y"
	{ yyval.node = createNode(TREE_CMD_READ, NULL, yystack.l_mark[0].node, NULL,NULL, NULL);}
break;
case 25:
#line 137 "parser.y"
	{ yyval.node = createNode(TREE_CMD_PRINT, NULL, yystack.l_mark[0].node, NULL,NULL, NULL);}
break;
case 26:
#line 138 "parser.y"
	{ yyval.node = createNode(TREE_CMD_RETURN, NULL, yystack.l_mark[0].node, NULL,NULL, NULL);}
break;
case 27:
#line 139 "parser.y"
	{ yyval.node = yystack.l_mark[0].node;}
break;
case 28:
#line 140 "parser.y"
	{ yyval.node = createNode(TREE_CMD_ATTR_VAR_SCALAR, NULL, yystack.l_mark[-2].node, yystack.l_mark[0].node,NULL, NULL);}
break;
case 29:
#line 141 "parser.y"
	{ yyval.node = createNode(TREE_CMD_ATTR_VAR_VEC, NULL, yystack.l_mark[-5].node, yystack.l_mark[-3].node, yystack.l_mark[0].node, NULL);}
break;
case 30:
#line 142 "parser.y"
	{ yyval.node = createNode(TREE_CMD_IF, NULL, yystack.l_mark[-3].node, yystack.l_mark[0].node, NULL, NULL);}
break;
case 31:
#line 143 "parser.y"
	{ yyval.node = createNode(TREE_CMD_IF_ELSE, NULL, yystack.l_mark[-5].node, yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL);}
break;
case 32:
#line 144 "parser.y"
	{ yyval.node = createNode(TREE_CMD_FOR, NULL, yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL);}
break;
case 33:
#line 145 "parser.y"
	{ yyval.node = createNode(TREE_CMD_FOR_TO, NULL, yystack.l_mark[-6].node, yystack.l_mark[-4].node, yystack.l_mark[-2].node, yystack.l_mark[0].node);}
break;
case 34:
#line 146 "parser.y"
	{ yyval.node = NULL;}
break;
case 35:
#line 150 "parser.y"
	{ yyval.node = createNode(TREE_CMD_PRINT_LIST_HEAD, NULL, createNode(TREE_STRING, yystack.l_mark[-1].symbol,NULL,NULL,NULL,NULL), yystack.l_mark[0].node,NULL, NULL);}
break;
case 36:
#line 151 "parser.y"
	{ yyval.node = createNode(TREE_CMD_PRINT_LIST_HEAD, NULL, yystack.l_mark[-1].node, yystack.l_mark[0].node,NULL, NULL);}
break;
case 37:
#line 152 "parser.y"
	{ yyval.node = createNode(TREE_CMD_PRINT_LIST_TAIL,NULL, createNode(TREE_STRING, yystack.l_mark[0].symbol,NULL,NULL,NULL,NULL), NULL,NULL, NULL);}
break;
case 38:
#line 153 "parser.y"
	{ yyval.node = createNode(TREE_CMD_PRINT_LIST_TAIL, NULL, yystack.l_mark[0].node, NULL,NULL, NULL);}
break;
case 39:
#line 157 "parser.y"
	{ yyval.node = createNode(TREE_CMD_LIST_HEAD, NULL, yystack.l_mark[-2].node, yystack.l_mark[0].node,NULL, NULL);}
break;
case 40:
#line 158 "parser.y"
	{ yyval.node = createNode(TREE_CMD_LIST_TAIL, NULL, yystack.l_mark[-1].node, NULL,NULL, NULL);}
break;
case 41:
#line 162 "parser.y"
	{ yyval.node = createNode(TREE_CMD_BLOCK, NULL, yystack.l_mark[-1].node, NULL,NULL, NULL);}
break;
case 42:
#line 165 "parser.y"
	{ yyval.node = createNode(TREE_LE, NULL, NULL, NULL,NULL, NULL);}
break;
case 43:
#line 166 "parser.y"
	{ yyval.node = createNode(TREE_GE, NULL, NULL, NULL,NULL, NULL);}
break;
case 44:
#line 167 "parser.y"
	{ yyval.node = createNode(TREE_EQ, NULL, NULL, NULL,NULL, NULL);}
break;
case 45:
#line 168 "parser.y"
	{ yyval.node = createNode(TREE_NE, NULL, NULL, NULL,NULL, NULL);}
break;
case 46:
#line 169 "parser.y"
	{ yyval.node = createNode(TREE_L, NULL, NULL, NULL,NULL, NULL);}
break;
case 47:
#line 170 "parser.y"
	{ yyval.node = createNode(TREE_G, NULL, NULL, NULL,NULL, NULL);}
break;
case 48:
#line 171 "parser.y"
	{ yyval.node = createNode(TREE_AND, NULL, NULL, NULL,NULL, NULL);}
break;
case 49:
#line 172 "parser.y"
	{ yyval.node = createNode(TREE_OR, NULL, NULL, NULL,NULL, NULL);}
break;
case 50:
#line 173 "parser.y"
	{ yyval.node = createNode(TREE_MUL, NULL, NULL, NULL,NULL, NULL);}
break;
case 51:
#line 174 "parser.y"
	{ yyval.node = createNode(TREE_DIV, NULL, NULL, NULL,NULL, NULL);}
break;
case 52:
#line 175 "parser.y"
	{ yyval.node = createNode(TREE_SUB, NULL, NULL, NULL,NULL, NULL);}
break;
case 53:
#line 176 "parser.y"
	{ yyval.node = createNode(TREE_ADD, NULL, NULL, NULL,NULL, NULL);}
break;
case 54:
#line 180 "parser.y"
	{yyval.node = yystack.l_mark[0].node;}
break;
case 55:
#line 181 "parser.y"
	{ yyval.node = createNode(TREE_EXP_VEC_INDEX, NULL, yystack.l_mark[-3].node, yystack.l_mark[-1].node,NULL, NULL);}
break;
case 56:
#line 182 "parser.y"
	{yyval.node = yystack.l_mark[0].node;}
break;
case 57:
#line 183 "parser.y"
	{ yyval.node = createNode(TREE_CHAR, yystack.l_mark[0].symbol, NULL, NULL,NULL, NULL);}
break;
case 58:
#line 184 "parser.y"
	{ yyval.node = createNode(TREE_EXP_OP_BINARY, NULL, yystack.l_mark[-2].node, yystack.l_mark[-1].node, yystack.l_mark[0].node, NULL);}
break;
case 59:
#line 185 "parser.y"
	{ yyval.node = createNode(TREE_EXP_BRACKET_ENCLOSURE, NULL, yystack.l_mark[-1].node,NULL, NULL, NULL);}
break;
case 60:
#line 186 "parser.y"
	{ yyval.node = createNode(TREE_EXP_FUNC_CALL, NULL, yystack.l_mark[-3].node,yystack.l_mark[-1].node, NULL, NULL);}
break;
case 61:
#line 187 "parser.y"
	{ yyval.node = createNode(TREE_FALSE, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 62:
#line 188 "parser.y"
	{ yyval.node = createNode(TREE_TRUE, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 63:
#line 191 "parser.y"
	{ yyval.node = yystack.l_mark[0].node;}
break;
case 64:
#line 192 "parser.y"
	{ yyval.node = NULL;}
break;
case 65:
#line 196 "parser.y"
	{ yyval.node = createNode(TREE_EXP_FUNC_CALL_ARG_LIST_HEAD, NULL, yystack.l_mark[-2].node,yystack.l_mark[0].node, NULL, NULL);}
break;
case 66:
#line 197 "parser.y"
	{ yyval.node = createNode(TREE_EXP_FUNC_CALL_ARG_LIST_TAIL, NULL, yystack.l_mark[0].node,NULL, NULL, NULL);}
break;
#line 860 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
