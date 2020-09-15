#include <stdio.h>

void main(void) {
	int i = 4;
	int j = 5;

	printf("%d", i - 1 + ++j);
	printf("%d", ++i - j--);
	printf("%d %d", i, j);

	system("pause");
}