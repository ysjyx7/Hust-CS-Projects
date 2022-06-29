#include <iostream>
#include<limits.h>
using namespace std;
int g[25][25];
void dfs(int x, int y, int depth);
bool check();
void flip(int x, int y);
int ans=INT_MAX;
int main()
{
    char s[5];
    for (int i = 0; i < 4; i++)
    {
        cin >> s;
        for (int j = 0; j < 4; j++)
        {
            if (s[j] == 'w')
                g[i][j] = 0;
            else
                g[i][j] = 1;
        }
    }
    dfs(0, 0, 0);
    if(ans==INT_MAX)
    {
        cout<<"Impossible";
    }
    else
    cout << ans;
}
bool check()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (g[i][j] != g[0][0])
            {
                return 0;
            }
        }
    }
    return 1;
}
void flip(int x, int y)
{
    g[x][y] = !g[x][y];
    if (x - 1 >= 0)
        g[x - 1][y] = !g[x - 1][y];
    if (x + 1 < 4)
        g[x + 1][y] = !g[x + 1][y];
    if (y - 1 >= 0)
        g[x][y - 1] = !g[x][y - 1];
    if (y + 1 < 4)
        g[x][y + 1] = !g[x][y + 1];
}
void dfs(int x, int y, int depth)
{
    if (check())
    {
        ans = min(ans, depth);
        return;
    }
    if(x>=4||y>=4)
    {
        return;
    }
    int xx,yy;
    xx=(x+1)%4;
    yy=y+(x+1)/4;
    dfs(xx,yy,depth);
    flip(x,y);
    dfs(xx,yy,depth+1);
    flip(x,y);
}