#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vector.h"


int
_vector_init(struct _vector *vec)
{
	assert(vec != NULL);

	char *tmp;

	vec->length = 0;
	vec->capacity = 0;

	tmp = malloc(vec->size * VECTOR_INIT_CAPACITY);

	if (tmp == NULL)
		return 1;

	vec->capacity = VECTOR_INIT_CAPACITY;
	vec->data = tmp;

	return 0;
}

int
_vector_push(struct _vector *vec, void *value)
{
	assert(vec != NULL);
	assert(vec->data != NULL);
	assert(value != NULL);


	if (vec->capacity == vec->length) {
		char *tmp;

		tmp = realloc(vec->data, vec->size * vec->capacity * VECTOR_CAPACITY_GROWTH);

		if (tmp == NULL)
			return 1;

		vec->capacity *= VECTOR_CAPACITY_GROWTH;
		vec->data = tmp;

	}

	memcpy(vec->data + vec->length * vec->size, value, vec->size);
	vec->length++;

	return 0;
}

void *
_vector_pop(struct _vector *vec)
{
	assert(vec != NULL);
	assert(vec->length != 0);

	return vec->data + --vec->length * vec->size;
}


void *
_vector_get(struct _vector *vec, int idx)
{
	assert(vec != NULL);
	assert(vec->data != NULL);
	assert(0 <= idx);
	assert(idx < vec->length);

	return vec->data + idx * vec->size;
}

void
_vector_set(struct _vector *vec, int idx, void *value)
{
	assert(vec != NULL);
	assert(vec->data != NULL);
	assert(0 <= idx);
	assert(idx < vec->length);
	assert(value != NULL);

	memcpy(vec->data + idx * vec->size, value, vec->size);
}

