#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <assert.h>


#define VECTOR_INIT_CAPACITY	8
#define VECTOR_CAPACITY_GROWTH	2


struct _vector {
	char *data;
	int length;
	int capacity;
	int size;

};

#define vector_generate(type)									\
												\
	struct _vector_##type;									\
												\
	struct _vector_functions_##type {							\
		int (*push)(struct _vector_##type *, type);					\
		type (*pop)(struct _vector_##type *);						\
		type (*get)(struct _vector_##type *, int);					\
		void (*set)(struct _vector_##type *, int, type);				\
												\
	};											\
												\
	struct _vector_##type {									\
		type *data;									\
		int length;									\
		int capacity;									\
		int size;									\
		struct _vector_functions_##type functions;					\
												\
	};											\
												\
												\
	int											\
	_vector_push_##type(struct _vector_##type *a, type value)				\
	{											\
		return _vector_push((struct _vector *)a, &value);				\
	}											\
												\
	type											\
	_vector_pop_##type(struct _vector_##type *a)						\
	{											\
		return *(type *)_vector_pop((struct _vector *)a);				\
	}											\
												\
	type											\
	_vector_get_##type(struct _vector_##type *a, int idx)					\
	{											\
		return *(type *)_vector_get((struct _vector *)a, idx);				\
	}											\
												\
	void											\
	_vector_set_##type(struct _vector_##type *a, int idx,					\
							type value)				\
	{											\
		_vector_set((struct _vector *)a, idx, &value);					\
		}


#define vector_init(type, name)									\
												\
	struct _vector_##type name;								\
												\
	name.functions.push = _vector_push_##type;						\
	name.functions.pop = _vector_pop_##type;						\
	name.functions.get = _vector_get_##type;						\
	name.functions.set = _vector_set_##type;						\
												\
	name.size = sizeof(type);								\
												\
	assert(_vector_init(&name) == 0)							\


#define vector_push(a, value)		(a.functions.push(&a, value))
#define vector_pop(a)			(a.functions.pop(&a))
#define vector_get(a, idx)		(a.functions.get(&a, idx))
#define vector_set(a, idx, value)	(a.functions.set(&a, idx, value))

int	_vector_init(struct _vector *vec);
int 	_vector_push(struct _vector *vec, void *value);
void 	*_vector_pop(struct _vector *vec);
void	*_vector_get(struct _vector *vec, int idx);
void	 _vector_set(struct _vector *vec, int idx, void *value);

#endif

