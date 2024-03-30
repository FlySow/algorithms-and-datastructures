#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <bool.h>

struct node {
	int name;
	int neigh_size;
	int neighbour[];
};

struct graph {
	int node_size;
	struct node nodes[];
};

struct graph create_graph(int size, bool complete);

#endif
