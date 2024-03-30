#include <stdlib.h>
#include "stack.h"
#include <stdbool.h>


void s_push(struct stack* stack, void* value) {
	struct stack_node* node = malloc(sizeof(struct stack_node));
	node->value = value;
	node->next = stack->stack;
	stack->stack = node;
}

struct stack* s_create(int size, void* init(const int)) {
	struct stack* stack = malloc(sizeof(struct stack));
	if(size == 0) {
		stack->stack = NULL;
		return stack;
	}
	struct stack_node* node =  malloc(sizeof(struct stack_node));
	node->value = init(0);
	stack->stack = node;
	for(int i = 1; i < size; i++) {
		s_push(stack, init(i));
	}
	return stack;
}

void* s_pop(struct stack* stack) {
	if(s_empty(stack)) return NULL;
	void* value = stack->stack->value;
	struct stack_node* node = stack->stack;
	stack->stack = node->next;
	free(node);
	return value;
}

bool s_empty(struct stack* stack) {
	return stack->stack == NULL;
}

void s_free(struct stack* stack) {
	while(!s_empty(stack)) {
		void* value = s_pop(stack);
		free(value);
	}
	free(stack);
}
