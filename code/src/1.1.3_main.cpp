#include <stdio.h>
#include <stdlib.h>


class A {
public:
	static void SayHello() {
		s_nNum = 1;
	}
private:
	static int s_nNum;
};
int A::s_nNum = 1;

int main1_1_3()
{
	A::SayHello();
	return 0;
}