#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "stack.h"
#include <stdbool.h>

struct queue {
	struct stack* inbox;
	struct stack* outbox;
};

struct queue* q_create(int size, void* init(const int));

void q_queue(struct queue* queue, void* value);

void* q_dequeue(struct queue* queue);

bool q_empty(struct queue* queue);

void q_free(struct queue* queue);

#endif
