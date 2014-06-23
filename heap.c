// Raymond Ho
// rho5@ucsc.edu
// This contains the implementations of a heap.

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "heap.h"

// The data structure of a heap.
// Uses array to store data.
typedef struct HeapStruct {
    int maxSize;
    int currentSize;
    int *array;
} HeapStruct;

// Create a new heap allocating memory.
heapHndl newHeap (int maxSize) {
    heapHndl tmp = malloc(sizeof(struct HeapStruct));
    assert (tmp != NULL); // No more memory to assign.
    tmp->maxSize = maxSize;
    tmp->currentSize = 0;
    tmp->array = malloc(sizeof(int) * (maxSize +1 ));
    return tmp;
}

// Optional for testing purposes.
heapHndl buildHeap (int maxSize, int data[], int numData) {
    heapHndl tmp = malloc(sizeof(struct HeapStruct));
    assert(tmp!= NULL);
    tmp->maxSize = maxSize;
    tmp->currentSize = 0;
    tmp->array = malloc(sizeof(int) * (maxSize+1));
    // Array[0] reserved for number of elements in array.
    tmp->array[0] = numData;
    for (int i = 0; i < numData; i++)
        insert (tmp, data[i]);
    // If currentSize != numData, there must've
    // been a bad user input. Exit program.
    assert(tmp->currentSize == numData);
    return tmp;
}

// Free malloced memory used by heap and array.
void freeHeap(heapHndl H) {
    free(H->array);
    free(H);
}

// Returns true/false if the heap is full.
bool isFull(heapHndl H) {
    return H->currentSize == H->maxSize;

}

// Returns true/false if the heap is empty.
bool heapEmpty(heapHndl H){
    return H->currentSize == 0;

}

// This function returns the min value of the heap.
int minValue(heapHndl H) {
    assert (!heapEmpty(H));
    // The root should have the largest value.
    return H->array[1];

}

// This function deletes the min element of the heap.
void deleteMin(heapHndl H) {
    // Makes sure the heap is not empty.
    assert(!heapEmpty(H));

    int root = 1;
    // Swap the root and last element.
    swap(H, root, H->currentSize);
    H->currentSize--;
    int tmp = H->array[root];
    for (int child; root * 2 <= H->currentSize; root = child) {
        // child is the left child.
        child = root * 2;
        // If left child is greater than right child, child becomes right child.
        if (child != H->currentSize && H->array[child+1] < H->array[child])
            child++;
        // Swap if child is less than tmp.
        if (H->array[child] < tmp) swap(H, root, child);
        else break;
    }
    H->array[root] = tmp;
}

// This function inserts an element into the heap.
void insert(heapHndl H, int priority) {
    // Makes sure heap has enough room for new element.
    assert(!isFull(H));
    // Increase the current size.
    H->currentSize++;
    // Add to array.
    int pos = H->currentSize;
    // Work up. (C rounds down).
    while (pos > 1 && priority < H->array[pos/2]) {
        swap (H, pos, pos/2);
        pos /= 2;
    }
    H->array[pos] = priority;
}

// This function swaps two elements of the array.
void swap(heapHndl H, int a, int b) {
    int tmp = H->array[a];
    H->array[a] = H->array[b];
    H->array[b] = tmp;
}

// This function simply prints out the heap.
void printHeap(heapHndl H) {
    for (int i = 1; i < H->currentSize + 1; ++i)
        printf("%d ", H->array[i]);
    if (H->currentSize == 0) printf("Heap is empty.\n");
    printf("\n");
}

