#include<iostream>
using namespace std;
int m,r,cnt,n;
int f[405],a[405],b[405],dp[201][201],flag[405];
void init()
{
    for(int i=0;i<=403;i++)
    {
        f[i]=i;
        a[i]=0;
        b[i]=0;
        flag[i]=0;
    }
    for(int i=0;i<201;i++)
    {
        for(int j=0;j<201;j++)
        {
            dp[i][j]=0;
        }
    }
    dp[0][0]=1;
    cnt=1;
}
int find(int x)
{
    while(x!=f[x])
    {
        x=f[x];
    }
    return x;
}
void merge(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy)
    {
        f[fx]=fy;
    }
}
int main()
{
    cin>>n;
    while(n--)
    {
        cin>>m>>r;
        init();
        for(int i=0;i<r;i++)
        {
            int xi,yi;
            cin>>xi>>yi;
            merge(xi,yi+200);
        }
        for(int i=1;i<=m;i++)
        {
            int father=find(i);
            if(flag[father])
            {
                a[flag[father]]++;
            }
            else{
                flag[father]=cnt;
                a[cnt]++;
                cnt++;
            }
            father=find(i+200);
            if(flag[father])
            {
                b[flag[father]]++;
            }
            else{
                flag[father]=cnt;
                b[cnt]++;
                cnt++;
            }
        }
        int ans=0;
        for(int i=1;i<cnt;i++)
        {
            for(int j=m/2;j>=a[i];j--)
            {
                for(int k=m/2;k>=b[i];k--)
                {
                    if(dp[j-a[i]][k-b[i]])
                    {
                        dp[j][k]=true;
                        if(j==k)
                        {
                            ans=(ans>j?ans:j);
                        }
                    }
                }
            }
        }
        cout<<ans<<endl;
    }
}