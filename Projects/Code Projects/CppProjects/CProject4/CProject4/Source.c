#include <stdio.h>

void main() {
	const int arraySize = 10;
	int array1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int array2[10];

	for (int i = 0; i < arraySize; i++)
	{
		array2[i] = i;
	}

	system("pause");
}