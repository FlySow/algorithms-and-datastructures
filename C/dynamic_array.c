#include <stdlib.h>
#include "dynamic_array.h"
#include <assert.h>

void da_insert(struct dynamic_array* array, int i, void* value) {
	assert(i <= array->size);
	void** new_array = array->array;
	if(array->size == array->capacity) {
		if(array->capacity == 0) new_array = malloc(sizeof(void*));
		else new_array = calloc(array->capacity*2, sizeof(void*));
	}
	for(int j = 0; j < i; j++) {
		new_array[j] = array->array[j];
	}
	for(int j = i+1; j < array->size; j++) {
			new_array[j] = array->array[j-1];
	}
	new_array[i] = value;
	if(array->size == array->capacity) {
		if(array->capacity == 0) array->capacity = 1;
		else array->capacity*= 2;
		free(array->array);
		array->array = new_array;
	}
	array->size++;
}

struct dynamic_array* da_create(int size, void* init(const int)) {
	struct dynamic_array* array = malloc(sizeof(struct dynamic_array));
	array->array = NULL;
	array->capacity = 0;
	array->size = 0;
	for(int i = 0; i < size; i++) {
		da_insert(array, i, init(i));
	}
	return array;
}

void* da_remove(struct dynamic_array* array, int i) {
	assert(i < array->size);
	void** new_array = array->array;
	if(array->size-1 <= array->capacity/2) {
		new_array = calloc(array->capacity/2, sizeof(void*));
	}
	for(int j = 0; j < i; j++) {
		new_array[j] = array->array[j];
	}
	for(int j = i; j < array->size-1; j++){
		new_array[j] = array->array[j+1];
	}
	void* res = array->array[i];
	if(array->size-1 == array->capacity/2) {
		array->capacity/= 2;
		free(array->array);
		array->array = new_array;
	}
	array->size--;
	return res;
}

void* da_get(struct dynamic_array* array, int i) {
	assert(i < array->size);
	return array->array[i];
}

void da_set(struct dynamic_array* array, int i, void* value) {
	assert(i < array->size);
	array->array[i] = value;
}

void da_free(struct dynamic_array* array) {
	for(int i = 0; i < array->size; i++) {
		free(array->array[i]);
	}
	free(array->array);
	free(array);
}






