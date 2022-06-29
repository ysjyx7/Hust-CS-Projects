#include <iostream>
#include <stack>
#include <string>
using namespace std;
string a;
int main()
{
t1:
    while (cin >> a)
    {
        if (a[0] == '0')
        {
            return 0;
        }
        int p, q, r, s, t,w,x;
        int len = a.size();
        int ans = 0;
        for (p = 0; p <= 1; p++)
        {
            for (q = 0; q <= 1; q++)
            {
                for (r = 0; r <= 1; r++)
                {
                    for (s = 0; s <= 1; s++)
                    {
                        for (t = 0; t <= 1; t++)
                        {
                            stack<int> sta;
                            for (int i = len - 1; i >= 0; i--)
                            {
                                switch (a[i])
                                {
                                case 'p':
                                    sta.push(p);
                                    break;
                                case 'q':
                                    sta.push(q);
                                    break;
                                case 'r':
                                    sta.push(r);
                                    break;
                                case 's':
                                    sta.push(s);
                                    break;
                                case 't':
                                    sta.push(t);
                                    break;
                                case 'K':
                                    w = sta.top();
                                    sta.pop();
                                    x = sta.top();
                                    sta.pop();
                                    sta.push(w && x);
                                    break;
                                case 'A':
                                    w = sta.top();
                                    sta.pop();
                                    x = sta.top();
                                    sta.pop();
                                    sta.push(w || x);
                                    break;
                                case 'N':
                                   w = sta.top();
                                    sta.pop();
                                    sta.push(!w);
                                    break;
                                case 'C':
                                    x = sta.top();
                                    sta.pop();
                                   w = sta.top();
                                    sta.pop();
                                    if (x == 1 && w == 0)
                                    {
                                        sta.push(0);
                                    }
                                    else
                                        sta.push(1);
                                    break;
                                case 'E':
                                   w = sta.top();
                                    sta.pop();
                                  x = sta.top();
                                    sta.pop();
                                    sta.push(!(w ^ x));
                                    break;
                                }
                            }
                            ans = sta.top();
                            if (ans == 0)
                            {
                                cout << "not" << endl;
                                goto t1;
                            }
                        }
                    }
                }
            }
        }
        if (ans == 1)
        {
            cout << "tautology" << endl;
        }
    }
}