// Raymond Ho
// rho5@ucsc.edu
//
// This is the header file of the graph ADT. This file will be used by
// the driver and main program. It contains the prototype functions to be
// implemented in graph.c

#ifndef __GRAPH_H_
#define __GRAPH_H_

#include "list.h"

// Don't be afraid of pointers. 
typedef struct Graph Graph;

// Pre: None
// Post: creates a new graph with n vertices numbered 0 to n − 1 and no edges, 
// and returns a handle to it.
Graph *newGraph(int n);

// Pre: G must exist
// Post: Adds the edge(from, to) the graph
void addEdge(Graph *G, int from, int to);

// Pre: G must exist
// Post: Frees the storage used by a no longer needed Graph object.
void freeGraph(Graph *G);

// Pre: G must exis*t
// Post: Performs Breadth first search and updates the graph's parent
//      and distance arrays. This will also erase the results of previous BFS.
void doBFS(Graph *G, int source);

// Pre: G must exist
// Post: Returns the number of edges in the shortest path from the last
//      BFS source to the destination. Return -1 if no possible path.
int getDistance(Graph *G, int destination);

// Pre: G must exist
// Post: Returns a list containing the path from the last doBFS source.
ListHndl getPathTo(Graph *G, int destination);

// For debugging purposes only.
// Prints the graph.
void printGraph(Graph *G);

#endif


