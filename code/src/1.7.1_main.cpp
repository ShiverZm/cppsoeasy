#include <stdio.h>
#include <stdlib.h>

#define N 3 
#define SCORE(n) (2*((N+1)*n))

int main() {
	int n = SCORE(5 + 1);
	printf("%d\n", n);
	system("pause");
	return 0;
}