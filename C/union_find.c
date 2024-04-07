#include <stdlib.h>
#include "union_find.h"

struct union_find* uf_create(int size) {
	int* link = calloc(size, sizeof(int));
	int* rank = calloc(size, sizeof(int));

	for(int i = 0; i < size; i++) {
		link[i] = i;
		rank[i] = 0;
	}
	struct union_find* uf = malloc(sizeof(struct union_find));
	uf->link = link;
	uf->rank = rank;
	return uf;
}

int uf_find(struct union_find* uf, int node) {
	int current = node;
	while(uf->link[current] != current) {
		current = uf->link[current];
	}
	//Compression
	uf->link[node] = current;
	return current;
}

void uf_union(struct union_find* uf, int a, int b) {
	int repr_a = uf_find(uf, a);
	int repr_b = uf_find(uf, b);
	if(repr_a != repr_b) {
		if(uf->rank[repr_a] > uf->rank[repr_b]) {
			uf->link[repr_b] = repr_a;
		} else if(uf->rank[repr_b] > uf->rank[repr_a]) {
			uf->link[repr_a] = repr_b;
		} else {
			uf->link[repr_a] = repr_b;
			uf->rank[repr_b] = uf->rank[repr_a] + 1;
		}
	}
}

void uf_free(struct union_find* uf) {
	free(uf->link);
	free(uf->rank);
	free(uf);
}

