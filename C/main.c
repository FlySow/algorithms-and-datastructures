#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


void* init(const int i) {
	int* res = malloc(sizeof(int));
	*res = i;
	return res;
}


int main(void) {
	struct linked_list list = ll_create(10, init);
	for(int i = 0; i < list.size-1; i++)
		printf("%d - ", *((int *)ll_get(list, i)));
	printf("%d\n", *((int *)ll_get(list, list.size-1)));

	list = ll_append(list, init(list.size));

	ll_put(list, 0, init(30));

	printf("%d\n", *((int *)ll_get(list, 0)));

	for(int i = list.size-1; i >= 0; i--)
		list = ll_remove(list, i);
	
	ll_free(list);
	return EXIT_SUCCESS;
}
