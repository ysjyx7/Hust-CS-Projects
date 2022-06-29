#include<iostream>
using namespace std;
struct edge{
    int u,v;
    double rate;
    double comm;
};
edge edges[250];
double dis[150];
int n,s,m;
double v;
int cnt;
bool bellman_fold();
int main()
{
    cin>>n>>m>>s>>v;
    for(int i=0;i<m;i++)
    {
        cin>>edges[cnt].u>>edges[cnt].v>>edges[cnt].rate>>edges[cnt].comm;
        edges[cnt+1].u=edges[cnt].v;
        edges[cnt+1].v=edges[cnt].u;
        cnt++;
        cin>>edges[cnt].rate>>edges[cnt].comm;
        cnt++;
    }
    dis[s]=v;
    if(bellman_fold())
    {
        cout<<"YES";
    }
    else{
        cout<<"NO";
    }
}
bool bellman_fold()
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<cnt;j++)
        {
            int u=edges[j].u;
            int v=edges[j].v;
            if((dis[u]-edges[j].comm)*edges[j].rate>dis[v])
            {
                dis[v]=(dis[u]-edges[j].comm)*edges[j].rate;
            }
        }
    }
    for(int j=0;j<cnt;j++)
    {
        int u=edges[j].u;
            int v=edges[j].v;
            if((dis[u]-edges[j].comm)*edges[j].rate>dis[v])
            {
                return true;
            }
    }
    return false;
}