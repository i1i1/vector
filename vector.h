#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <assert.h>
#include <stdlib.h>


#define VECTOR_START_MAXNMEMB	8
#define VECTOR_MAXNMEMB_GROWTH	1.4

#define VECTOR_MEM_ERR	1
#define VECTOR_OK	0


#define vector_generate(type)							\
										\
	struct vector_##type {							\
		type *data;							\
		size_t nmemb;							\
		size_t  maxnmemb;						\
										\
		const struct vector_functions_##type * const func;		\
										\
	};									\
										\
	int									\
	vector_init_##type(struct vector_##type *v)				\
	{									\
		type *data;							\
		assert(v);							\
										\
		data = realloc(NULL, sizeof(type) * VECTOR_START_MAXNMEMB);	\
										\
		if (!data)							\
			return VECTOR_MEM_ERR;					\
										\
		v->nmemb = 0;							\
		v->maxnmemb = VECTOR_START_MAXNMEMB;				\
		v->data = data;							\
										\
		return VECTOR_OK;						\
	}									\
										\
	void									\
	vector_free_##type(struct vector_##type *v)				\
	{									\
		assert(v);							\
										\
		free(v->data);							\
	}									\
										\
	size_t									\
	vector_nmemb_##type(const struct vector_##type *v)			\
	{									\
		assert(v);							\
										\
		return v->nmemb;						\
	}									\
										\
	type *									\
	vector_data_##type(const struct vector_##type *v)			\
	{									\
		assert(v);							\
		assert(v->data);						\
										\
		return v->data;							\
	}									\
										\
	void									\
	vector_set_##type(struct vector_##type *v, size_t idx, type val)	\
	{									\
		assert(v);							\
		assert(v->data);						\
										\
		assert(idx < v->nmemb);						\
										\
		v->data[idx] = val;						\
	}									\
										\
	type									\
	vector_get_##type(const struct vector_##type *v, size_t idx)		\
	{									\
		assert(v);							\
		assert(v->data);						\
										\
		assert(idx < v->nmemb);						\
										\
		return v->data[idx];						\
	}									\
										\
	int									\
	vector_push_##type(struct vector_##type *v, type val)			\
	{									\
		type *data;							\
										\
		assert(v);							\
		assert(v->data);						\
										\
		if (v->nmemb == v->maxnmemb) {					\
			data =							\
			realloc(v->data, (size_t)((float)v->maxnmemb		\
						 * sizeof(type) *		\
						VECTOR_MAXNMEMB_GROWTH));	\
										\
			if (!data)						\
				return VECTOR_MEM_ERR;				\
										\
			v->data = data;						\
			v->maxnmemb = (size_t)((float)v->maxnmemb *		\
					VECTOR_MAXNMEMB_GROWTH);		\
		}								\
										\
		v->data[v->nmemb++] = val;					\
										\
		return VECTOR_OK;						\
	}									\
										\
	type									\
	vector_pop_##type(struct vector_##type *v)				\
	{									\
		assert(v);							\
		assert(v->data);						\
		assert(v->nmemb);						\
										\
		return v->data[--v->nmemb];					\
	}									\
										\
	struct vector_functions_##type {					\
		int (*push)(struct vector_##type *, type);			\
		type (*pop)(struct vector_##type *);				\
		type (*get)(const struct vector_##type *, size_t);		\
		void (*set)(struct vector_##type *, size_t, type);		\
		type *(*data)(const struct vector_##type *);			\
		void (*free)(struct vector_##type *);				\
		size_t (*nmemb)(const struct vector_##type *);			\
										\
	};									\
										\
	struct vector_functions_##type vec_func_##type = {			\
		vector_push_##type,						\
		vector_pop_##type,						\
		vector_get_##type,						\
		vector_set_##type,						\
		vector_data_##type,						\
		vector_free_##type,						\
		vector_nmemb_##type						\
	};


#define vector_init(type, name)							\
										\
	struct vector_##type name = { .func = &vec_func_##type } ;		\
										\
	assert(vector_init_##type(&name) == VECTOR_OK)


#define vector_pop(a)		a.func->pop(&a)
#define vector_push(a, val)	a.func->push(&a, val)
#define vector_get(a, idx)	a.func->get(&a, idx)
#define vector_set(a, idx, val)	a.func->set(&a, idx, val)
#define vector_data(a)		a.func->data(&a)
#define vector_free(a)		a.func->free(&a)
#define vector_nmemb(a)		a.func->nmemb(&a)


#endif

