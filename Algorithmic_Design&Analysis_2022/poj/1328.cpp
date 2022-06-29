#include<iostream>
#include<cmath>
#include<algorithm>
#include<limits.h>
using namespace std;
struct intv
{
    double a,b;
};
intv intvs[1500];
bool cmp(intv &a,intv &b)
{
    return a.a<b.a;
}
int main()
{
    int i=1;
    int n,d;
    while(1)
    {
        cin>>n>>d;
        if(n==0)
        {
            break;
        }
        bool flag=true;
        for(int i=0;i<n;i++)
        {
            double x,y;
            cin>>x>>y;
            if(flag==false)
            {
                continue;
            }
            if(y>d)
            {
                flag=false;
                continue;
            }
            double dis=sqrt(d*d-y*y);
            intvs[i].a=x-dis;
            intvs[i].b=x+dis;
        }
        if(flag==false)
        {
            cout<<"Case "<<i<<": "<<-1<<endl;
            i++;
            continue;
        }
        sort(intvs,intvs+n,cmp);
        double end=INT_MIN;
        int ans=0;
        for(int i=0;i<n;i++)
        {
            if(end<intvs[i].a)
            {
                ans++;
                end=intvs[i].b;
            }
            else if(end>intvs[i].b)
            {
                end=intvs[i].b;
            }
        }
        cout<<"Case "<<i<<": "<<ans<<endl;
        i++;
    }
}