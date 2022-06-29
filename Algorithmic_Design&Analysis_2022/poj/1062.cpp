#include <iostream>
#include <queue>
#include <cstring>
#define inf 0x3f3f3f3f
using namespace std;
struct node
{
    int id, val;
    bool operator<(const node &b) const
    {
        return id > b.id;
    }
    node(int id, int val)
    {
        this->id = id;
        this->val = val;
    }
};
int dis[150];
int g[150][150];
int rk[150];
int flag[150];
int m, n;
priority_queue<node> q;
void dij(int s);
int main()
{
    cin >> m >> n;
    // memset(dis,inf,sizeof(dis));
    memset(g, -1, sizeof(g));
    for (int i = 1; i <= n; i++)
    {
        int p, l, x;
        cin >> p >> l >> x;
        g[i][i] = p;
        rk[i] = l;
        g[i][0] = x;
        for (int j = 0; j < x; j++)
        {
            int v, va;
            cin >> v >> va;
            g[i][v] = va;
        }
    }
    int ans = inf;
    for (int i = 0; i <= m; i++)
    {
        memset(flag, 0, sizeof(flag));
        for (int j = 1; j <= n; j++)
        {
            if (rk[1] + i < rk[j] || rk[1] +i-m > rk[j])
            {
                flag[j] = 1;
            }
        }
        dij(1);
        for (int j = 1; j <= n; j++)
        {
            ans = min(ans, dis[j] + g[j][j]);
        }
    }
    cout << ans;
}
void dij(int s)
{
    memset(dis, inf, sizeof(dis));
    dis[s] = 0;
    node now(s, 0);
    q.push(now);
    while (!q.empty())
    {
        now = q.top();
        q.pop();
        flag[now.id] = 1;
        for (int i = 1; i <= n; i++)
        {
            if (i == s)
            {
                continue;
            }
            if (flag[i] == 0 && g[now.id][i] != -1 && dis[i] > dis[now.id] + g[now.id][i])
            {
                dis[i] = dis[now.id] + g[now.id][i];
                q.push(node(i, dis[i]));
            }
        }
    }
}