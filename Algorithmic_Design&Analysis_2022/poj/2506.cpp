#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
string add(string a, string b);
int main()
{
    int n;
    string dp[300];
    dp[0]="1";
    dp[1] = "1";
    dp[2] = "3";
    for (int i = 3; i <= 260; i++)
    {
        dp[i]=add(dp[i-1],add(dp[i-2],dp[i-2]));
    }
    while (~scanf("%d", &n))
    {
        cout<<dp[n]<<endl;
    }
}
string add(string a, string b)
{
    if (a.size() < b.size())
    {
        swap(a, b);
    }
    int c = 0;
    for (int i = a.size() - 1, j = b.size() - 1; i >= 0; i--, j--)
    {
        a[i] += (j >= 0 ? b[i] - '0' : 0) + c;
        int temp = (a[i] - '0') % 10;
        c = (a[i] - '0') / 10;
        a[i] = temp + '0';
    }
    if (c != 0)
    {
        a = "1" + a;
    }
    return a;
}