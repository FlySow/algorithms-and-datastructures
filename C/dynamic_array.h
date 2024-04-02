#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

struct dynamic_array {
	void** array;
	int capacity;
	int size;
};

struct dynamic_array* da_create(int size, void* init(const int));

void da_insert(struct dynamic_array* array, int i, void* value);

void* da_remove(struct dynamic_array* array, int i);

void* da_get(struct dynamic_array* array, int i);

void da_set(struct dynamic_array* array, int i, void* value);

void da_free(struct dynamic_array* array);

#endif
