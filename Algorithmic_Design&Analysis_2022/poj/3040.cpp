#include<iostream>
#include<algorithm>
#include<cstring>
#include<limits.h>
using namespace std;
struct point
{
    /* data */
    int cnt,val;
};
point ps[21];
int used[21];
bool cmp(point &a,point &b)
{
    return a.val<b.val;
}
int main()
{
    int n,c;
    cin>>n>>c;
    for(int i=0;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        ps[i].val=a;
        ps[i].cnt=b;
    }
    sort(ps,ps+n,cmp);
    int ans=0;
    while(n)
    {
        if(ps[n-1].val<=c)
        {
            break;
        }
        ans+=ps[n-1].cnt;
        n--;
    }
    while(1)
    {
        int res=c;
        int flag=0;
        memset(used,0,sizeof(used));
        for(int i=n-1;i>=0;i--)
        {
            int k=res/ps[i].val;
            int act=min(ps[i].cnt,k);
            used[i]=act;
            res-=act*ps[i].val;
            if(res<=0)
            {
                flag=1;
                break;
            }
        }
        if(res>0)
        {
            for(int i=0;i<n;i++)
            {
                if(ps[i].cnt>used[i])
                {
                    while(used[i]<ps[i].cnt)
                    {
                        used[i]++;
                        res-=ps[i].val;
                        if(res<=0)
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(res<=0)
                    {
                        break;
                    }
                }
            }
        }
        if(!flag)
        {
            break;
        }
        int ct=INT_MAX;
        for(int i=0;i<n;i++)
        {
            if(used[i])
            {
                ct=min(ct,ps[i].cnt/used[i]);
            }
        }
        ans+=ct;
        for(int i=0;i<n;i++)
        {
            ps[i].cnt-=ct*used[i];
        }
    }
    cout<<ans;
}