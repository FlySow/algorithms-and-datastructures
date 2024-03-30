#include "linked_list.h"
#include <stdlib.h>
#include <assert.h>


struct linked_list ll_create(int size, void* init(const int)) {
	if(size <= 0) return (struct linked_list) {.size = 0, .root = NULL, .tail = NULL};
	struct linked_list_node* root = malloc(sizeof(struct linked_list));
	struct linked_list_node* tmp = root;
	for(int i = 0; i < size-1; i++) {
		tmp->value = init(i);
		tmp->next = malloc(sizeof(struct linked_list));
		tmp = tmp->next;
	}
	tmp->value = init(size-1);
	tmp->next = NULL;
	return (struct linked_list)  {.size = size, .root = root, .tail = tmp};
}

void* ll_get(struct linked_list list, int i) {
	assert(list.size > i);
	struct linked_list_node* tmp = list.root;
	for(int j = 0; j < i; j++) {
		tmp = tmp->next;
	}
	return tmp->value;
}

void ll_put(struct linked_list list, int i, void* value) {
	assert(list.size > i);
	struct linked_list_node* tmp = list.root;
	for(int j = 0; j < i; j++) {
		tmp = tmp->next;
	}
	free(tmp->value);
	tmp->value = value;
}

struct linked_list ll_append(struct linked_list list, void* value) {
	if(list.size == 0) {
		list.root = malloc(sizeof(struct linked_list_node));
		list.root->value = value;
		list.root->next = NULL;
		list.tail = list.root;
		list.size++;
		return list;
	}
	list.tail->next = malloc(sizeof(struct linked_list_node));
	list.tail->next->value = value;
	list.tail->next->next = NULL;
	list.tail = list.tail->next;
	list.size++;
	return list;
}
	
struct linked_list ll_remove(struct linked_list list, int i) {
	assert(list.size > i);
	list.size--;
	if(i == 0) {
		free(list.root->value);
		struct linked_list_node* next = list.root->next;
		free(list.root);
		list.root = next;
		return list;
	}
	struct linked_list_node* tmp = list.root;
	for(int j = 0; j < i-1; j++) {
		tmp = tmp->next;
	}
	free(tmp->next->value);
	struct linked_list_node* next = tmp->next->next;
	free(tmp->next);
	tmp->next = next;
	if(i == list.size) list.tail = tmp;
	return list;
}

void ll_free(struct linked_list list) {
	struct linked_list_node* tmp = list.root;
	for(int i = 0; i < list.size; i++) {
		free(tmp->value);
		struct linked_list_node* tmp_ = tmp->next;
		free(tmp);
		tmp = tmp_;
	}
}
