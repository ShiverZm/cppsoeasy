#include <stdio.h>
#include <stdlib.h>


int main()
{
	char str[] = "\\\0";
	const char* pcColor = "blue1";
	char acColor[] = "blue1";

	printf("%d %d %d",
		sizeof(str),
		sizeof(pcColor),
		sizeof(acColor)
		);

	return 0;
}