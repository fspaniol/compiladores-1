#ifndef HASHCELLH
#define HASHCELLH
#define HASH_SIZE 997

#define SYMBOL_SCALAR 9
#define SYMBOL_VECTOR 10
#define SYMBOL_FUNCTION 11

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_FLOAT 2 
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_IDENTIFIER 4
#define SYMBOL_LIT_STRING 5
#define SYMBOL_LIT_IDENTIFIER_INT 6
#define SYMBOL_LIT_IDENTIFIER_FLOAT 7 
#define SYMBOL_LIT_IDENTIFIER_CHAR 8

typedef struct hashcell {
  char* key;
  int type;
  int initialized;
  int lineNumber;
  struct hashcell *next;
}HASHCELL;

//adds value to hash
HASHCELL* addHash(char *key, int type);
HASHCELL* getHash(char *key);
int hashFunction(char *key);
#endif