#include<iostream>
#include<cmath>
using namespace std;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int r,c;
int h[101][101];
int dp[101][101];
int dfs(int x,int y);
int main()
{
    cin>>r>>c;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>h[i][j];
        }
    }
    int ans=-1;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            ans=max(ans,dfs(i,j));
        }
    }
    cout<<ans;
}
int dfs(int x,int y)
{
    if(dp[x][y]!=0)
    {
        return dp[x][y];
    }
    dp[x][y]=1;
    for(int i=0;i<4;i++)
    {
        int xx=x+dx[i];
        int yy=y+dy[i];
        if(xx>=0&&xx<r&&yy>=0&&yy<c&&h[xx][yy]<h[x][y])
        {
            dp[x][y]=max(dfs(xx,yy)+1,dp[x][y]);
        }
    }
    return dp[x][y];
}