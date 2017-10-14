#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H
typedef struct {
    int * matrix;
    int sizemax;
} Graph;

Graph createGraph(int sizemax);
void addEdge(Graph g, int v1, int v2);
int isAdjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int vertex, int * output);
void printGraph(Graph g);
void dropGraph(Graph g);
#endif