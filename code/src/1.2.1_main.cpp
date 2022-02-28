#include <stdio.h>


int main1_2_1() {
	int i;
	int a[5] = { 0 };
	for (i = 0; i <= 30; i++) {
		a[i] = 0;
		printf("a[%d]:%d\n", i, a[i]);
	}
	return 0;
}