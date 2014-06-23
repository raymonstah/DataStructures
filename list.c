//	Raymond Ho
//	rho5@ucsc.edu
//	This file contains all of the implementations for list module.

#include "list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct NodeStruct {
    int data;
    struct NodeStruct* next;
    struct NodeStruct* prev;
} NodeStruct;

//	Rename NodeStruct* as NodePtr
typedef NodeStruct* NodePtr;

typedef struct ListStruct {
    NodePtr first;
    NodePtr last;
    NodePtr current;
} ListStruct;

//	ListHndl is just a ListStruct* renamed.

/*** Constructors-Destructors ***/


ListHndl newList() {

    ListHndl tempList;
    tempList = malloc (sizeof(ListStruct));
    assert(tempList != NULL);
    tempList->first = NULL;
    tempList->last = NULL;
    tempList->current = NULL;
    return tempList;
}

void freeList(ListHndl* L) {
    makeEmpty(*L);
    free(*L);
}

NodePtr newNode() {

    NodePtr tempNode;
    tempNode = malloc (sizeof(NodeStruct));
    assert(tempNode != NULL);
    tempNode->next = NULL;
    tempNode->prev = NULL;
    return tempNode;
}

/*** Access functions ***/

// returns true is list is empty else returns false.
bool isEmpty(ListHndl L) {
    return L->first == NULL;
}

// returns true if current == NULL
bool offEnd(ListHndl L) {
    return L->current == NULL;
}

// returns true if current == first and !offEnd()
bool atFirst(ListHndl L) {
    return !offEnd(L) && (L->current == L->first);
}

// returns true if current == last and !offEnd()
bool atLast(ListHndl L) {
    return !offEnd(L) && (L->current == L->last);

}

// return the first element; pre: !isEmpty()
int getFirst(ListHndl L) {
    assert(!isEmpty(L));
    return L->first->data;
}

// return the last element; pre: !isEmpty()
int getLast(ListHndl L) {
    assert(!isEmpty(L));
    return L->last->data;
}

// return the current element pre: !offEnd()
int getCurrent(ListHndl L) {
    assert(!isEmpty(L));
    return L->current->data;
}


/*** Manipulation procedures ***/

// delete all elements from the list,
// making it empty. Post: isEmpty(), offEnd() are both true
void makeEmpty(ListHndl L) {

    //Iterate L.
    NodePtr curr = NULL;
    while(L->first != NULL) {
        curr = L->first;
        L->first = L->first->next;
        free(curr);
    }

}

// without changing list order, make the first element
// the current one.  Pre: !isEmpty(); Post: !offEnd()
void moveFirst(ListHndl L) {
    assert (!isEmpty(L));
    L->current = L->first;

}

// without changing list order, make the last element 2
// the current one. Pre: !isEmpty(); Post: !offEnd()
void moveLast(ListHndl L) {
    assert (!isEmpty(L));
    L->current = L->last;

}


// move the current marker one element earlier in the list
// Pre: !offEnd();   Post: offEnd() only if atFirst() was true
void movePrev(ListHndl L) {
    assert (!offEnd(L));
    L->current = L->current->prev;

}

// move the current marker one element later in the list.
// Pre: !offEnd();   Post: offEnd() only if atLast() was true
void moveNext(ListHndl L) {
    assert (!offEnd(L));
    L->current = L->current->next;

}

// Inserts new element before first
// Post: !isEmpty(); doesn’t change current element
void insertAtFront(ListHndl L, int data) {
    NodePtr tmp = newNode();
    tmp->data = data;
    tmp->next = L->first;
    L->first = tmp;
    if (L->last == NULL) L->last = L->first;
}

// Inserts new element after last one
// Post: !isEmpty(); doesn’t change current element
void insertAtBack(ListHndl L, int data) {
    NodePtr tmp = newNode();
    tmp->data = data;
    tmp->prev = L->last;
    tmp->next = NULL;
    if (L->first == NULL) L->first = tmp;
    else L->last->next = tmp;
    L->last = tmp;
}

// Inserts new element before current one
// Pre: !offEnd(); Post: !isEmpty(), !offEnd(), !atFirst()
void insertBeforeCurrent(ListHndl L, int data) {
    assert (!offEnd(L));
    NodePtr tmp = newNode();
    tmp->data = data;
    tmp->prev = L->current->prev;
    tmp->next = L->current;
    if (L->current->prev == NULL) L->first = tmp;
    else L->current->prev->next = tmp;
    L->current->prev = tmp;
    if (L->last == NULL) L->last = L->current;
}

// Insert new element in order
// Post: !isEmpty()
void insertOrder(ListHndl L, int data) {

    NodePtr tmp = newNode();
    tmp->data = data;

    NodePtr prev = NULL;
    NodePtr curr = L->first;

    while (curr != NULL && data > curr->data) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) L->last = tmp;
    if (prev == NULL) L->first = tmp;
    else prev->next = tmp;
    tmp->next = curr;

}
// delete the first element. Pre: !isEmpty()
void deleteFirst(ListHndl L) {
    assert (!isEmpty(L));
    NodePtr tmp = L->first;
    L->first = L->first->next;
    if (L->first) L->first->prev = NULL;
    free(tmp);

}

// delete the last element. Pre: !isEmpty()
void deleteLast(ListHndl L) {
    assert (!isEmpty(L));
    NodePtr tmp = L->last;
    L->last = L->last->prev;
    L->last->next = NULL;
    free(tmp);
}

// delete the current element.
// Pre: !isEmpty(), !offEnd(); Post: offEnd()
void deleteCurrent(ListHndl L) {
    assert (!isEmpty(L) || !offEnd(L));
    NodePtr tmp = L->current;
    if (L->current->prev != NULL)
        L->current->prev->next = L->current->next;
    if (L->current->next != NULL)
        L->current->next->prev = L->current->prev;
    L->current = NULL;
    free(tmp);
}

/*** Other operations ***/

// prints out the list with the
// current element marked, helpful for debugging
void printList(FILE* out, ListHndl L) {
    if (out == NULL) out = stdout;
    NodePtr tmp = L->first;
    while (tmp != NULL) {
        if (tmp == L->current)
            fprintf(out, "[%d] ", tmp->data);
        else fprintf(out, "%d ", tmp->data);
        tmp = tmp->next;
    }
    if (L->first == NULL) fprintf(out, "List is empty.\n");
    else fprintf(out, "\n");
}





