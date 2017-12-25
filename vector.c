#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "vector.h"


int
vector_init(vector *v, size_t size, void *(*real)(void *, size_t))
{
	void *data;

	assert(v);
	assert(size);

	if (!real)
		real = realloc;

	data = real(NULL, size * VECTOR_START_MAXNMEMB);

	if (!data)
		return VECTOR_MEM_ERR;

	v->nmemb = 0;
	v->maxnmemb = VECTOR_START_MAXNMEMB;
	v->size = size;
	v->data = data;
	v->realloc = real;

	return VECTOR_OK;
}

void
vector_free(vector *v)
{
	assert(v);

	v->realloc(v->data, 0);
}

void
vector_initdata(vector *v, void *arr, size_t nmemb, size_t size,
		void *(*real)(void *, size_t))
{
	assert(v);
	assert(arr);
	assert(nmemb);
	assert(size);

	if (!(real))
		real = realloc;

	v->nmemb = nmemb;
	v->maxnmemb = nmemb;
	v->size = size;
	v->realloc = realloc;
}

int
vector_nmemb(const vector *v)
{
	assert(v);

	return v->nmemb;
}

void *
vector_data(const vector *v)
{
	assert(v);
	assert(v->data);

	return v->data;
}

void
vector_set(vector *v, size_t idx, const void *val)
{
	assert(v);
	assert(v->data);
	assert(val);

	assert(idx < v->nmemb);

	memcpy((void *)((char *)v->data + idx * v->size), val, v->size);
}

void *
vector_get(const vector *v, size_t idx)
{
	assert(v);
	assert(v->data);

	assert(idx < v->nmemb);

	return (void *)((const char *)v->data + idx * v->size);
}

int
vector_push(vector *v, const void *val)
{
	void *data;

	assert(v);
	assert(v->data);
	assert(val);

	if (v->nmemb == v->maxnmemb) {
		data = v->realloc(v->data,
				(size_t)((float)v->maxnmemb * v->size * VECTOR_MAXNMEMB_GROWTH));

		if (!data)
			return VECTOR_MEM_ERR;

		v->data = data;
		v->maxnmemb = (size_t)((float)v->maxnmemb * VECTOR_MAXNMEMB_GROWTH);
	}

	v->nmemb++;
	vector_set(v, v->nmemb - 1, val);

	return VECTOR_OK;
}

void *
vector_pop(vector *v)
{
	void *res;

	assert(v);
	assert(v->nmemb);

	res = vector_get(v, v->nmemb - 1);
	v->nmemb--;

	return res;
}

