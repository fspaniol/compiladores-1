#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int inited=0;
HASHCELL* table[HASH_SIZE];

void initHash() {
  int i;
  if(!inited) {
    for(i=0;i<HASH_SIZE;i++) {
      table[i]=NULL;
    }
    inited=1;
  }
}

HASHCELL* getHASHCELL(char* key) {
  int address = hashFunction(key); 
  HASHCELL *position = table[address];
  if(position==NULL)
    return NULL;
  while(strcmp(position->key, key)!=0){
    if(position->next == NULL)
      return NULL;  
    position = position->next;
  }
  return position;
}


int hashFunction(char *key) {
  int address = 1;
  int i;
  for(i=0; i<strlen(key); i++) {
    address = (address * key[i])%HASH_SIZE +1;
  }
  return address;
}

HASHCELL* addHash(char *key, int type) {
  int address;
  if(!inited)
    initHash();
  printf("adding to hash %s \n", key);
  HASHCELL *ptr;
  address = hashFunction(key);
  ptr = getHASHCELL(key);
  if(ptr!=NULL)
    return ptr;

  HASHCELL *cell = (HASHCELL*) calloc(sizeof(HASHCELL), 1);

  cell->type = type;
  cell->datatype = -1;
  cell->next = NULL;
  char *keycpy = calloc(strlen(key)+1,1);
  strncpy(keycpy, key, strlen(key));
  cell->key = keycpy;
  if(table[address] == NULL) {
    table[address] = cell;
  } else {
      ptr = table[address];
      while(ptr->next != NULL) {
        ptr = ptr->next;
      }
      ptr->next = cell;
  }
  return cell;
}


HASHCELL* getHash(char *key) {
  if(!inited)
    initHash();
  int address = hashFunction(key);
  HASHCELL *ptr = getHASHCELL(key);
  return ptr;
}
