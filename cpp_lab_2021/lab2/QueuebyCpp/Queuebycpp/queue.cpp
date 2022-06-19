#include"def.h"
QUEUE::QUEUE(int m):elems(new int[m]), max(m) 
{ 
    tail = 0; 
    head = 0; 
}
QUEUE::QUEUE(const QUEUE& q) :elems(new int[q.max]), max(0)
{
    for (int i = 0; i < q.max; i++)
    {
        elems[i] = q.elems[i];
    }
    *(int*)&max = q.max;
    head = q.head;
    tail = q.tail;
}
QUEUE::QUEUE(QUEUE&& q)noexcept:elems(q.elems),max(q.max)
{
    head = q.head;
    tail = q.tail;
    q.tail = 0;
    q.head = 0;
    *(int**)&q.elems = NULL;
    *(int*)&q.max = 0;
}
QUEUE::operator int() const noexcept
{
    if (elems == NULL)
    {
        return 0;
    }
    return (tail + max - head) % max;
}
int QUEUE::size() const noexcept
{
    return max;
}
QUEUE& QUEUE::operator<<(int e)
{
    if ((tail + 1) % max == head)
    {
        throw("QUEUE is full!");
        return *this;
    }
    elems[tail] = e;
    tail = (tail + 1) % max;
    return *this;
}
QUEUE& QUEUE::operator>>(int& e)
{
    if (head == tail)
    {
        throw("QUEUE is empty!");
        return *this;
    }
    e = elems[head];
    head = (head + 1) % max;
    return *this;
}
QUEUE& QUEUE::operator=(const QUEUE& q)
{
    if (this == &q)
    {
        return *this;
    }
    if (elems != NULL)
    {
        delete[] elems;
    }
    *(int**)&elems = new int[q.max];
    for (int i = 0; i < q.max; i++)
    {
        elems[i] = q.elems[i];
    }
    *(int*)&max = q.max;
    head = q.head;
    tail = q.tail;
    return *this;
}
QUEUE& QUEUE::operator=(QUEUE&& q) noexcept
{
    if (this == &q)
    {
        return *this;
    }
    if(elems!=NULL)//判断是否为空，非空再delete
        delete[] elems;
    *(int**)&elems = q.elems;
    *(int*)&max = q.max;
    head = q.head;
    tail = q.tail;
    *(int*)&q.max = 0;
    *(int**)&q.elems = NULL;
    q.head = 0;
    q.tail = 0;
    return *this;
}
char* QUEUE::print(char* s) const noexcept
{
    int i = head;
    int j = 0;
    while (i != tail)
    {
        j += sprintf(s + j, ",%d", elems[i]);
        i = (i + 1) % max;
    }
    strcpy(s, s + 1);//将第一个逗号去除
    return s;
}
QUEUE::~QUEUE()
{
    if(elems!=NULL)
        delete[] elems;
    *(int**)&elems = NULL;
    *(int*)&max = 0;
    head = 0;
    tail = 0;
}