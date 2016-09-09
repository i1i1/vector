#ifndef _INT_VECTOR_
#define _INT_VECTOR_

#define VECTOR_CAPACITY 8

typedef
struct
{
	unsigned int size;
	unsigned int capacity;
	int *data;
} vector;

void
vector_init(vector *Vector);

int 
vector_len(vector *Vector);

int
vector_getvalue(vector *Vector, int index);

int
vector_setvalue(vector *Vector, int index, int value);

void
vector_append(vector *Vector, int value);

int
vector_pop(vector *Vector);

int
compare(int a, int b);

void
vector_qsort(vector *Vector);

void
vector_free(vector *Vector);

#endif
