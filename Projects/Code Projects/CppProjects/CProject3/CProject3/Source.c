#include <stdio.h>

void swap(int *p, int *q)
{
	int tempVar = *p;
	*p = *q;
	*q = tempVar;
}

void main() {
	int num1 = 3;
	int num2 = 5;

	printf("Before swap... \np/num1 = %d, and q/num2 = %d \n\n", num1, num2);
	swap(&num1, &num2);
	printf("After swap... \np/num1 = %d, and q/num2 = %d \n\n", num1, num2);

	system ("pause");
}