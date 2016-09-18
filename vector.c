#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"

int
vector_init(vector *Vector) {

	Vector->size = 0;
	Vector->capacity = VECTOR_CAPACITY;
	Vector->flag = 0;

	int tmp = malloc(sizeof(int) * VECTOR_CAPACITY);

	if (!tmp)
		return 1;

	return Vector->data = tmp;
}

void
vector_initarr(vector *Vector, int *arr, int size) {

        assert(arr != NULL);

        Vector->size = size;
        Vector->capacity = size - 1;
        Vector->flag = 1;

        Vector->data = arr;
}

int
vector_len(vector *Vector) { 

    assert(Vector != NULL);

	return Vector->size;
}

int*
vector_getarr(vector *Vector) {

	assert(Vector != NULL);
	return Vector->data;
}

int
vector_get(vector *Vector, int index) {

	assert(Vector != NULL);
	assert(-1 < index);
	assert(index < Vector->size);

	return Vector->data[index];
}

int
vector_set(vector *Vector, int index, int value) {

	assert(Vector != NULL);
	assert(0 <= index);
	assert(index < Vector->size);

	Vector->data[index] = value;
}

int
vector_push(vector *Vector, int value) {

	assert(Vector != NULL);

	int tmp;

	if (Vector->size >= Vector->capacity) {

		if (Vector->flag)
			return 1;

		Vector->capacity *= VECTOR_CAPACITY_GROWTH;
		tmp = realloc(Vector->data, sizeof(int) * Vector->capacity);

		if (!tmp)
			return 1;

		Vector->data = tmp;

	}

	Vector->data[Vector->size++] = value;

	return 0;


}

int
vector_pop(vector *Vector) {

	assert(Vector != NULL);
	assert(Vector->size != 0);

	return Vector->data[Vector->size--];
}

void
vector_free(vector *Vector) {

	assert(Vector != NULL);
	assert(Vector->data != NULL);

	free(Vector->data);
}

