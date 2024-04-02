#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "stack.h"
#include "graph.h"
#include <stdbool.h>
#include "queue.h"
#include "dynamic_array.h"
#include "binary_heap.h"

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
	printf("%d\n", *((int *)s_pop(stack)));

	s_push(stack, init(10));
	
	s_free(stack);
	
	printf("Test for queue data structure\n");
	struct queue* queue = q_create(10, init);

	q_queue(queue, init(10));
	while(!q_empty(queue)) 
		printf("%d ", *((int *) q_dequeue(queue)));
	
	printf("\n");
	q_free(queue);

	printf("Test for graph data structure\n");
	struct graph* graph = g_create(10, true);

	int* vertices = depth_first_search(graph, 0);
	
	for(int i = 0; i < graph->size; i++)
		printf("%d ", vertices[i]);
	printf("\n");
	free(vertices);

	vertices = breadth_first_search(graph, 0);
	for(int i = 0; i < graph->size; i++) 
		printf("%d ", vertices[i]);
	printf("\n");
	free(vertices);

	g_free(graph);
	
	printf("Test for dynamic array data structure\n");
	struct dynamic_array* array = da_create(10, init);
	
	printf("capacity: %d\n", array->capacity);

	da_remove(array, array->size-1);
	da_remove(array, array->size-1);
	
	printf("capacity: %d\n", array->capacity);

	da_set(array, 7, init(30));

	for(int i = 0; i < array->size; i++) {
		printf("%d ", *((int *) da_get(array, i)));
	}
	printf("\n");

	da_free(array);
	
	printf("Test for binary heap\n");
	struct binary_heap* bh = bh_create(10, compare, init);
	
	bh_insert(bh, init(30));

	for(int i = 0; i < 11; i++) {
		printf("%d ", *((int*)bh_extract(bh)));
	}
	printf("\n");

	bh_free(bh);
	

	return EXIT_SUCCESS;
}
