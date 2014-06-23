// Raymond Ho
// rho5@ucsc.edu
//
// This is the implementation of the functions in graph.h
//

#include <stdlib.h>
#include <assert.h>
#include "graph.h"

typedef struct Graph {
    ListHndl *vertices;
    int *color; // 0 = White, 1 = Grey, 2 = Black
    int *parent;
    int *distance;
    int numVertices;
    int numEdges;
} Graph;

// Create a new graph, return pointer to it.
Graph *newGraph(int n) {
    Graph *tmp = malloc(sizeof(Graph));
    tmp->numVertices = n;
    tmp->numEdges = 0;
    tmp->vertices = calloc(n, sizeof(ListHndl));
    tmp->color = calloc(n, sizeof(int));
    tmp->parent = calloc(n, sizeof(int));
    tmp->distance = calloc(n, sizeof(int));

    // Makes sure enough memory was available.
    assert(tmp && tmp->vertices && tmp->color 
            && tmp->parent && tmp->distance);

    for (int i = 0; i < n; ++i) tmp->vertices[i] = newList();

    return tmp;
}

// Add an edge to a graph by appending it to given linked list.
void addEdge(Graph *G, int from, int to) {
    insertAtBack(G->vertices[from], to);
    G->numEdges++;
}

// Free memory to prevent leaks.
void freeGraph(Graph *G) {
    for (int i = 0; i < G->numVertices; ++i)
        freeList(&G->vertices[i]);
    free(G->vertices);
    free(G->color);
    free(G->parent);
    free(G->distance);
    free(G);
}

// Perform breadth first search on graph with given source.
void doBFS(Graph *G, int source) {

    // Initialize graph first.
    for (int i = 0; i < G->numVertices; ++i) {
        G->color[i] = 0; // Set to white.
        G->distance[i] = 0;
        G->parent[i] = -1;
    }
    
    G->color[source] = 1; // Set to grey.
    G->distance[source] = 0;

    // Create a list Q and add source to it.
    ListHndl Q = newList();
    insertAtBack(Q, source);
    while (!isEmpty(Q)) {
        //Dequeue and delete first element.
        int u = getFirst(Q); deleteFirst(Q);
        // Move current position to point at first.
        if (!isEmpty(G->vertices[u])) moveFirst(G->vertices[u]);
        //Traverse vertices of u.
        while (!offEnd(G->vertices[u])) {
            int v = getCurrent(G->vertices[u]);
            if (G->color[v] == 0) { // Check if V is white.
                G->color[v] = 1; // Color V grey.
                G->distance[v] = G->distance[u] + 1;
                G->parent[v] = u;
                insertAtBack(Q, v);
            }
            moveNext(G->vertices[u]);
        }
        G->color[u] = 2; // Color u black.
    }
    freeList(&Q);
}

// Return the distance of a given destination
int getDistance(Graph *G, int destination) {
    if (G->distance[destination] == 0) return -1;
    return G->distance[destination];
}

// Return the List handle of paths to a destination.
ListHndl getPathTo(Graph *G, int destination) {
    int distance = getDistance(G, destination);
    if (distance == -1) return NULL;

    ListHndl tmp = newList(); // Freed by user.
    insertAtBack(tmp, destination);
    for (int i = 0; i < distance; ++i) {
        insertAtFront(tmp, G->parent[destination]);
        destination = G->parent[destination];
    }
    return tmp;
}

void printGraph(Graph *G) {
    for (int i = 0; i < G->numVertices; ++i) {
        printf("%d: ", i);
        printList(NULL, G->vertices[i]);
    }
}

