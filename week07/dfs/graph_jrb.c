#include <stdio.h>
#include "graph_jrb.h"

Graph createGraph() {
    Graph g = make_jrb();
    return g;
}

void addEdge(Graph g, int v1, int v2) {
    Graph node = jrb_find_int(g, v1);
    if (node == NULL) {
        Graph tree = make_jrb();
        jrb_insert_int(g, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(1));
    } else {
        Graph tree = jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }

    node = jrb_find_int(g, v2);
    if (node == NULL) {
        Graph tree = make_jrb();
        jrb_insert_int(g, v2, new_jval_v(tree));
        jrb_insert_int(tree, v1, new_jval_i(1));
    } else {
        Graph tree = jval_v(node->val);
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
}

int isAdjacent(Graph g, int v1, int v2) {

}

int getAdjacentVertices(Graph g, int v, int * output) {
    int total = 0;
    Graph node = jrb_find_int(g, v);
    if (node != NULL) {
        Graph tree = jval_v(node->val);
        jrb_traverse(node, tree) {
            output[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}

void printGraph(Graph g) {
    Graph node;
    jrb_traverse(node, g) {
        printf("%d: ", jval_i(node->key));
        Graph tree = jval_v(node->val);
        Graph temp;
        jrb_traverse(temp, tree) {
            printf("%d ", jval_i(temp->key));
        }
        printf("\n");
    }
}

void dropGraph(Graph g) {
    Graph node;
    jrb_traverse(node, g) {
        jrb_free_tree(jval_v(node->val));
    }
}