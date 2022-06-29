#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
struct pond
{
    int id, f, d, t;
    bool operator<(const pond &a)const
    {
        if (f == a.f)
        {
            return id > a.id;
        }
        return f < a.f;
    }
} p[30];
int ans;
int a[30];
int b[30];
int n, h;
int main()
{
    while (1)
    {
        cin >> n;
        if (n == 0)
        {
            return 0;
        }
        memset(a, 0, sizeof(a));
        cin >> h;
        h *= 12;
        for (int i = 0; i < n; i++)
            cin >> p[i].f;
        for (int i = 0; i < n; i++)
            cin >> p[i].d;
        for (int i = 0; i < n - 1; i++)
            cin >> p[i].t;
        for (int i = 0; i < n; i++)
        {
            p[i].id = i;
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            memset(b, 0, sizeof(b));
            int temph = h;
            priority_queue<pond> pp;
            for (int j = 0; j < i; j++)
            {
                temph -= p[j].t;
            }
            for (int j = 0; j <= i; j++)
            {
                pp.push(p[j]);
            }
            int nowans = 0;
            while (temph > 0 && !pp.empty())
            {
                pond q = pp.top();
                pp.pop();
                temph--;
                nowans += q.f;
                b[q.id] += 5;
                q.f -= q.d;
                if (q.f < 0)
                    q.f = 0;
                pp.push(q);
            }
            if(nowans>ans)
            {
                ans=nowans;
                for(int j=0;j<=i;j++)
                {
                    a[j]=b[j];
                }
            }
            else if(nowans==ans)
            {
                int flag=0;
                for(int j=0;j<=i;j++)
                {
                    if(a[j]>b[j])
                    {
                        break;
                    }
                    else if(a[j]<b[j])
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag)
                {
                    for(int j=0;j<=i;j++)
                    {
                        a[j]=b[j];
                    }
                }
            }
        }
        for(int i=0;i<n-1;i++)
        {
            cout<<a[i]<<','<<' ';
        }
        cout<<a[n-1]<<endl;
        cout<<"Number of fish expected: "<<ans<<endl;
        cout<<endl;
    }
}
