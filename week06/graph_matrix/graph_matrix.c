#include <stdio.h>
#include <stdlib.h>
#include "graph_matrix.h"

Graph createGraph(int sizemax) {
    Graph g;
    g.matrix = (int *)malloc(sizemax * sizemax * sizeof(int));
    g.sizemax = sizemax;
    return g;
}

void addEdge(Graph g, int v1, int v2) {
    int size = g.sizemax;
    if (v1 > size - 1 || v2 > size - 1) {
        printf("Graph can only contains vertex no bigger than %d\n", size);
        return;
    }
    g.matrix[v1 * size + v2] = 1;
    g.matrix[v2 * size + v1] = 1;
}

int isAdjacent(Graph g, int v1, int v2) {
    int * matrix = g.matrix;
    int size = g.sizemax;
    if (matrix[v1 * size + v2] == 1) return 1;
    return 0;
}

int getAdjacentVertices(Graph g, int vertex, int * output) {
    int * matrix = g.matrix;
    int size = g.sizemax;
    int i;
    int count = 0;
    for (i = 0; i < size; i++) {
        if (matrix[i * size + vertex] == 1) {
            output[count] = i;
            count++;
        }
    }
    return count;
}

void printGraph(Graph g) {
    int * matrix = g.matrix;
    int size = g.sizemax;
    int i;
    for (i = 0; i < size * size; i++) {
        printf("%d ", matrix[i]);
        if ((i + 1)%size == 0) printf("\n");
    }
}

void dropGraph(Graph g) {
    free(g.matrix);
    g.sizemax = 0;
}