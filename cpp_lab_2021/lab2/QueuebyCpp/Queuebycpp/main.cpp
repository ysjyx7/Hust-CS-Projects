#include"def.h"
extern const char* TestQUEUE(int& s);
int main()
{
	QUEUE q(100);
	int e;
	const char* s= TestQUEUE(e);
	std::cout << s << std::endl;
	std::cout << e;
}
