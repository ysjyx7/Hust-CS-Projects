#include"defstack.h"
extern const char* TestSTACK(int& e);
int main()
{
	STACK s(10);
	int e;
	const char* ss = TestSTACK(e);
	std::cout << ss << std::endl;
	std::cout << e;
}