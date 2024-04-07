#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_

struct union_find {
	int* link;
	int* rank;
};

struct union_find* uf_create(int size);

int uf_find(struct union_find* uf, int node);

void uf_union(struct union_find* uf, int a, int b);

void uf_free(struct union_find* uf);

#endif
