#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int
main()
{
	vector a;
	int i, sum = 0;

	vector_init(&a);
	for (i = 0; i < 100; i++)
		vector_append(&a, 99 - i);

	for (i = 0; i < 100; i++) {
		sum += vector_getvalue(&a, i);
		printf("%d:%d ", i, vector_getvalue(&a, i));
	}

	printf("\n%d \n", sum);
	vector_qsort(&a);
	for (i = 0; i < 100; i++)
	    printf("%d:%d\t", i, vector_getvalue(&a, i));
	return 0;
}
