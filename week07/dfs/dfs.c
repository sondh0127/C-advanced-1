#include <stdio.h>
#include "dfs.h"
#include "../../lib/Libfdr/dllist.h"
#include "../../lib/Libfdr/jrb.h"

void DFS(Graph g, int start, int stop, void (*func)(int)) {
    Graph node;
    Graph visited = createGraph();
    Dllist stack;
    Dllist temp;
    
    int count;
    int i;
    int key;

    JRB check1 = jrb_find_int(g,start);
	JRB check2 = jrb_find_int(g,stop);
	if(check1 == NULL ) {
		printf("Graph does not have vertex %d\n", start);
		return;
	}
	if(stop != -1 && check2 == NULL) {
		printf("Graph does not have vertex %d\n", stop);
		return;
	}

    int V = 0;
    // Create a graph name 'visited' in which each node's key is
    // a vertex, and it's key indicate whether the vertex has been
    // visited (1) or not (0)
    jrb_traverse(node, g) {
    	V++;
        jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));
    }
    int adjacents[V];
    // Create a stack and push the first element
    stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    // Traversing
    while(dll_empty(stack) != 1) {
        // Take the top element in the stack
        temp = dll_last(stack);
        key = jval_i(temp->val);
        
        // Mark this element as 'visited'
        node = jrb_find_int(visited, key);
        if(jval_i(node->val) == 0) {
        	// Pass the vertex to external function
        	(*func)(key);

        	// Mark this element as 'visited'
        	jrb_delete_node(node);
        	jrb_insert_int(visited, key, new_jval_i(1));

        } else {
        	// Pop this element
        dll_delete_node(temp);
        }
        
        
        // If this is the required vertex, return
        if (key == stop) {
        	free_dllist(stack);
			jrb_free_tree(visited);
            return;
        }
        
        count = getAdjacentVertices(g, key, adjacents);
        for (i = 0; i < count; i++) {
            // If the vertice has not been visited, push it
            node = jrb_find_int(visited, adjacents[i]);
            if (jval_i(node->val) == 0) {
                key = jval_i(node->key);
                dll_append(stack, new_jval_i(key));
            }
        }
    }
    free_dllist(stack);
	jrb_free_tree(visited);
}