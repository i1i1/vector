#ifndef _INT_VECTOR_
#define _INT_VECTOR_

#define VECTOR_CAPACITY 8
#define VECTOR_CAPACITY_GROWTH 2

typedef
struct
{
	unsigned int size;
	unsigned int capacity;
	int *data;
	int flag;       /* flag == TRUE, if data wasn't allocated */
} vector;

int
vector_init(vector *Vector);

void
vector_initarr(vector *Vector, int *arr, int len);

int 
vector_len(vector *Vector);

int*
vector_getarr(vector *Vector);

int
vector_get(vector *Vector, int index);

int
vector_set(vector *Vector, int index, int value);

int
vector_push(vector *Vector, int value);

int
vector_pop(vector *Vector);

void
vector_free(vector *Vector);

#endif
