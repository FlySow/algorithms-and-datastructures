#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"

struct queue* q_create(int size, void* init(const int)) {
	struct queue* queue = malloc(sizeof(struct queue));
	queue->inbox = s_create(size, init);
	queue->outbox = s_create(0, NULL);
	return queue;
}

void q_queue(struct queue* queue, void* value) {
	s_push(queue->inbox, value);
}

void* q_dequeue(struct queue* queue) {
	if(!s_empty(queue->outbox)) return s_pop(queue->outbox);
	while(!s_empty(queue->inbox)) {
		s_push(queue->outbox, s_pop(queue->inbox));
	}
	return s_pop(queue->outbox);
}

bool q_empty(struct queue* queue) {
	return s_empty(queue->inbox) && s_empty(queue->outbox);
}

void q_free(struct queue* queue) {
	s_free(queue->inbox);
	s_free(queue->outbox);
	free(queue);
}
