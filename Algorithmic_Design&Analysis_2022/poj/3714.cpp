#include <iostream>
#include <cmath>
#include <algorithm>
#define N 100005
const double inf = 1e20;
using namespace std;
struct point
{
    int flag;
    double x;
    double y;
} p[2*N];
int tempt[N];
bool cmpx(point &a, point &b)
{
    if (a.x != b.x)
    {
        return a.x < b.x;
    }
    return a.y < b.y;
}
bool cmpy(int a, int b)
{
    return p[a].y < p[b].y;
}
double dis(point &a, point &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
// double min(double a,double b)
// {
//     return a<b?a:b;
// }
double solution(int left, int right)
{
    double d = inf;
    if (left == right)
    {
        return d;
    }
    if (left + 1 == right)
    {
        if (p[left].flag != p[right].flag)
            return dis(p[left], p[right]);
    }
    int mid = (left + right) >> 1;
    double dl = solution(left, mid);
    double dr = solution(mid + 1, right);
    d = min(dl, dr);
    int i, j, k = 0;
    for (i = left; i <= right; i++)
    {
        if (fabs(p[mid].x - p[i].x) <= d)
        {
            tempt[k++] = i;
        }
    }
    sort(tempt, tempt + k, cmpy);
    for (i = 0; i < k; i++)
    {
        for (j = i + 1; j < k; j++)
        {
            if(p[tempt[i]].flag!=p[tempt[j]].flag)
            {
                double d3=dis(p[tempt[i]],p[tempt[j]]);
                d=min(d,d3);
            }
        }
    }
    return d;
}
int main()
{
    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            scanf("%lf %lf", &p[i].x, &p[i].y);
            p[i].flag=0;
        }
        for(int i=n;i<2*n;i++)
        {
            scanf("%lf %lf",&p[i].x,&p[i].y);
            p[i].flag=1;
        }
        sort(p, p + 2*n, cmpx);
        double d = solution(0, 2*n - 1);
        printf("%.3lf\n",d);
    }
}