#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"

void
vector_init(vector *Vector) {

	Vector->size = 0;
	Vector->capacity = VECTOR_CAPACITY;
	
	Vector->data = malloc(sizeof(int) * VECTOR_CAPACITY);
}

void
vector_init(vector *Vector, int *arr, int size) {

        assert(arr != NULL);

        Vector->size = size;
        Vector->capacity = size - 1;

        Vector->data = arr;
}

int
vector_len(vector *Vector) { 

        assert(*Vector != NULL);

	return Vector->size;
}

int
*vector_getarr(vector *Vector) {

	assert(*Vector != NULL);
	return Vector->data;
}

int
vector_get(vector *Vector, int index) {

	assert(*Vector != NULL);
	assert(-1 < index);
	assert(index < Vector->size);

	return Vector->data[index];
}

int
vector_set(vector *Vector, int index, int value) {

	assert(*Vector != NULL);
	assert(0 <= index);
	assert(index < Vector->size);

	Vector->data[index] = value;

	return 0;
}

void
vector_append(vector *Vector, int value) {

	assert(*Vector != NULL);

	if (Vector->size >= Vector->capacity) {
		Vector->capacity *= VECTOR_CAPACITY_GROWTH;
		Vector->data = realloc(Vector->data, sizeof(int) * Vector->capacity);
	}

	Vector->data[Vector->size++] = value;
}

int
vector_pop(vector *Vector) {

	assert(*Vector != NULL);
	assert(Vector->size != 0);

	return Vector->data[Vector->size--];
}

void
vector_free(vector *Vector) {

	assert(*Vector != NULL);
	assert(Vector->data != NULL);

	free(Vector->data);
}
