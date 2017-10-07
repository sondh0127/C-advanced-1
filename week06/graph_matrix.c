#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int * matrix;
    int sizemax;
    // Not sure whether sizemax = 100 means matrix[100 * 100] or matrix[10 * 10]
    // The implementation in this file follow the latter
} Graph;

Graph createGraph(int sizemax);
void addEdge(Graph g, int v1, int v2);
int isAdjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int vertex, int * output); // return the number of adjacent vertices
void printGraph(Graph g);
void dropGraph(Graph g);

int main() {
    int i, n, output[100];
    Graph g = createGraph(100);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    n = getAdjacentVertices(g, 1, output);
    if (n == 0) {
        printf("No adjacent vertices of node 1.\n");
    } else {
        printf("Adjacent vertices of node 1:");
        for (i = 0; i < n; i++) {
            printf("%5d", output[i]);
        }
        printf("\n");
    }
    printGraph(g);
    dropGraph(g);

    return 0;
}

Graph createGraph(int sizemax) {
    Graph g;
    g.matrix = (int *)malloc(sizemax * sizeof(int));
    g.sizemax = sizemax;
    return g;
}

void addEdge(Graph g, int v1, int v2) {
    int size = sqrt(g.sizemax);
    if (v1 > size - 1 || v2 > size - 1) {
        printf("Graph can only contains vertex no bigger than %d\n", size);
        return;
    }
    g.matrix[v1 * size + v2] = 1;
    g.matrix[v2 * size + v1] = 1;
}

int isAdjacent(Graph g, int v1, int v2) {
    int * matrix = g.matrix;
    int size = sqrt(g.sizemax);
    if (matrix[v1 * size + v2] == 1) return 1;
    return 0;
}

int getAdjacentVertices(Graph g, int vertex, int * output) {
    int * matrix = g.matrix;
    int size = sqrt(g.sizemax);
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
    int sizemax = g.sizemax;
    int size = sqrt(sizemax);
    int i;
    for (i = 0; i < sizemax; i++) {
        printf("%d ", matrix[i]);
        if ((i + 1)%size == 0) printf("\n");
    }
}

void dropGraph(Graph g) {
    free(g.matrix);
    g.sizemax = 0;
}