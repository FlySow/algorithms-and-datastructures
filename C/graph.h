#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdbool.h>
#include "linked_list.h"

struct graph_edge { 
	int neighbour;
	int weight;
};

struct graph_vertice {
	int name;
	struct linked_list* neighbours;
};

struct graph_undirected_edge {
	int n1;
	int n2;
	int weight;
};

struct graph {
	int size;
	struct graph_vertice* vertices;
	struct linked_list* undirected_edges;
};

struct graph* g_create(int size, bool complete);

void add_edge(struct graph* graph, int strt_node, int end_node, int weight, bool oriented);

void g_free(struct graph* graph);

int* depth_first_search(struct graph* graph, int strt_node);

int* breadth_first_search(struct graph* graph, int strt_node);

int* djikstra(struct graph* graph, int strt_node);

int* a_star(struct graph* graph, int strt_node, int end_node, int heuristic(const int));

struct linked_list* kruskal(struct graph* graph);

#endif
