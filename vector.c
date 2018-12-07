#include <stdlib.h>
#include "vector.h"

int
_vector_grow(void **pp, int sz)
{
	void *p = *pp;
	size_t nmax;

	if (!p) {
		p = VECTOR_MALLOC(sizeof(size_t) * 2 + sz * VECTOR_MAXNMEMB_START);

		if (!p)
			return 1;

		p = (size_t *)p + 2;
		_vector_nmemb(p) = 0;
		_vector_maxnmemb(p) = VECTOR_MAXNMEMB_START;

		*pp = p;

		return 0;
	}

	nmax = (float)(_vector_maxnmemb(p) * VECTOR_MAXNMEMB_GROWTH);
	p = VECTOR_REALLOC(_vector_raw(p), sizeof(size_t) * 2 + sz * nmax);

	if (!p)
		return 1;

	p = (size_t *)p + 2;
	_vector_maxnmemb(p) = nmax;

	*pp = p;

	return 0;
}

