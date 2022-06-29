#include<iostream>
#include<cstring>
#define inf 0x3f3f3f3f
using namespace std;
struct edge{
    int u,v,val;
};
edge edges[5000000];
int dis[50010];
void bellman_ford();
int n,cnt;
int up=-1;
int down=inf;
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        if(down>a-1)
        {
            down=a-1;
        }
        if(up<b)
        {
            up=b;
        }
        edges[cnt].u=b;
        edges[cnt].v=a-1;
        edges[cnt++].val=-c;
    }
    for(int i=down;i<=up;i++)
    {
        if(i!=up)
        {
            edges[cnt].u=i;
            edges[cnt].v=i+1;
            edges[cnt++].val=1;
        }
        if(i!=down)
        {
            edges[cnt].u=i;
            edges[cnt].v=i-1;
            edges[cnt++].val=0;

        }
    }
    bellman_ford();
    cout<<dis[up]-dis[down];
}
void bellman_ford()
{
    memset(dis,0,sizeof(dis));
    for(int i=down;i<=up;i++)
    {
        int flag=0;
        for(int j=0;j<cnt;j++)
        {
            if(dis[edges[j].v]>dis[edges[j].u]+edges[j].val)
            {
                dis[edges[j].v]=dis[edges[j].u]+edges[j].val;
                flag=1;
            }
        }
        if(flag==0)
        {
            break;
        }
    }
}