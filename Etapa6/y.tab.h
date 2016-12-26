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
extern YYSTYPE yylval;
