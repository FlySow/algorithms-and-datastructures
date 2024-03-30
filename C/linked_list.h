#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

struct linked_list_node {
	void* value;
	struct linked_list_node* next;
};

struct linked_list {
	int size;
	struct linked_list_node* root;
	struct linked_list_node* tail;
};

struct linked_list* ll_create(int size, void* init (const int));

void* ll_get(struct linked_list* list, int i);

void ll_put(struct linked_list* list, int i, void* value);

void ll_append(struct linked_list* list, void* value);

void ll_remove(struct linked_list* list, int i);

void ll_free(struct linked_list* list);

#endif
