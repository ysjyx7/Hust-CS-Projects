#include <iostream>
using namespace std;
struct matrix
{
    int m[31][31];
};
int n, m, t;
matrix add(matrix a, matrix b)
{
    matrix c;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c.m[i][j] = (a.m[i][j] + b.m[i][j]) % m;
        }
    }
    return c;
}
matrix multi(matrix a, matrix b)
{
    matrix c;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int sum = 0;
            for (int k = 0; k < n; k++)
            {
                sum += (a.m[i][k] * b.m[k][j]) % m;
            }
            c.m[i][j] = sum % m;
        }
    }
    return c;
}
matrix pow(matrix a, int t)
{
    matrix b;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                b.m[i][j] = 1;
            else
                b.m[i][j] = 0;
        }
    }
    while (t)
    {
        if (t & 1)
        {
            b = multi(b, a);
        }
        a = multi(a, a);
        t >>= 1;
    }
    return b;
}
matrix sum(matrix a, int t)
{
    matrix c;
    if (t == 1)
    {
        return a;
    }
    matrix temp = sum(a, t / 2);
    if (t % 2 == 1)
    {
        matrix p = pow(a, t / 2 + 1);
        return add(add(temp, p), multi(temp, p));
    }
    matrix p = pow(a, t / 2);
    return add(temp, multi(p, temp));
}
int main()
{
    cin >> n >> t >> m;
    matrix a;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a.m[i][j];
            a.m[i][j] = a.m[i][j] % m;
        }
    }
    a = sum(a, t);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            cout << a.m[i][j] << ' ';
        }
        cout << a.m[i][n - 1];
        cout << endl;
    }
}