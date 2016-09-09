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

int
vector_len(vector *Vector) { 

	return Vector->size; 
}

int
vector_getvalue(vector *Vector, int index) {

	assert(*Vector != NULL);
	assert(0 <= index < Vector->size);

	return Vector->data[index];
}

int
vector_setvalue(vector *Vector, int index, int value) {

	assert(*Vector != NULL);
	assert(0 <= index < Vector->size);

	Vector->data[index] = value;

	return 0;
}

void
vector_append(vector *Vector, int value) {

	assert(*Vector != NULL);
	if (Vector->size >= Vector->capacity) {

		Vector->capacity *= 2;

		Vector->data = realloc(Vector->data, sizeof(int) * Vector->capacity);
	}
	
	Vector->data[Vector->size++] = value;
}

int
vector_pop(vector *Vector) {
	assert(Vector->size == 0);
	return Vector->data[Vector->size--];
}

int
compare(int a, int b) {
	if (a > b) 
    		return a;
        return b;
}

void
vector_qsort(vector *Vector) {
	assert(*Vector != NULL);
	qsort(Vector->data, Vector->size, sizeof(int), &compare);
}

void
vector_free(vector *Vector) {

	assert(*Vector != NULL);
	assert(Vector->data != NULL);

	free(Vector->data);
}
