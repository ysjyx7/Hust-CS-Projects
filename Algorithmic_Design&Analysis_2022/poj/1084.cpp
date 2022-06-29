#include <iostream>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <queue>
using namespace std;
#define maxn 21
struct pos
{
    int x, y;
    pos(int xx, int yy) : x(xx), y(yy) {}
    pos() {}
};
struct posdep
{
    int x, y, dep;
    posdep(int xx, int yy, int dd) : x(xx), y(yy), dep(dd) {}
    posdep() {}
};
struct snake
{
    int x, y, dep, st;
    snake(int xx, int yy, int dd, int tt) : x(xx), y(yy), dep(dd), st(tt) {}
    snake() {}
};
bool mapp[maxn][maxn], preused[maxn][maxn], used[maxn][maxn][1 << 14];
int n, m, l, k;
const int Dir[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};
bool in_bounce(int x, int y)
{
    if (x <= n && x >= 1 && y <= m && y >= 1)
        return 1;
    return 0;
}
int calstep(int x, int y)
{
    deque<posdep> q;
    if (x == 1 && y == 1)
        return 0;
    q.push_back(posdep(x, y, 0));
    preused[x][y] = 1;
    bool sign = 0;
    posdep now;
    while (!q.empty())
    {
        now = q.front();
        for (int i = 0; i < 4; i++)
        {
            int newx, newy;
            newx = now.x + Dir[i][0], newy = now.y + Dir[i][1];
            if (!in_bounce(newx, newy) || mapp[newx][newy] || preused[newx][newy])
                continue;
            if (newx == 1 && newy == 1)
            {
                sign = 1;
                break;
            }
            q.push_back(posdep(newx, newy, now.dep + 1));
            preused[newx][newy] = 1;
        }
        if (sign)
            break;
        q.pop_front();
    }
    if (sign)
        return now.dep + 1;
    return -1;
}
queue<snake> q;
int main()
{
    // freopen("in.txt","r",stdin);
    int minstep, maxstep;
    int i, j, x, y, T = 1;
    pos body[10], block[405];
    while (scanf("%d%d%d", &n, &m, &l), n || m || l)
    {
        int tailnum = 0; //初始的尾部值
        while (!q.empty())
            q.pop();
        memset(mapp, 0, sizeof(mapp));
        memset(preused, 0, sizeof(preused));
        memset(used, 0, sizeof(used));
        for (i = 1; i <= l; i++)
        {
            scanf("%d%d", &body[i].x, &body[i].y);
        }
        for (i = 1; i <= l; i++)
            if (i != 1)
            {
                for (j = 0; j < 4; j++)
                    if (body[i].x + Dir[j][0] == body[i - 1].x && body[i].y + Dir[j][1] == body[i - 1].y)
                        tailnum = (tailnum << 2) + j;
            }
        scanf("%d", &k);
        for (i = 1; i <= k; i++)
        {
            scanf("%d%d", &x, &y);
            block[i].x = x, block[i].y = y;
            mapp[x][y] = 1;
        }
        for (i = 2; i <= l; i++)
            mapp[body[i].x][body[i].y] = 1;
        //把尾部都当成障碍的步数上限
        maxstep = calstep(body[1].x, body[1].y);
        cout<<endl<<maxstep<<endl;

        memset(mapp, 0, sizeof(mapp));
        for (i = 1; i <= k; i++)
            mapp[block[i].x][block[i].y] = 1;
        q.push(snake(body[1].x, body[1].y, 0, tailnum));
        used[body[1].x][body[1].y][tailnum] = 1;
        bool sign = 0;
        snake now;
        if (body[1].x != 1 || body[1].y != 1)
        {
            while (!q.empty())
            {
                now = q.front();
                //剪枝开始预估一下距离
                int dis;
                dis = now.x - 1 + now.y - 1 + now.dep;
                if (maxstep != -1 && dis > maxstep)
                {
                    q.pop();
                    continue;
                }
                //剪枝结束
                // 0-2 1-3
                int tailinf = now.st;
                int bd[10];  //准备保存提取出来的尾部信息
                bool dir[4]; //标记头部的四个方向是否可以走
                dir[0] = dir[1] = dir[2] = dir[3] = 1;

                for (i = 1; i < l; i++) //根据尾部的信息提取出尾部的坐标
                {
                    bd[l - i] = tailinf & 3;
                    tailinf >>= 2;
                }
                x = now.x, y = now.y; //头部坐标
                for (i = 1; i < l; i++)
                {
                    x = x + Dir[(bd[i] + 2) % 4][0], y = y + Dir[(bd[i] + 2) % 4][1];
                    for (j = 0; j < 4; j++)
                        if (now.x + Dir[j][0] == x && now.y + Dir[j][1] == y)
                            dir[j] = 0;
                }
                for (i = 0; i < 4; i++)
                    if (!in_bounce(now.x + Dir[i][0], now.y + Dir[i][1]) || mapp[now.x + Dir[i][0]][now.y + Dir[i][1]])
                        dir[i] = 0;
                //前一个部分在后一个部分的哪个方向
                for (i = 0; i < 4; i++)
                    if (dir[i])
                    {
                        int tailinf = (now.st >> 2) + (i << (2 * (l - 2)));
                        if (now.x + Dir[i][0] == 1 && now.y + Dir[i][1] == 1)
                        {
                            sign = 1;
                            break;
                        }
                        if (!used[now.x + Dir[i][0]][now.y + Dir[i][1]][tailinf])
                        {
                            q.push(snake(now.x + Dir[i][0], now.y + Dir[i][1], now.dep + 1, tailinf));
                            used[now.x + Dir[i][0]][now.y + Dir[i][1]][tailinf] = 1;
                        }
                    }
                if (sign)
                    break;
                q.pop();
            }
            if (sign)
                printf("Case %d: %d\n", T, now.dep + 1);
            else
                printf("Case %d: -1\n", T);
        }
        else
            printf("Case %d: 0\n", T);
        T++;
    }
    return 0;
}