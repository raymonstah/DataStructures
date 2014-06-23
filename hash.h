// Raymond Ho
// rho5@ucsc.edu
//
// This file contains the prototype functions of a hashset to 
// be implemented in hash.c

#ifndef __HASH_H__
#define __HASH_H__

#include "list.h"
#include <stdbool.h>

// I'm not a big fan of Handles.. but using this per instructor's spec.
typedef struct HashStruct* HashHandle;

// Pre condition: size must be greater than 0.
// Post condition: Create a new hashset with a given size.
HashHandle new_hashset (int size);

// Pre condition: H is not NULL
// Post condition: Frees the hashset, and the words it points at.
void free_hashset (HashHandle H);

// Pre condition: H is not NULL
// Post condition: Inserts a new string into the hashset.
// If string exists, it is overwritten.
void put_hashset (HashHandle H, char*, int);

// Pre condition: H is not NULL
// Post condition: Looks up the string in the hashset. 
// Returns pointer to List if found, NULL if not found.
ListStruct* has_hashset (HashHandle H, char*);

// Pre condition: The argument passed in is not null
// Post condition: Returns a size_t, hashcode of that string.
unsigned int strhash(char *string);

// For debugging purposes only.
void printHash(HashHandle H);

#endif

