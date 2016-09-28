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

	vector_init(&a, sizeof(int));

	for (i = 0; i < 100; i++)
		vector_push(&a, &i);

	for (i = 0; i < 100; i++) {
		sum += *(int*)vector_get(&a, i);
		printf("%d:%d\t", i, *(int*)vector_get(&a, i));
	}

	printf("\n%d \n", sum);
	int *b = vector_getarr(&a);
	qsort(b, vector_len(&a), sizeof(int), &compare);
	for (i = 0; i < 100; i++)
		printf("%d:%d\t", i, *(int*)vector_get(&a, i));
	int arr[] = {33, 26, 65, -10, 3}, len = 5;
	vector vec;
	vector_initarr(&vec, arr, len, sizeof(int));
	vector_get(&vec, 0);
	printf("\n\n");
	for (i = 0; i < vector_len(&vec); i++)
		printf("%d:%d\t", i, *(int*)vector_get(&vec, i));
	qsort(vector_getarr(&vec), vector_len(&vec), sizeof(int), &compare);
	printf("\n\n");
	for (i = 0; i < len; i++)
		printf("%d:%d\t", i, *(int*)vector_get(&vec, i));
	printf("\n");
	return 0;
}
