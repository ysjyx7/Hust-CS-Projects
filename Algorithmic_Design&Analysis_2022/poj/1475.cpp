#include <iostream>
#include <queue>
#include <string.h>
#include <string>
using namespace std;
char map[25][25];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
char p[5] = "ewsn";
char b[5] = "EWSN";
int r, c;
int kcase=1;
struct person
{
    int x, y;
    string path;
    person(int _x = 0, int _y = 0, string _path = "")
    {
        x = _x;
        y = _y;
        path = _path;
    }
};
struct point
{
    int bx, by;
    int px, py;
    string path;
    point(int _bx = 0, int _by = 0, int _px = 0, int _py = 0, string _path = "")
    {
        bx = _bx;
        by = _by;
        px = _px;
        py = _py;
        path = _path;
    }
};
point st;
void init()
{
    cin >> r >> c;
    for (int i = 0; i < r; i++)
    {
        cin >> map[i];
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (map[i][j] == 'S')
            {
                st.px = i;
                st.py = j;
            }
            if (map[i][j] == 'B')
            {
                st.bx = i;
                st.by = j;
            }
        }
    }
}
bool check(int x, int y)
{
    if (x < 0 || x >= r || y < 0 || y >= c || map[x][y] == '#')
    {
        return false;
    }
    return true;
}
bool bfs1(int px, int py, int bx, int by, int bbx, int bby, string &path)
{
    int vis[25][25];
    memset(vis, 0, sizeof(vis));
    vis[px][py] = 1;
    vis[bbx][bby] = 1;
    queue<person> q;
    person head(px, py, "");
    q.push(head);
    while (!q.empty())
    {
        person h = q.front();
        q.pop();
        if (h.x == bx && h.y == by)
        {
            path = h.path;
            return true;
        }
        for (int i = 0; i < 4; i++)
        {
            int xx = h.x + dx[i];
            int yy = h.y + dy[i];
            if (check(xx, yy) && !vis[xx][yy])
            {
                vis[xx][yy] = 1;
                q.push(person(xx, yy, h.path + p[i]));
            }
        }
    }
    return false;
}
string bfs2()
{
    string ans;
    int vis[25][25];
    memset(vis, 0, sizeof(vis));
    queue<point> q;
    int flag = 0;
    vis[st.bx][st.by] = 1;
    q.push(st);
    while (!q.empty())
    {
        point h = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int bbx = h.bx + dx[i], bby = h.by + dy[i];
            int ppx = h.bx - dx[i], ppy = h.by - dy[i];
            string path = "";
            if (check(bbx, bby) && check(ppx, ppy) && !vis[bbx][bby])
            {
                if (bfs1(h.px, h.py, ppx, ppy, h.bx, h.by, path))
                {
                    point n;
                    n.bx = bbx;
                    n.by = bby;
                    n.px = h.bx;
                    n.py = h.by;
                    n.path = h.path + path + b[i];
                    q.push(n);
                    vis[bbx][bby] = 1;
                    if (map[bbx][bby] == 'T')
                    {
                        if (flag == 0)
                        {
                            flag = 1;
                            ans = n.path;
                        }
                        else
                        {
                            if (n.path.size() < ans.size())
                            {
                                ans = n.path;
                            }
                        }
                    }
                }
            }
        }
    }
    if (flag)
        return ans;
    else
        return "Impossible.";
}
int main()
{
    while(1)
    {
        init();
        if(r==0)
        {
            return 1;
        }
        string ans=bfs2();
        cout<<"Maze #"<<kcase++<<endl;
        cout<<ans<<endl<<endl;
    }
}