#ifndef HASHCELLH
#define HASHCELLH
#define HASH_SIZE 997

#define SYMBOL_SCALAR 9
#define SYMBOL_VECTOR 10
#define SYMBOL_FUNCTION 11

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_FLOAT 2 
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_IDENTIFIER 4
#define SYMBOL_STRING 5
#define SYMBOL_IDENTIFIER_SCALAR 6
#define SYMBOL_IDENTIFIER_VECTOR 7 
#define SYMBOL_IDENTIFIER_FUNCTION 8
#define DATATYPE_INT
#define DATATYPE_FLOAT
#define DATATYPE_CHAR
#define DATATYPE_BOOL

typedef struct hashcell {
  char* key;
  int type;
  int datatype;
  int lineNumber;
  struct hashcell *next;
}HASHCELL;

//adds value to hash
HASHCELL* addHash(char *key, int type);
HASHCELL* getHash(char *key);
int hashFunction(char *key);
#endif