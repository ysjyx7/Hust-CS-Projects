#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
struct Queue {
    int* const  elems;	   	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	  	//elems��������Ԫ�ظ���max
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
};
extern const char* TestQueue(int& s);
void initQueue(Queue* const p, int m);	//��ʼ��pָ���У��������m��Ԫ��
void initQueue(Queue* const p, const Queue& s); //��s�����ʼ��pָ����
void initQueue(Queue* const p, Queue&& s); //��s�ƶ���ʼ��pָ����
int  number(const Queue* const p);	//����pָ���е�ʵ��Ԫ�ظ���
int  size(const Queue* const p);			//����pָ������������Ԫ�ظ���max
Queue* const enter(Queue* const p, int e);  //��e�����β����������p
Queue* const leave(Queue* const p, int& e); //�Ӷ��׳�Ԫ�ص�e��������p
Queue* const assign(Queue* const p, const Queue& q); //�����s�����в�����p
Queue* const assign(Queue* const p, Queue&& q); //�ƶ���s�����в�����p
char* print(const Queue* const p, char* s);//��ӡpָ������s������s
void destroyQueue(Queue* const p);	 //����pָ��Ķ���
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