#define HASH_SIZE 997

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_FLOAT 2 
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_IDENTIFIER 4
#define SYMBOL_LIT_STRING 5
typedef struct hashcell {
  char* key;
  int type;
  struct hashcell *next;
}HASHCELL;

//adds value to hash
HASHCELL* addHash(char *key, int type);
HASHCELL* getHash(char *key);
  