#include "graph.h"
#include <stdlib.h>
#include "linked_list.h"

void* id(const int i) {
	res = malloc(sizeof(int));
	*res = i;
	return res;
}

struct graph create_graph(int size, bool complete) {
	struct node* nodes = calloc(size, sizeof(struct node));
	for(int i = 0; i < size; i++) {
		nodes[i]->name = i;
		if(complete)
			nodes[i]->neighbours = ll_create(size, id);
		else
			nodes[i]->neighbours = ll_create(0, NULL);

	}
	return (struct graph) {.node_size = size, .nodes = nodes};
}

int[] depth_first_search(struct graph, int strt_node) {
	//wip, need stack structure
}


