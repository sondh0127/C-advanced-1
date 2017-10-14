#include <stdio.h>
#include "bfs.h"
#include "../../lib/Libfdr/dllist.h"
#include "../../lib/Libfdr/jrb.h"
#define SIZEMAX 100

void BFS(Graph g, int start, int stop, void (*func)(int)) {
    Graph node;
    Graph visited = createGraph();
    Dllist queue;
    Dllist temp;
    int adjacents[SIZEMAX];
    int count;
    int i;
    int key;

    node = jrb_find_int(g, start);
    if (node == NULL) {
        printf("Graph does not have vertex %d\n", start);
        return;
    }
    
    // Create a graph name 'visited' in which each node's key is
    // a vertex, and it's key indicate whether the vertex has been
    // visited (1) or not (0)
    jrb_traverse(node, g) {
        jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));
    }

    // Create a queue and enqueue the first element
    queue = new_dllist();
    dll_append(queue, new_jval_i(start));

    // Traversing
    while(dll_empty(queue) != 1) {
        // Take first element in the queue
        temp = dll_first(queue);
        key = jval_i(temp->val);
        
        // Pass the vertex to external function
        (*func)(key);

        // If this is the required vertex, return
        if (key == stop) {
            return;
        }
        
        // Dequeue this element
        dll_delete_node(temp);

        // Mark this element as 'visited'
        node = jrb_find_int(visited, key);
        jrb_delete_node(node);
        jrb_insert_int(visited, key, new_jval_i(1));

        count = getAdjacentVertices(g, key, adjacents);
        for (i = 0; i < count; i++) {
            // If the vertice has not been visited, enqueue it
            node = jrb_find_int(visited, adjacents[i]);
            if (jval_i(node->val) == 0) {
                key = jval_i(node->key);
                dll_append(queue, new_jval_i(key));
                // Mark this element as 'visited'
                jrb_delete_node(node);
                jrb_insert_int(visited, key, new_jval_i(1));
            }
        }
    }
}