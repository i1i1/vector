#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vector.h"

int
vector_init(vector *Vector, int size) {

	Vector->size = size;
	Vector->length = 0;
	Vector->capacity = VECTOR_CAPACITY;
	Vector->flag = 0;

	unsigned char *tmp = malloc(Vector->size * Vector->capacity);

	if (!tmp)               /* malloc returned no memory signal */
		return 1;

	Vector->data = tmp;

	return 0;
}

void
vector_initarr(vector *Vector, unsigned char *arr, int length, int size) {

        assert(arr != NULL);

        Vector->length = length;
        Vector->capacity = length - 1;
        Vector->flag = 1;
        Vector->size = size;

        Vector->data = arr;
}

int
vector_len(vector *Vector) { 

	assert(Vector != NULL);

	return Vector->length;
}

void*
vector_getarr(vector *Vector) {

	assert(Vector != NULL);

	return Vector->data;
}

void*
vector_get(vector *Vector, int index) {

	assert(Vector != NULL);
	assert(-1 < index);
	assert(index < Vector->length);

	return Vector->data + index * Vector->size;
}

void
vector_set(vector *Vector, int index, void *value) {

	assert(Vector != NULL);
	assert(0 <= index);
	assert(index < Vector->length);

	memcpy(Vector->data + index * Vector->size, value, Vector->size);
}

int
vector_push(vector *Vector, void *value) {

	assert(Vector != NULL);

	if (Vector->length == Vector->capacity) {

		if (Vector->flag)
			return 1;		/* can't reallocate given array */

		unsigned char *tmp;

		Vector->capacity *= VECTOR_CAPACITY_GROWTH;
		tmp = realloc(Vector->data, Vector->size * Vector->capacity);

		if (!tmp)
			return 1;		/* realloc returned no memory signal */

		Vector->data = tmp;

	}

	vector_set(Vector, Vector->length++, value);

	return 0;
}

void*
vector_pop(vector *Vector) {

	assert(Vector != NULL);
	assert(Vector->length != 0);

	return Vector->data + Vector->length-- * Vector->size;
}

void
vector_free(vector *Vector) {

	assert(Vector != NULL);
	assert(Vector->data != NULL);

	free(Vector->data);
}
