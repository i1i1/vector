#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int
cmp(int *a, int *b) {
	return *a - *b;
}

vector_generate(int);

int
main()
{
	vector_init(int, a);
	int i, sum = 0;

	for (i = 99; i > -1; i--)
		if (vector_push(a, i))
			return 1;

	for (i = 0; i < 100; i++) {
		sum += vector_get(a, i);
		printf("%02d:%02d\t", i, vector_get(a, i));

	}

	printf("\nsum = %d\n", sum);

	int *b = vector_data(a);

	qsort(b, vector_nmemb(a), sizeof(int), (void *)cmp);

	for (i = 0; i < 100; i++)
		printf("%d:%d\t", i, vector_get(a, i));

	printf("\n");

	return 0;
}
