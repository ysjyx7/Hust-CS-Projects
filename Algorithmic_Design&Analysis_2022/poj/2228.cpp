#include <iostream>
#include <string.h>
#define inf 0x3f3f3f3f
using namespace std;
int n, b;
const int maxn = 4000;
int u[maxn];
int dp[2][maxn][2];
int main()
{
    cin >> n >> b;
    for (int i = 1; i <= n; i++)
    {
        cin >> u[i];
    }
    memset(dp, -inf, sizeof(dp));
    dp[1][0][0] = 0;
    dp[1][1][1] = 0;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            dp[i & 1][j][0] = max(dp[(i - 1) & 1][j][0], dp[(i - 1) & 1][j][1]);
            if (j >= 1)
                dp[i & 1][j][1] = max(dp[(i - 1) & 1][j - 1][0], dp[(i - 1) & 1][j - 1][1] + u[i]);
        }
    }
    int ans = max(dp[n & 1][b][0], dp[n & 1][b][1]);

    memset(dp, -inf, sizeof(dp));
    dp[1][1][1] = u[1];
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            dp[i & 1][j][0] = max(dp[(i - 1) & 1][j][0], dp[(i - 1) & 1][j][1]);
            if (j >= 1)
                dp[i & 1][j][1] = max(dp[(i - 1) & 1][j - 1][0], dp[(i - 1) & 1][j - 1][1] + u[i]);
        }
    }
    ans = max(ans, dp[n & 1][b][1]);

    printf("%d\n", ans);
}