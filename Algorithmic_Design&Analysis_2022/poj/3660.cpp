#include <iostream>
#include <algorithm>
using namespace std;
int n, m;
bool g[101][101];
int a[101];
int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u][v] = 1;
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                g[i][j] = g[i][j] | (g[i][k] & g[k][j]);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int times=0;
        for(int j=1;j<=n;j++)
        {
            if(g[i][j]||g[j][i])
            times++;
        }
        if(times==n-1)
        {
            ans++;
        }
    }
    cout<<ans;
}