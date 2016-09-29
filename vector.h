#ifndef _VECTOR_
#define _VECTOR_

#define VECTOR_CAPACITY 8
#define VECTOR_CAPACITY_GROWTH 2

/*
    VECTOR_CAPACITY is conctant of a begining vector size
    VECTOR_CAPACITY_GROWTH is a conctant of vector's growth rate
*/

typedef
struct
{
	unsigned int length;        /* the number of used vector units */
	unsigned int capacity;      /* the size of vector in vector units */
	unsigned int size;          /* vector unit size */
	unsigned char *data;        /* vector addres */
	int flag;                   /* flag == TRUE, if data wasn't allocated */
} vector;

int
vector_init(vector *Vector, int size);

void
vector_initarr(vector *Vector, unsigned char *arr, int length, int size);

int
vector_len(vector *Vector);

void*
vector_getarr(vector *Vector);

void*
vector_get(vector *Vector, int index);

void
vector_set(vector *Vector, int index, void *value);

int
vector_push(vector *Vector, void *value);

void*
vector_pop(vector *Vector);

void
vector_free(vector *Vector);

#endif
