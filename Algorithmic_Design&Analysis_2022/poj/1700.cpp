#include<iostream>
#include<algorithm>
using namespace std;
int a[1001];
int main()
{
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
        }
        sort(a,a+n);
        int ans=0;
        while(n>3)
        {
            ans+=min(2*a[0]+a[n-1]+a[n-2],a[n-1]+a[0]+2*a[1]);
            n-=2;
        }
        if(n==3)
        {
            ans+=a[1]+a[0]+a[2];
        }
        else if(n==2)
        {
            ans+=a[1];
        }
        else if(n==1)
        {
            ans+=a[0];
        }
        cout<<ans<<endl;
    }
}