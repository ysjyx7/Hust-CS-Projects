#include"mat.h"
extern const char* TestMAT(int& e);
int main() 					//����չmain()������������
{
	int e;
	const char* s;
	s = TestMAT(e);
	printf("%s\n%d", s, e);
}