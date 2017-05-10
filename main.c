#include <stdio.h>

#include "vector.h"


vector_generate(float);

int
main(void)
{
	int i;

	vector_init(float, arr);
	vector_push(arr, 0);
	vector_push(arr, 1);
	vector_push(arr, 2);

	for (i = 0; i < 3; i++)
		printf("%d) %f\n", i, vector_pop(arr));

	return 0;
}

