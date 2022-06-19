#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
#include<stdio.h>
using namespace std;
template <typename T>
class MAT {
	T* const e;							//指向所有整型矩阵元素的指针
	const int r, c;							//矩阵的行r和列c大小
public:
	MAT(int r, int c);						//矩阵定义
	MAT(const MAT& a);				//深拷贝构造
	MAT(MAT&& a)noexcept;			//移动构造
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//取矩阵r行的第一个元素地址，r越界抛异常
	virtual MAT operator+(const MAT& a)const;	//矩阵加法，不能加抛异常
	virtual MAT operator-(const MAT& a)const;	//矩阵减法，不能减抛异常
	virtual MAT operator*(const MAT& a)const;	//矩阵乘法，不能乘抛异常
	virtual MAT operator~()const;					//矩阵转置
	virtual MAT& operator=(const MAT& a);		//深拷贝赋值运算
	virtual MAT& operator=(MAT&& a)noexcept;	//移动赋值运算
	virtual MAT& operator+=(const MAT& a);		//“+=”运算
	virtual MAT& operator-=(const MAT& a);		//“-=”运算
	virtual MAT& operator*=(const MAT& a);		//“*=”运算
//print输出至s并返回s：列用空格隔开，行用回车结束
	virtual char* print(char* s)const noexcept;
};
template<class Type>
MAT<Type>::MAT(int r, int c) :c(c), r(r), e(new Type[r * c])
{}
template <class Type>
MAT<Type>::MAT(const MAT& a) : c(a.c), r(a.r), e(new Type[a.r * a.c])
{
	for (int i = 0; i < r * c; i++)
	{
		e[i] = a.e[i];
	}
}
template <class Type>
MAT<Type>::MAT(MAT&& a)noexcept :c(a.c), r(a.r), e(a.e)
{
	*(int**)&a.e = NULL;
	*(int*)&(a.r) = 0;
	*(int*)&(a.c) = 0;
}
template<class Type>
MAT<Type>::~MAT()noexcept
{
	if (e != NULL)
		delete e;
	*(int**)&e = NULL;
	*(int*)&r = 0;
	*(int*)&c = 0;
}
template<class Type>
Type* const MAT<Type>::operator[](int r)
{
	if (r < 0 || r >= this->r)
	{
		throw("error!");
		return &e[0];
	}
	return e + r * c;
}
template<class Type>
MAT<Type> MAT<Type>::operator+(const MAT<Type>& a)const
{
	if (r != a.r || c != a.c)
	{
		throw("Can not add two matrices!");
		return *this;
	}
	MAT ans(a.r, a.c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			ans[i][j] = ((MAT)(*this))[i][j] + ((MAT)a)[i][j];
	return ans;
}
template<class Type>MAT<Type>
	MAT<Type>::operator-(const MAT<Type>& a)const
	{
		MAT ans(a.r, a.c);
		for (int i = 0; i < r * c; i++)
		{
			ans.e[i] = e[i] - a.e[i];
		}
		return ans;
	}
	template<class Type>
	MAT<Type> MAT<Type>::operator*(const MAT<Type>& a)const
	{
		if (c != a.r)
		{
			throw("Can not multiply two matrices!");
			return *this;
		}
		MAT ans(r, a.c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < a.c; j++)
			{
				int sum = 0;
				for (int k = 0; k < c; k++)
				{
					sum += e[k + i * c] * a.e[j + k * a.c];
				}
				ans.e[i * r + j] = sum;
			}
		}
		return ans;
	}
	template<class Type>
	MAT<Type> MAT<Type>::operator~()const
	{
		MAT m(c, r);
		for (int i = 0; i < c; i++)
		{
			for (int j = 0; j < r; j++)
			{
				int t = i * r + j;
				m.e[t] = e[t / r + (t % r) * c];
			}
		}
		return m;
	}
	template<class Type>
	MAT<Type>& MAT<Type>::operator=(const MAT<Type>& a)
	{
		if (this == &a)
		{
			return *this;
		}
		if (e != NULL)
		{
			delete(e);
		}
		*(Type**)&e = new Type[a.r * a.c];
		for (int i = 0; i < a.r * a.c; i++)
		{
			e[i] = a.e[i];
		}
		*(int*)&r = a.r;
		*(int*)&c = a.c;
		return *this;
	}
	template<class Type>
	MAT<Type>& MAT<Type>::operator=(MAT<Type>&& a)noexcept
	{
		if (this == &a)
		{
			return *this;
		}
		if (e != NULL)
		{
			delete(e);
		}
		*(Type**)&e = a.e;
		*(int*)&r = a.r;
		*(int*)&c = a.c;
		*(int**)&a.e = NULL;
		*(int*)&a.r = 0;
		*(int*)&a.c = 0;
		return *this;
	}
	template<class Type>
	MAT<Type>& MAT<Type>::operator+=(const MAT<Type>& a)
	{
		if (r != a.r || c != a.c)
		{
			throw("Can not add two matrices!");
			return *this;
		}
		for (int i = 0; i < r * c; i++)
		{
			e[i] += a.e[i];
		}
		return *this;
	}
	template<class Type>
	MAT<Type>& MAT<Type>::operator-=(const MAT<Type>& a)
	{
		if (r != a.r || c != a.c)
		{
			throw("Can not add two matrices!");
			return *this;
		}
		for (int i = 0; i < r * c; i++)
		{
			e[i] -= a.e[i];
		}
		return *this;
	}
	template<class Type>
	MAT<Type>& MAT<Type>::operator*=(const MAT<Type>& a)
	{
		if (c != a.r)
		{
			throw("Can not multiply two matrices!");
		}
		MAT<Type> temp(*this);
		temp = *this * a;
		for (int i = 0; i < r * c; i++)
			e[i] = temp.e[i];
		return *this;
	}
	template<class Type>
	char* MAT<Type>::print(char* s)const noexcept
	{
		char temp[2000];
		if (typeid(e[0]) == typeid(int))
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (j == c - 1)
					{
						sprintf(temp, "%6d\n\0", (int)e[i * c + j]);
					}
					else
					{
						sprintf(temp, "%6d \0", (int)e[i * c + j]);
					}
					strcat(s, temp);
				}
			}
		}
		else if (typeid(e[0]) == typeid(long long))
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (j == c - 1)
					{
						sprintf(temp, "%6lld\n\0", (long long)e[i * c + j]);
					}
					else
					{
						sprintf(temp, "%6lld \0", (long long)e[i * c + j]);
					}
					strcat(s, temp);
				}
			}
		}
		return s;
	}
	template MAT<int>;
	template MAT<long long>;