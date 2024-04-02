#include <stdlib.h>
#include "dynamic_array.h"
#include "binary_heap.h"
#include <assert.h>
#include <stdio.h>

void bh_insert(struct binary_heap* bh, void* value) {
	da_insert(bh->parents, bh->size+1, value);
	bh->size++;
	bh_percolate_up(bh, bh->size);
}

void bh_percolate_up(struct binary_heap* bh, int i) {
	assert(i <= bh->size && i > 0);
	int current = i;
	void* inserted_value = da_get(bh->parents, i);
	while(current > 1 && bh->compare(inserted_value, da_get(bh->parents, current/2)) < 0) {
		da_set(bh->parents, current, da_get(bh->parents, current/2));
		current/= 2;
	}
	da_set(bh->parents, current, inserted_value);
}					


void bh_percolate_down(struct binary_heap* bh, int i) {
	assert(i <= bh->size && i > 0);
	int current = i;
	int son = 2*i;
	while(son <= bh->size) {
		if(son < bh->size && bh->compare(da_get(bh->parents, son), da_get(bh->parents, son+1)) > 0) {
			son++;
		}
		void* son_val = da_get(bh->parents, son);
		void* current_val = da_get(bh->parents, current);
		if(bh->compare(current_val, son_val) > 0) {
			da_set(bh->parents, son, current_val);
			da_set(bh->parents, current, son_val);
			current = son;
			son = 2*current;
		}else {
			break;
		}
	}
}


struct binary_heap* bh_create(int size, int (*compare)(const void*, const void*), void* init(const int)) {
	struct dynamic_array* parents = da_create(0, NULL);
	struct binary_heap* bh = malloc(sizeof(struct binary_heap));
	bh->parents = parents;
	bh->size = 0;
	bh->compare = compare;
	da_insert(bh->parents, 0, NULL);
	for(int i = 0; i < size; i++) {
		bh_insert(bh, init(i));
	}
	return bh;
}

void* bh_extract(struct binary_heap* bh) {
	if(bh->size == 0) return NULL;
	if(bh->size == 1) {
		bh->size--;
		return da_remove(bh->parents, 1);
	}
	void* value = da_get(bh->parents, 1);
	da_set(bh->parents, 1, da_remove(bh->parents, bh->size));
	bh->size--;
	bh_percolate_down(bh, 1);
	return value;
}

void bh_free(struct binary_heap* bh) {
	da_free(bh->parents);
	free(bh);
}

bool bh_empty(struct binary_heap* bh) {
	return bh->size == 0;
}


