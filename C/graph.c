#include "graph.h"
#include <stdlib.h>
#include "linked_list.h"
#include "stack.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "binary_heap.h"
#include <limits.h>
#include "union_find.h"

void* id(const int i) {
	struct graph_edge* res = malloc(sizeof(struct graph_edge));
	res->neighbour = i;
	res->weight = 1;
	return res;
}

struct vertex_dist { 
	int vertex;
	int dist;
};

int compare_vertex_dist(const void* a, const void* b) {
	return ((struct vertex_dist*)a)->dist-((struct vertex_dist*)b)->dist;
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
	graph->undirected_edges = ll_create(0, NULL);
	return graph;
}

void add_edge(struct graph* graph, int strt_node, int end_node, int weight, bool oriented) {
	assert(end_node < graph->size && strt_node < graph->size);
	struct graph_edge* edge = malloc(sizeof(struct graph_edge));
	edge->neighbour = end_node;
	edge->weight = weight;
	ll_append(graph->vertices[strt_node].neighbours, edge);
	if(oriented) {
		edge = malloc(sizeof(struct graph_edge));
		edge->neighbour = strt_node;
		edge->weight = weight;
		ll_append(graph->vertices[end_node].neighbours, edge);
		
		struct graph_undirected_edge* uedge = malloc(sizeof(struct graph_undirected_edge));
		
		uedge->n1 = strt_node;
		uedge->n2 = end_node;
		uedge->weight = weight;
		ll_append(graph->undirected_edges, uedge);
	}
}


void g_free(struct graph* graph) {
	for(int i = 0; i < graph->size; i++) {
		ll_free(graph->vertices[i].neighbours);
	}
	free(graph->vertices);
	//ll_free(graph->undirected_edges);
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
		int vertice = ((struct graph_edge *)s_pop(vertices))->neighbour;
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
		int vertice = ((struct graph_edge *)q_dequeue(vertices))->neighbour;
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


int* djikstra(struct graph* graph, int strt_node) {
	assert(strt_node < graph->size);
	struct binary_heap* priority_queue = bh_create(0, compare_vertex_dist, NULL);
	int* dist = calloc(graph->size, sizeof(int));
	for(int i = 0; i < graph->size; i++) 
		dist[i] = INT_MAX;
	dist[strt_node] = 0;

	int* pred = calloc(graph->size, sizeof(int));
	memset(pred, -1, graph->size);
	pred[strt_node] = strt_node;

	//Allocate the first couple vertex dist with the origin and dist being strt_node and 0
	struct vertex_dist* source = malloc(sizeof(struct vertex_dist));
	source->dist = 0;
	source->vertex = strt_node;
	
	bh_insert(priority_queue, source);
	while(!bh_empty(priority_queue)) {
		//Retrieve the couple vertex, dist with the smallest distance from strt_node
		struct vertex_dist* min_vertex_dist = bh_extract(priority_queue);
		//Retrieve the vertex from the said couple
		int min_vertex = min_vertex_dist->vertex;
		
		//Get all the neighbours from the min_vertex
		struct linked_list* neighbours = graph->vertices[min_vertex].neighbours;
		
		for(int i = 0; i < neighbours->size; i++) {
			//Retrieve the edge between min_vertex and one of his neighbours
			struct graph_edge* edge  = (struct graph_edge*) ll_get(neighbours, i);
			//Retrieve the neighbours and weight
			int neighbour = edge->neighbour;
			int weight = edge->weight;
			
			//Check the distance
			if(dist[neighbour] > dist[min_vertex] + weight) {
				dist[neighbour] = dist[min_vertex] + weight;
				pred[neighbour] = min_vertex;

				//Allocate new couple vertex dist to put it in the priority queue (will be freed)
				struct vertex_dist* vd = malloc(sizeof(struct vertex_dist));
				vd->vertex = neighbour;
				vd->dist = dist[neighbour];

				bh_insert(priority_queue, vd);


			}
		}
		free(min_vertex_dist);
	}
	bh_free(priority_queue);
	free(dist);
	return pred;
}

int* a_star(struct graph* graph, int strt_node, int end_node, int heuristic(const int)) {
	assert(strt_node < graph->size);
	struct binary_heap* priority_queue = bh_create(0, compare_vertex_dist, NULL);
	int* dist = calloc(graph->size, sizeof(int));
	for(int i = 0; i < graph->size; i++) 
		dist[i] = INT_MAX;
	dist[strt_node] = 0;

	int* pred = calloc(graph->size, sizeof(int));
	memset(pred, -1, graph->size);
	pred[strt_node] = strt_node;

	int current = strt_node;
	int value = heuristic(strt_node);
	
	while(current != end_node) {
		//Get all the neighbours from the current node
		struct linked_list* neighbours = graph->vertices[current].neighbours;
		
		dist[current] = value - heuristic(current);

		for(int i = 0; i < neighbours->size; i++) {
			//Retrieve the edge between min_vertex and one of his neighbours
			struct graph_edge* edge  = (struct graph_edge*) ll_get(neighbours, i);
			//Retrieve the neighbours and weight
			int neighbour = edge->neighbour;
			int weight = edge->weight;

			int d = heuristic(neighbour) + dist[current] + weight;
			
			//Check the distance
			if(dist[neighbour] > dist[current] + weight) {
				pred[neighbour] = current;

				//Allocate new couple vertex dist to put it in the priority queue (will be freed)
				struct vertex_dist* vd = malloc(sizeof(struct vertex_dist));
				vd->vertex = neighbour;
				vd->dist = d;

				bh_insert(priority_queue, vd);
			}
		}
		//Retrieve the couple vertex, dist with the smallest distance from strt_node
		struct vertex_dist* min_vertex_dist = bh_extract(priority_queue);
		//Retrieve the vertex from the said couple
		current = min_vertex_dist->vertex;
		value = min_vertex_dist->dist;

		free(min_vertex_dist);
	}
	bh_free(priority_queue);
	free(dist);
	return pred;
}

int compare_undirected(const void* a, const void* b) {
	return ((struct graph_undirected_edge*)a)->weight - ((struct graph_undirected_edge*)b)->weight;
}


// /!\ be very careful, this algorithm requires ALL vertices to be connected by undirected edges
// if they're not connected by such manners, the algorithm could loop indefinitely
struct linked_list* kruskal(struct graph* graph) {
	struct union_find* uf =  uf_create(graph->size);
	struct linked_list* result_tree = ll_create(0, NULL);
	struct binary_heap* priority_queue = bh_create(0, compare_undirected, NULL);

	struct linked_list* uedges = graph->undirected_edges;
	for(int i = 0; i < uedges->size; i++) {
		bh_insert(priority_queue, ll_get(uedges, i));
	}

	while(result_tree->size < graph->size-1) {
		struct graph_undirected_edge* min = bh_extract(priority_queue);
		
		if(uf_find(uf, min->n1) != uf_find(uf, min->n2)) {
			uf_union(uf, min->n2, min->n1);
			ll_append(result_tree, min);
		}

	}

	uf_free(uf);
	bh_free(priority_queue);
	return result_tree;
}
