#include <stdio.h>
#include <stdlib.h>

#define S (60 * 60 * 24 * 365UL)
#define Seconds_Of_Year(year) {  (((( (year % 4==0) && (year % 100 != 0 )) || (year % 400==0)) ? 1 : 0 )+365) * 24 * 3600 }

void main5_16_1(){
	long second = S;
	printf("A Year Seconds :%d\n", second);
	system("pause");
}