#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

int
cmp(int *a, int *b)
{
	return *a - *b;
}

int
main()
{
	int *a = NULL;
	int i, sum = 0;

	for (i = 99; i >= 0; i--) {
		if (vector_push(a, i))
			return 1;
	}

	for (i = 0; i < vector_nmemb(a); i++) {
		sum += a[i];
		printf("%d:%d\t", i, a[i]);
	}

	printf("\nsum is equal to %d. total %ld elements\n", sum, vector_nmemb(a));

	qsort(a, vector_nmemb(a), sizeof(int), (void *)cmp);

	for (i = 0; i < vector_nmemb(a); i++)
		printf("%d:%d\t", i, a[i]);

	printf("\n");

	while (vector_nmemb(a))
		printf("%d\t", vector_pop(a));

	printf("\n");
	vector_free(a);

	return 0;
}

