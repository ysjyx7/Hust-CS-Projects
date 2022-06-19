#include"defstack.h"
STACK::STACK(int m):QUEUE(m),q(m)
{}
STACK::STACK(const STACK &s):QUEUE(s),q(s.q)
{}
STACK::STACK(STACK&& s)noexcept :QUEUE((QUEUE&&)s),q((QUEUE&&)s.q)
{}
int STACK::size()const noexcept
{
	return QUEUE::size()+q.size();
}
STACK::operator int()const noexcept
{
	return int(q) + QUEUE::operator int();
}
STACK& STACK::operator<<(int e)
{
	if (int(q)+1 == q.size())
	{
		throw("STACK is full!");
		return *this;
	}
	if (QUEUE::operator int()+1 == QUEUE::size())
	{
		q<<(e);
	}
	else
	{
		QUEUE::operator<<(e);
	}
	return *this;
}
STACK& STACK::operator>>(int& e)
{
	if (STACK::operator int()==0)
	{
		throw("STACK is empty!");
		return *this;
	}
	if (int(q)==0)
	{
		int num = QUEUE::operator int();
		while (num > 1)
		{
			int front;
			QUEUE::operator>>(front);
			QUEUE::operator<<(front);
			num--;
		}
		QUEUE::operator>>(e);
	}
	else if(int(q)!=0)
	{
		int num = int(q);
		while (num > 1)
		{
			int front;
			q>>(front);
			q<<(front);
			num--;
		}
		q>>(e);
	}
	return *this;
}
STACK& STACK::operator=(const STACK& s)
{
	if (this == &s)
	{
		return *this;
	}
	QUEUE::operator=(s);
	q=(s.q);
	return *this;
}
STACK& STACK::operator=(STACK&& s)noexcept
{
	if (this == &s)
	{
		return s;
	}
	QUEUE::operator=((QUEUE&&)s);
	q=((QUEUE&&)s.q);
	return *this;
}
char* STACK::print(char* b)const noexcept
{
	QUEUE::print(b);
	strcat(b, ",");
	q.print(b + strlen(b));
	return b;
}
STACK::~STACK()
{}