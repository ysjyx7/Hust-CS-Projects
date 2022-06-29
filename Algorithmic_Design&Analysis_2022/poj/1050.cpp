#include<iostream>
#include<limits.h>
using namespace std;
int sum[150][150];
int a[150][150];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>a[i][j];
            sum[i][j]+=sum[i-1][j]+a[i][j];
        }
    }
    int ans=INT_MIN;
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            int nowmax=INT_MIN;
            for(int k=1;k<=n;k++)
            {
                int temp=sum[j][k]-sum[i-1][k];
                if(nowmax>0)
                {
                    nowmax+=temp;
                }
                else{
                    nowmax=temp;
                }
                if(nowmax>ans)
                {
                    ans=nowmax;
                }
            }
        }
    }
    cout<<ans;

}