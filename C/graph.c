#include "graph.h"
#include <stdlib.h>
#include "linked_list.h"
#include "stack.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

void* id(const int i) {
	int* res = malloc(sizeof(int));
	*res = i;
	return res;
}

struct graph* g_create(int size, bool complete) {
	struct graph_vertice* vertices = calloc(size, sizeof(struct graph_vertice));
	for(int i = 0; i < size; i++) {
		vertices[i].name = i;
		if(complete)
			vertices[i].neighbours = ll_create(size, id);
		else
			vertices[i].neighbours = ll_create(0, NULL);

	}
	struct graph* graph = malloc(sizeof(struct graph));
	graph->vertices = vertices;
	graph->size = size;
	return graph;
}

void g_free(struct graph* graph) {
	for(int i = 0; i < graph->size; i++) {
		ll_free(graph->vertices[i].neighbours);
	}
	free(graph->vertices);
	free(graph);
}

int* depth_first_search(struct graph* graph, int strt_node) {
	assert(strt_node < graph->size);
	struct stack* vertices = s_create(0, NULL);
	bool* explored_vertices = calloc(graph->size, sizeof(bool));
	memset(explored_vertices, false, graph->size);
	s_push(vertices, &strt_node);
	int* res = calloc(graph->size, sizeof(int));
	int acc = 0;
	while(!s_empty(vertices)) {
		int vertice = *((int *)s_pop(vertices));
		if(!explored_vertices[vertice]) {
			res[acc] = vertice;
			acc++;
			explored_vertices[vertice] = true;
			struct linked_list* neighbours = graph->vertices[vertice].neighbours;
			for(int i = 0; i < neighbours->size; i++) {
				s_push(vertices, ll_get(neighbours, i));
			}
		}
	}
	for(int i = acc; i < graph->size; i++) {
		res[i] = -1;
	}
	s_free(vertices);
	free(explored_vertices);
	return res;
}

int* breadth_first_search(struct graph* graph, int strt_node) {
	assert(strt_node < graph->size);
	struct queue* vertices = q_create(0, NULL);
	bool* explored_vertices = calloc(graph->size, sizeof(bool));
	memset(explored_vertices, false, graph->size);
	q_queue(vertices, &strt_node);
	int* res = calloc(graph->size, sizeof(int));
	int acc = 0;
	while(!q_empty(vertices)) {
		int vertice = *((int *)q_dequeue(vertices));
		if(!explored_vertices[vertice]) {
			res[acc] = vertice;
			acc++;
			explored_vertices[vertice] = true;
			struct linked_list* neighbours = graph->vertices[vertice].neighbours;
			for(int i = 0; i < neighbours->size; i++) {
				q_queue(vertices, ll_get(neighbours, i));
			}
		}
	}
	for(int i = acc; i < graph->size; i++) {
		res[i] = -1;
	}
	q_free(vertices);
	free(explored_vertices);
	return res;
}


