#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int
cmp(int *a, int *b) {
	return *a - *b;
}

int
main()
{
	vector a;
	int i, sum = 0;

	if (vector_init(&a, sizeof(int), NULL))
		return 1;

	for (i = 99; i > -1; i--)
		if (vector_push(&a, &i))
			return 1;

	for (i = 0; i < 100; i++) {
		sum += *(int *)vector_get(&a, i);
		printf("%02d:%02d\t", i, *(int*)vector_get(&a, i));

	}

	printf("\n%d\n", sum);

	int *b = vector_data(&a);

	qsort(b, vector_nmemb(&a), sizeof(int), (void *)cmp);
	for (i = 0; i < 100; i++)
		printf("%d:%d\t", i, *(int *)vector_get(&a, i));

	int arr[] = {33, 26, 65, -10, 3}, nmemb = 5;
	vector vec;
	vector_initdata(&vec, arr, nmemb, sizeof(int), NULL);
	printf("\n\n%d\n\n", vector_get(&vec, 0));

	for (i = 0; i < vector_nmemb(&vec); i++)
		printf("%d:%d\t", i, *(int*)vector_get(&vec, i));

	qsort(vector_data(&vec), vector_nmemb(&vec), sizeof(int), (void *)cmp);

	printf("\n\n");

	for (i = 0; i < nmemb; i++)
		printf("%d:%d\t", i, *(int *)vector_get(&vec, i));
	printf("\n");

	return 0;
}
