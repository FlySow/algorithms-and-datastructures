#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <bool.h>
#include <linked_list.h>

struct node {
	int name;
	struct linked_list neightbours;
};

struct graph {
	int node_size;
	struct node nodes[];
};

struct graph create_graph(int size, bool complete);

int[] depth_first_search(struct graph, int strt_node);

#endif
