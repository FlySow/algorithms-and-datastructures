#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>

struct stack_node {
	void* value;
	struct stack_node* next;
};

struct stack {
	struct stack_node* stack;
};

struct stack* s_create(int size, void* init(const int));

void* s_pop(struct stack* stack);

void s_push(struct stack* stack, void* value);

bool s_empty(struct stack* stack);

void s_free(struct stack* stack);

#endif
