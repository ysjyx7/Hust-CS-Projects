#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
struct Queue {
    int* const  elems;	   	//elems申请内存用于存放队列的元素
    const  int  max;	  	//elems申请的最大元素个数max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
};
extern const char* TestQueue(int& s);
void initQueue(Queue* const p, int m);	//初始化p指队列：最多申请m个元素
void initQueue(Queue* const p, const Queue& s); //用s深拷贝初始化p指队列
void initQueue(Queue* const p, Queue&& s); //用s移动初始化p指队列
int  number(const Queue* const p);	//返回p指队列的实际元素个数
int  size(const Queue* const p);			//返回p指队列申请的最大元素个数max
Queue* const enter(Queue* const p, int e);  //将e入队列尾部，并返回p
Queue* const leave(Queue* const p, int& e); //从队首出元素到e，并返回p
Queue* const assign(Queue* const p, const Queue& q); //深拷贝赋s给队列并返回p
Queue* const assign(Queue* const p, Queue&& q); //移动赋s给队列并返回p
char* print(const Queue* const p, char* s);//打印p指队列至s并返回s
void destroyQueue(Queue* const p);	 //销毁p指向的队列
int main()
{
    struct Queue* const p=(struct Queue*)malloc(sizeof(struct Queue));
   // for (int i = 1; i <= 5; i++)
     //   enter(p, i);
    int s = 0;
    const char* e = TestQueue(s);
    printf("%s", e);
    printf("\n%d", s);
}
void initQueue(Queue* const p, int m)
{
    *(int**)&(p->elems) = (int*)malloc(sizeof(int) * m);
    *(int*)&(p->max) = m;
    p->head = p->tail = 0;
}
void initQueue(Queue* const p, const Queue& s)
{
    *(int**)&(p->elems) = (int*)malloc(sizeof(int) * s.max);
    *(int*)&(p->max) = s.max;
    p->head = s.head;
    p->tail = s.tail;
    int i = s.head;
   // int j = 0;
    while (i != s.tail)
    {
        (*(int**)&(p->elems))[i]= s.elems[i];
        i = (i + 1) % s.max;
    }
}
void initQueue(Queue* const p, Queue&& s)
{
    *(int**)&(p->elems) = s.elems;
    p->head = s.head;
    *(int*)&p->max = s.max;
    p->tail = s.tail;
    //free(*(int**)&(s.elems));
    *(int**)&s.elems = NULL;
    s.head = 0;
    s.tail = 0;
    *(int*)&s.max = 0;
}
int number(const Queue* const p)
{
    if (p->elems == NULL)
        return 0;
    return (p->tail - p->head+p->max)%p->max;
}
int size(const Queue* const p)
{
    return p->max;
}
Queue* const enter(Queue* const p, int e)
{
    if ((p->tail + 1) % p->max == p->head)
    {
        throw("Queue is full!");
        return p;
    }
    (*(int**)&(p->elems))[p->tail] = e;
    p->tail = (p->tail + 1) % p->max;
    return p;
}
Queue* const leave(Queue* const p, int& e)
{
    if (p->head == p->tail)
    {
        throw("Queue is empty!");
        return p;
    }
    e = p->elems[p->head];
    p->head = (p->head + 1) % p->max;
    return p;
}
Queue* const assign(Queue* const p, const Queue& q)
{
    if (p == &q)
    {
        return p;
    }
    if (p != NULL)
    {
        free(p->elems);
        *(int**)&p->elems = NULL;
        *(int**)&p->elems = (int*)malloc(sizeof(int) * q.max);
    }
    for (int i = 0; i < q.max; i++)
        (*(int**)&p->elems)[i] = q.elems[i];
    *(int*)&p->max = q.max;
    p->head = q.head;
    p->tail = q.tail;
    return p;
}
Queue* const assign(Queue* const p, Queue&& q)
{
    if (p == & q)
    {
        return p;
    }
    if (p->elems != NULL) {
        free(p->elems);
        *(int**)&p->elems = NULL;
    }
    *(int**)&p->elems = q.elems;
    *(int*)&p->max = q.max;
    p->head = q.head;
    p->tail = q.tail;
    *(int**)&q.elems = NULL;
    *(int*)&q.max = q.head = q.tail = 0;
    return p;
}
char* print(const Queue* const p, char* s)
{
    int i = p->head;
    int x = 0;
    while (i != p->tail)
    {
        x = x+sprintf(s + x, ",%d", p->elems[i]);
        i = (i + 1) % p->max;
    }
    strcpy(s, s + 1);
    return s;
}
void destroyQueue(Queue* const p)
{
    free(p->elems);
    *(int**)&p->elems = NULL;
    *(int*)&p->max = 0;
    p->head = 0;
    p->tail = 0;
}