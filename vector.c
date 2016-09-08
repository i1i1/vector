#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void
vector_init(vector *Vector) {

	Vector->size = 0;
	Vector->capacity = VECTOR_CAPACITY;

	Vector->data = malloc(sizeof(int) * VECTOR_CAPACITY)
}

int
vector_getvalue(vector *Vector, int index) {

	return *(Vector->data + index);
}

void
vector_setvalue(vector *Vector, int index, int value) {

	*(Vector->data + index) = value
}

void
vector_append(vector *Ve�tor, int value) {

	if (Vector->size < Vector->capacity) {

		*(Vector->data + Vector->size) = value;
	}
	else {

		Vector->capacity *= 2

			Vector->data = realloc(Vector->data, sizeof(int) * Vector->capacity);
	}
}

void
vector_free(vector *Vector) {

	free(Vector->data);
	free(Vector->capacity);
	free(Vector->size);
}