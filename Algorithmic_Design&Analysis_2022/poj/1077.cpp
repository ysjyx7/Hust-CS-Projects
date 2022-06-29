#include<iostream>
#include<unordered_map>
#include<queue>
#include<stdio.h>
using namespace std;
unordered_map<int,bool> vis;
unordered_map<int,int> step;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
char in[3][3];
int map[3][3];
int state;
int main()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            char x;
            cin>>x;
            if(x=='x')
                x='0';
            state=state*10+x-'0';
        }
    }
    queue<int> q;
    q.push(state);
    vis[state]=1;
    step[state]=0;
    while(!q.empty())
    {
        int h;
        h=q.front();
        q.pop();
        if(h==123456780)
        {
            cout<<step[h];
            return 1;
        }
        for(int i=0;i<4;i++)
        {
            int t=h;
            int r,c;
            for(int j=2;j>=0;j--)
            {
                for(int k=2;k>=0;k--)
                {
                    map[j][k]=t%10;
                    t/=10;
                    if(map[j][k]==0)
                    {
                        r=j;
                        c=k;
                    }
                }
            }
            if((i==0&&c==2)||(i==1&&c==0)||(i==2&&r==2)||(i==3&&r==0))
            {
                continue;
            }
            int v=0;
            int dr=r+dx[i];
            int dc=c+dy[i];
            map[r][c]=map[dr][dc];
            map[dr][dc]==0;
            for(int j=0;j<2;j++)
            {
                for(int k=0;k<2;k++)
                {
                    v=v*10+map[j][k];
                }
            }
            if(!vis[v])
            {
                vis[v]=1;
                step[v]=step[h]+1;
                q.push(v);
            }
        }
    }
    cout<<-1;
}