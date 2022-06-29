#include<iostream>
#include<queue>
#include<cstring>
#define inf 0x3f3f3f3f
using namespace std;
int dis[1500];
int g[1500][1500];
struct node{
    int num,val;
    bool operator<(const node& b)const
    {
        return val>b.val;
    }
    node(int n,int v)
    {
        num=n;
        val=v;
    }
};
priority_queue<node> q;
int main()
{
    int n,t;
    cin>>t>>n;
    memset(dis,inf,sizeof(dis));
    memset(g,-1,sizeof(g));
    for(int i=0;i<t;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        if(g[u][v]!=-1&&g[u][v]>w)
        {
            g[u][v]=w;
            g[v][u]=w;
        }
        else if(g[u][v]==-1)
        {
            g[u][v]=w;
            g[v][u]=w;
        }
    }
    dis[n]=0;
    node nownode(n,0);
    q.push(nownode);
    while(!q.empty())
    {
        nownode=q.top();
        q.pop();
        for(int i=1;i<n;i++)
        {
            if(g[nownode.num][i]!=-1&&dis[i]>dis[nownode.num]+g[nownode.num][i])
            {
                dis[i]=dis[nownode.num]+g[nownode.num][i];
                q.push(node(i,dis[i]));
            }
        }
    }
    cout<<dis[1];
}