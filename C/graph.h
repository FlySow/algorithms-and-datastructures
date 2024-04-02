#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdbool.h>
#include "linked_list.h"

struct graph_vertice {
	int name;
	struct linked_list* neighbours;
};

struct graph {
	int size;
	struct graph_vertice* vertices;
};

struct graph* g_create(int size, bool complete);

void g_free(struct graph* graph);

int* depth_first_search(struct graph* graph, int strt_node);

int* breadth_first_search(struct graph* graph, int strt_node);

#endif
