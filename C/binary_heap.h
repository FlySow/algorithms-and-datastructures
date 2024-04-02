#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_

#include "dynamic_array.h"

struct binary_heap {
	struct dynamic_array* parents;
	int (*compare)(const void*, const void*);
	int size;
};

struct binary_heap* bh_create(int size, int (*compare)(const void*, const void*), void* init(const int));

void bh_percolate_up(struct binary_heap* bh, int i);


void bh_percolate_down(struct binary_heap* bh, int i);

void* bh_extract(struct binary_heap* bh);

void bh_insert(struct binary_heap* bh, void* value);

void bh_free(struct binary_heap* bh);


#endif
