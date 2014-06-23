// Raymond Ho
// rho5@ucsc.edu
//
// This is the implementation file of a hash set.
//

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// A Book structure contaning a list of library ID and title.
typedef struct Book {
    ListStruct* libID; // Each book has its own list of library IDs
    char name[40]; // Each book has a name.
} Book;

// A hashset contains a linked list of books.
typedef struct HashStruct {
    int size;
    NodeStruct **chain; //An array of Linked Lists.
} HashStruct;

// Constructor for a new book.
// Copies the name using strncpy
// Creates a new linked list of type (int).
Book *newBook(char* name, int value) {
    Book *this = malloc (sizeof(Book));
    assert(this != NULL);
    strncpy(this->name, name, 40);
    this->libID = newList(sizeof(int));
    insertAtBack(this->libID, &value);
    return this;
}

// Constructor for a hashset.
// Mallocs memory for each index of the array with given size input.
// Sets each index of array to 0.
HashHandle new_hashset(int size) {
    HashHandle tempHash = malloc (sizeof (HashStruct));
    assert (tempHash != NULL);
    tempHash->size = size;
    int sizeof_chain = size * sizeof(NodeStruct*);
    tempHash->chain = malloc(sizeof_chain);
    assert(tempHash->chain != NULL);
    memset(tempHash->chain, 0, sizeof_chain);
    return tempHash;
}

// Destructor for a hashset
// Recursively starts from to bottom to free malloc'ed memory.
void free_hashset (HashHandle this) {
    for (int i = 0; i < this->size; i++) {
        if (this->chain[i] == NULL) continue;
        NodeStruct *tmp = this->chain[i];
        Book *book;
        while (tmp != NULL) {
            NodeStruct *next = tmp->next; 
            book = tmp->data;
            freeList(&book->libID);
            free(tmp->data);
            free(tmp);
            tmp = next;
        }
    }
    free(this->chain);
    free(this);
}

// A function to place an item into the hashset
// If the item is found, the value will be appended to its linked list.
void put_hashset (HashHandle this, char *item, int value) {
    assert(this != NULL);
    
    // If the item is already in the hash table
    // Simply add the value to its list.
    ListStruct* list = has_hashset(this, item);
    if (list != NULL) insertAtBack(list, &value);
    
    // This means the item was not found.
    else {
        // Get Hash index of string.
        int index = strhash(item) % this->size;
        // Create a new book.
        Book *book = newBook(item, value); 
        NodeStruct *it = malloc(sizeof(NodeStruct));
        // Since book is allocated already, we can direct assign it.
        it->data = book;
        it->next = NULL;
        // Add to list
        NodeStruct *tmp = this->chain[index];
        it->next = tmp;
        this->chain[index] = it;
    }
}

// Checks to see if item exists in hashtable,
// If it does, return a pointer to it's linked list (library IDs)
// Return NULL if not found.
ListStruct* has_hashset (HashHandle this, char *item) { 
    //Finds the index to look at.
    int index = strhash(item) % this->size;
    if (this->chain[index] == NULL) return NULL;

    NodeStruct *tmp = this->chain[index];
    Book *book;
    while (tmp != NULL) {
        book = tmp->data;
        assert(book->name != NULL);
        if (strncmp(item, book->name, 40) == 0)
            return book->libID;
        tmp = tmp->next;
    }
    return NULL;
}

// Converts a string to a size_t using Horner's method to
// compute the hash code of a string.
// Reference: java.lang.String.hashCode
//
unsigned int strhash (char *string) {
    assert (string != NULL);
    unsigned int hashcode = 0;
    while (*string) hashcode = (hashcode << 5) - hashcode + *string++;
    return hashcode;
}

// Print the Hash for debugging issues.
void printHash(HashHandle H) {
    for (int i = 0; i < H->size; i++) {
        printf("Slot %d: ", i); 
        NodeStruct *cur = H->chain[i];
        Book *book;
        while (cur != NULL) {
            book = cur->data;
            printf("%s->", book->name);
            printList(NULL, book->libID, 1);
            cur = cur->next;
        }
        printf("\n");
    }
}

