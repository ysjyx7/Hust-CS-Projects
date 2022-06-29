#include<stdio.h>
#include<vector>
using namespace std;
int n,m;
bool find(vector<int> &a,int target);
int main()
{
    vector<int> a;
    vector<int> b;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int temp;
        scanf("%d",&temp);
        a.push_back(temp);
    }
    scanf("%d",&m);
    for(int i=0;i<m;i++)
    {
        int x;
        scanf("%d",&x);
        if(find(a,10000-x))
        {
            printf("YES");
            return 1;
        }
    }
    printf("NO");
}
bool find(vector<int> &a,int target)
{
    int l=0,r=n;
    int mid;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(a[mid]==target)
        {
            return true;
        }
        else if(a[mid]<target)
        {
            l=mid+1;
        }
        else
        {
            r=mid;
        }
    }
    return false;
}