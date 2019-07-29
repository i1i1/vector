#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define VECTOR_MAXNMEMB_START	8
#define VECTOR_CANARY_BEG	0x02BADA55
#define VECTOR_CANARY_END	0x2BADA550


typedef uint32_t canary;

struct vector {
	size_t nmemb;
	size_t max_nmemb;
	canary canary_beg;
};


#define _vector_get_vector(a)		((struct vector *)a - 1)
#define _vector_get_nmemb(a)		(_vector_get_vector(a)->nmemb)
#define _vector_get_max_nmemb(a)	(_vector_get_vector(a)->max_nmemb)
#define _vector_get_canary_beg(a, sz)	(_vector_get_vector(a)->canary_beg)
#define _vector_get_canary_end(a, sz)	(*(canary *)((uint8_t *)(a) + sz * _vector_get_max_nmemb(a)))
#define _vector_is_canaries_ok(a)					\
	((_vector_get_canary_beg(a, sizeof(*a)) == VECTOR_CANARY_BEG &&	\
	  _vector_get_canary_end(a, sizeof(*a)) == VECTOR_CANARY_END))
#define _vector_assert_canaries(a)					\
	(assert((a) && "Points to null"),				\
	 assert(_vector_get_canary_beg(a, sizeof(*a)) == VECTOR_CANARY_BEG && \
		"Canary at the beginning died :("),			\
	 assert(_vector_get_canary_end(a, sizeof(*a)) == VECTOR_CANARY_END && \
		"Canary at the end died :("))

#define _vector_push(a, val)		((a)[_vector_get_nmemb(a)++] = (val))
#define _vector_pop(a)			((a)[--_vector_get_nmemb(a)])
#define _vector_need_grow(a)		(_vector_get_nmemb(a) == _vector_get_max_nmemb(a))
#define _vector_grow(a)			(__vector_grow((void **)(a), sizeof(**a)))
#define _vector_init(a)			_vector_grow(a)


/*
 * Can be used for documentation purposes.
 */
#define vector_of(elem)	elem *

#define vector_decl(elem, nm)	vector_of(elem) nm = NULL;

#define vector_nmemb(a)		((*(a)) ? (_vector_assert_canaries(*(a)), \
					   _vector_get_nmemb(*(a))) : 0)

#define vector_pop(a)		(_vector_assert_canaries(*(a)),		\
				 assert(_vector_get_nmemb(*(a)) > 0),	\
				 _vector_pop(*(a)))

#define vector_free(a)		((*(a) ? (_vector_assert_canaries(*(a)), \
					   free(_vector_get_vector(*(a))), \
					   *(a) = NULL) : 0))

#define vector_push(a, val)	(*(a) ? ((_vector_need_grow(*(a)) ?		\
					  _vector_grow(a) : 0) ?		\
					 1 : (_vector_push(*(a), val), 0))	\
				 : (_vector_init(a) ? 1				\
				    : (_vector_push(*(a), val), 0)))


int __vector_grow(void **pp, int sz);


#ifdef VECTOR_IMPLEMENTATION

int
__vector_grow(void **pp, int sz)
{
	void *p = *pp;
	struct vector *v;
	size_t nmax;

	if (!p) {
		p = malloc(sizeof(struct vector) + sz * VECTOR_MAXNMEMB_START + sizeof(canary));

		if (!p)
			return 1;

		v = p;
		v->nmemb = 0;
		v->max_nmemb = VECTOR_MAXNMEMB_START;
		_vector_get_canary_beg(v + 1, sz) = VECTOR_CANARY_BEG;
		_vector_get_canary_end(v + 1, sz) = VECTOR_CANARY_END;
		*pp = (struct vector *)p + 1;

		return 0;
	}

	nmax = _vector_get_max_nmemb(p) << 1;
	p = realloc(_vector_get_vector(p), sizeof(struct vector) + sz * nmax + sizeof(canary));

	if (!p)
		return 1;

	v = p;
	v->max_nmemb = nmax;
	_vector_get_canary_end(v + 1, sz) = VECTOR_CANARY_END;

	*pp = (struct vector *)p + 1;

	return 0;
}

#endif /* VECTOR_IMPLEMENTATION */


#endif /* _VECTOR_H_ */

