// Raymond Ho
// rho5@ucsc.edu
// This contains the prototype for functions of a heap.

#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stdlib.h>
typedef struct HeapStruct*  heapHndl;
typedef struct NodeStruct*	NodePtr;


/*** Constructors-Destructors ***/

// Pre conditions: Enough memory to create a new heap.
// Post conditions: A new heap is created with indicated size.
heapHndl newHeap (int minSize);


// Optional for testing purposes.
heapHndl buildHeap (int minSize, int data[], int numData);

// Pre conditions: A heap must already exist.
// Post conditions: The heap is now freed to prevent memory leaks.
void freeHeap(heapHndl H);


/*** Functions ***/

// Pre conditions: A heap must exist to check if it's full.
// Post conditions: Returns true if the heap is full, false otherwise.
bool isFull(heapHndl H);

// Pre conditions: A heap must exist to check if it's empty.
// Post conditions: Returns true if the heap is empty, false otherwise.
bool heapEmpty(heapHndl H);

// Pre conditions: A heap must not be empty
// Post conditions: Returns the min value in the heap.
int minValue(heapHndl H);

// Pre conditions: A heap must have a min value. ie not empty.
// Post conditions: The min value will be deleted from the heap.
void deleteMin(heapHndl H);

// Pre conditions: A heap must not be full.
// Post conditions: The heap is no longer empty.
void insert(heapHndl H, int priority);

// Pre conditions: A heap must have at least two elements to swap.
// Post conditions: Elements A and B will be swapped.
void swap(heapHndl H, int a, int b);

// Pre conditions: A heap must not be empty.
// Post conditions: The heap is now sorted
void sortHeap(heapHndl H);

// Post condition: Heap is printed
void printHeap(heapHndl H);

#endif
