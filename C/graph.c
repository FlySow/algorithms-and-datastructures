#include "graph.c"
#include <stdlib.h>

struct graph create_graph(int size, bool complete) {
	struct node* nodes = calloc(size, sizeof(struct node));
	for(int i = 0; i < size; i++) {
		nodes[i]->name = i;
		//wip
	}
}
