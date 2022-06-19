#include"mat.h"
extern const char* TestMAT(int& e);
int main() 					//请扩展main()测试其他运算
{
	int e;
	const char* s;
	s = TestMAT(e);
	printf("%s\n%d", s, e);
}