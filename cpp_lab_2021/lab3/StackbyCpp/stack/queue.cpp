#include"defstack.h"
QUEUE::QUEUE(int m) :elems(new int[m]), max(m)//初始化队列，最多申请m个元素
{
    tail = 0;
    head = 0;
}
QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]), max(0)//用q深拷贝构造队列
{
    for (int i = 0; i < q.max; i++)
    {
        elems[i] = q.elems[i];
    }
    *(int*)&max = q.max;
    head = q.head;
    tail = q.tail;
}
QUEUE::QUEUE(QUEUE&& q)noexcept :elems(q.elems), max(q.max)//用q移动初始化队列
{
    head = q.head;
    tail = q.tail;
    q.tail = 0;
    q.head = 0;
    *(int**)&q.elems = NULL;
    *(int*)&q.max = 0;
}
QUEUE::operator int() const noexcept//获取队列中元素个数
{
    return tail-head<0?tail-head+max:tail-head;
}
int QUEUE::size() const noexcept//获取队列中能存放的最大数量
{
    return max;
}
QUEUE& QUEUE::operator<<(int e)//入队
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
QUEUE& QUEUE::operator>>(int& e)//出队
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
    if (elems != NULL)//防止反复析构
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
    if (elems != NULL)//判断是否为空，非空再delete
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
        i = (i + 1) % this->max;
    }
    strcpy(s, s + 1);//将第一个逗号去除
    return s;
}
QUEUE::~QUEUE()
{
    if (elems != NULL)
        delete[] elems;
    *(int**)&elems = NULL;
    *(int*)&max = 0;
    head = 0;
    tail = 0;
}