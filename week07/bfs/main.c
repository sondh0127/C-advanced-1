#include <stdio.h>
#include "graph_jrb.h"
#include "bfs.h"

void printVertex(int v) {
    printf("%4d", v);
}

int main() {
    // 0___1___2___4___5
    //     |   |
    //     3___|
    printf("Graph:\n");
    printf("0__1__2__4__5\n");
    printf("   |  |\n");
    printf("   3__|\n");
    Graph g = createGraph();
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 5);
    printf("\nBFS: start from node 1 to 4:\n");
    BFS(g, 1, 4, printVertex);
    printf("\nBFS: start from node 1 to all:\n");
    BFS(g, 1, -1, printVertex);
    printf("\n");

    return 0;
}