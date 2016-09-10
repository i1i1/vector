#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int
compare(int a, int b) {
	if (a > b)
		return a;
	return b;
}

int
main()
{
	vector a;
	int i, sum = 0;

	vector_init(&a);
	for (i = 0; i < 100; i++)
		vector_append(&a, 99 - i);

	for (i = 0; i < 100; i++) {
		sum += vector_get(&a, i);
		printf("%d:%d\t", i, vector_get(&a, i));
	}

	printf("\n%d \n", sum);
	int *b = vector_getarr(&a);
	qsort(b, vector_len(&a), sizeof(int), &compare);
	for (i = 0; i < 100; i++)
	    printf("%d:%d\t", i, vector_get(&a, i));
	return 0;
}
