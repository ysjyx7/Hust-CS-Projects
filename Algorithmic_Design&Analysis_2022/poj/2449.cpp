#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#define inf 0x3f3f3f3f
using namespace std;
struct node{
    int id,h,f;
};
vector<pair<int,int>> map[100010],map1[100010];
int dist[1001];
int flag[1001];
int n,m;
int s,t;
void dijstra();
int main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        map[u].push_back(pair<int,int>(v,w));
        map1[v].push_back(pair<int,int>(u,w));
    }
    cin>>s>>t;
    dijstra();
}
void dijstra()
{
    for(int i=1;i<=n;i++)
    {
        dist[i]=inf;
    }
    dist[t]=0;
    flag[t]=1;
    int k=0;
    for(int i=1;i<=n;i++)
    {
        int min=inf;
        for(int j=1;j<=n;j++)
        {
            if(!flag[j])
            {
                if(dist[j]<min)
                {
                    k=j;
                    min=dist[j];
                }
            }
        }
        flag[k]=1;
        for(int j=1;j<=n;j++)
        {
            if(!flag[j]&&min+map1[k][j].first)
            {
                
            }
        }
    }
}