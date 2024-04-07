#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "stack.h"
#include "graph.h"
#include <stdbool.h>
#include "queue.h"
#include "dynamic_array.h"
#include "binary_heap.h"
#include "union_find.h"

void* init(const int i) {
	int* res = malloc(sizeof(int));
	*res = i;
	return res;
}

int compare(const void* a, const void* b) {
	return *((int*)a)-*((int*)b);
}


int main(void) {
	printf("Test for linked list data structure\n");
	struct linked_list* list = ll_create(10, init);
	for(int i = 0; i < list->size-1; i++)
		printf("%d - ", *((int *)ll_get(list, i)));
	printf("%d\n", *((int *)ll_get(list, list->size-1)));

	ll_append(list, init(list->size));

	ll_put(list, 0, init(30));

	printf("%d\n", *((int *)ll_get(list, 0)));

	for(int i = list->size-1; i >= 0; i--)
		ll_remove(list, i);
	
	ll_free(list);

	printf("Test for stack data structure\n");
	struct stack* stack = s_create(10, init);
	int* s_value = s_pop(stack);
	printf("%d\n", *s_value);
	free(s_value);

	s_push(stack, init(10));
	
	s_free(stack);
	
	printf("Test for queue data structure\n");
	struct queue* queue = q_create(10, init);

	q_queue(queue, init(10));
	while(!q_empty(queue)) {
		int* q_value = (int *) q_dequeue(queue);
		printf("%d ", *q_value);
		free(q_value);
	}
	
	printf("\n");
	q_free(queue);

	printf("Test for graph data structure\n");
	struct graph* graph = g_create(10, false);
	
	add_edge(graph, 0, 1, 1, true);
	add_edge(graph, 2, 4, 4, false);
	add_edge(graph, 4, 3, 5, false);
	add_edge(graph, 5, 6, 1, true);
	add_edge(graph, 6, 7, 2, true);
	add_edge(graph, 6, 8, 3, true);
	add_edge(graph, 7, 8, 0, true);

	int* vertices = depth_first_search(graph, 5);
	
	for(int i = 0; i < graph->size; i++)
		printf("%d ", vertices[i]);
	printf("\n");
	free(vertices);

	vertices = breadth_first_search(graph, 5);
	for(int i = 0; i < graph->size; i++) 
		printf("%d ", vertices[i]);
	printf("\n");
	free(vertices);
	
	int* pred = djikstra(graph, 5);
	printf("%d\n", pred[8]);
	
	free(pred);

	add_edge(graph, 2, 4, 1, true);
	add_edge(graph, 3, 4, 1, true);
	add_edge(graph, 4, 8, 1, true);
	add_edge(graph, 2, 1, 1, true);

	struct linked_list* spanning_tree = kruskal(graph);
	for(int i = 0; i < spanning_tree->size; i++) {
		struct graph_undirected_edge* edge = ll_get(spanning_tree, i);
		printf("%d - %d\n", edge->n1, edge->n2);
	}

	ll_free(spanning_tree);

	g_free(graph);
	
	printf("Test for dynamic array data structure\n");
	struct dynamic_array* array = da_create(10, init);
	
	printf("capacity: %d\n", array->capacity);

	free(da_remove(array, array->size-1));
	free(da_remove(array, array->size-1));
	
	printf("capacity: %d\n", array->capacity);

	da_set(array, 7, init(30));

	for(int i = 0; i < array->size; i++) {
		printf("%d ", *((int *) da_get(array, i)));
	}
	printf("\n");

	da_free(array);
	
	printf("Test for binary heap\n");
	struct binary_heap* bh = bh_create(10, compare, init);
	
	bh_insert(bh, init(9));

	for(int i = 0; i < 11; i++) {
		int* bh_value = bh_extract(bh);
		printf("%d ", *bh_value);
		free(bh_value);
	}
	printf("\n");

	bh_free(bh);
	
	printf("Test for union find data structure\n");

	struct union_find* uf = uf_create(10);
	
	for(int i = 0; i < 10; i++) {
		printf("repr of %d is %d\n", i, uf_find(uf, i));
	}

	for(int i = 0; i < 10; i++) {
		uf_union(uf, 0, i);
	}

	for(int i = 0; i < 10; i++) {
		printf("repr of %d is %d\n", i, uf_find(uf, i));
	}
	
	uf_free(uf);

	return EXIT_SUCCESS;
}
