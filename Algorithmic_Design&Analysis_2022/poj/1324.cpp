#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
bool g[21][21];
bool vis[21][21][1 << 14];
bool preused[21][21];
int maxn;
struct node
{
    int x, y;
    int st, dis;
    node(int _x, int _y, int _st, int _dis)
    {
        x = _x;
        y = _y;
        st = _st;
        dis = _dis;
    }
};
int tcase = 1;
int dir[10];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int r, c, l;
bool check(int x, int y, node n);
int BFS(node n);
int calstep(int x, int y);
queue<node> q;
bool map[21][21];
int main()
{
    while (1)
    {
        cin >> r >> c >> l;
        if (r == 0)
        {
            return 1;
        }
        node head(0, 0, 0, 0);
        cin >> head.x >> head.y;
        int x, y, nx, ny;
        x = head.x;
        y = head.y;
        memset(map, 0, sizeof(map));
        for (int i = 1; i < l; i++)
        {
            cin >> nx >> ny;
            for (int j = 0; j < 4; j++)
            {
                if (x + dx[j] == nx && y + dy[j] == ny)
                {
                    head.st = (head.st << 2) + j;
                }
            }
            map[nx][ny]=1;
            x = nx, y = ny;
        }
        int k;
        cin >> k;
        memset(g, 0, sizeof(g));
        for (int i = 0; i < k; i++)
        {
            cin >> x >> y;
            g[x][y] = 1;
            map[x][y] = 1;
        }
        maxn = calstep(head.x, head.y);
        cout << "Case " << tcase << ':' << ' ' << BFS(head) << endl;
        while (!q.empty())
        {
            q.pop();
        }
    }
}
bool check(int x, int y, node n)
{
    for (int i = l - 1; i >= 1; i--)
    {
        dir[i] = n.st & 3;
        n.st >>= 2;
    }
    int xx = n.x;
    int yy = n.y;
    for (int i = 1; i < l; i++)
    {
        xx += dx[dir[i]];
        yy += dy[dir[i]];
        if (xx == x && yy == y)
        {
            return false;
        }
    }
    return true;
}
int BFS(node head)
{
    tcase++;
    if (head.x == 1 && head.y == 1)
    {
        return 0;
    }
    q.push(head);
    vis[head.x][head.y][head.st] = tcase;
    while (!q.empty())
    {
        node n = q.front();
        int di;
        di = n.x - 1 + n.y - 1 + n.dis;
        if (maxn != -1 && di > maxn)
        {
            q.pop();
            continue;
        }
        q.pop();
        int x = n.x;
        int y = n.y;
        int st = n.st;
        int dis = n.dis;
        for (int i = 0; i < 4; i++)
        {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx == 1 && yy == 1)
                return dis + 1;
            if (xx < 1 || xx > r || yy < 1 || yy > c || !check(xx, yy, n) || g[xx][yy])
                continue;
            int ndis = dis + 1;
            int nst;
            nst = (st >> 2) + ((i + 2) % 4 << ((l - 2) << 1));
            if (vis[xx][yy][nst] == tcase)
                continue;
            q.push(node(xx, yy, nst, ndis));
            vis[xx][yy][nst] = tcase;
        }
    }
    return -1;
}
bool in_bounce(int x, int y)
{
    if (x <= r && x >= 1 && y <= c && y >= 1)
        return 1;
    return 0;
}
int calstep(int x, int y)
{
    queue<node> q;
    if (x == 1 && y == 1)
        return 0;
    q.push(node(x, y, 0, 0));
    preused[x][y] = 1;
    bool sign = 0;
    node now(0, 0, 0, 0);
    while (!q.empty())
    {
        now = q.front();
        for (int i = 0; i < 4; i++)
        {
            int newx, newy;
            newx = now.x + dx[i], newy = now.y + dy[i];
            if (!(in_bounce(newx,newy)) || map[newx][newy] || preused[newx][newy])
                continue;
            if (newx == 1 && newy == 1)
            {
                sign = 1;
                break;
            }
            q.push(node(newx, newy,0, now.dis + 1));
            preused[newx][newy] = 1;
        }
        if (sign)
            break;
        q.pop();
    }
    if (sign)
        return now.dis + 1;
    return -1;
}