#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include <assert.h>

#define VECTOR_MAXNMEMB_START	8
#define VECTOR_MAXNMEMB_GROWTH	1.4

#define VECTOR_REALLOC(ptr, size)	realloc(ptr, size)
#define VECTOR_FREE(ptr)			VECTOR_REALLOC(ptr, 0)
#define VECTOR_MALLOC(size)			VECTOR_REALLOC(NULL, size)

#define vector_nmemb(a)		((const size_t)_vector_raw(a)[0])

#define _vector_raw(a)		((size_t *)(a) - 2)
#define _vector_nmemb(a)	(_vector_raw(a)[0])
#define _vector_maxnmemb(a)	(_vector_raw(a)[1])

#define vector_push(a, val)	(((a) && !_vector_needgrow(a, 1)) ? \
								(_vector_hardpush(a, val), 0) : \
									(_vector_grow((void *)&(a), sizeof(*(a))) ? 1 : \
										(_vector_hardpush(a, val), 0)))
#define vector_pop(a)		(assert(vector_nmemb(a)), (a)[_vector_nmemb(a)--])
#define vector_free(a)		((a) ? VECTOR_FREE(_vector_raw(a)) : 0)

#define _vector_hardpush(a, val) ((a)[_vector_nmemb(a)++] = val)
#define _vector_needgrow(a, n)	((_vector_nmemb(a) + n) > _vector_maxnmemb(a))

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

#endif /* _VECTOR_H_ */

