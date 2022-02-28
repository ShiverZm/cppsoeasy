#include <stdio.h>
#include <stdlib.h>


class A {
public:
	A() {
		printf("A()\n");
	};
	virtual ~A() {
		printf("~A()\n");
	};
};

class B :public A {
public:
	B() {
		printf("B()\n");
	}
	~B() {
		printf("~B()\n");
	}
};

int main1_5_4()
{
	A* pA = new B;
	delete pA;
	system("pause");
	return 0;
}