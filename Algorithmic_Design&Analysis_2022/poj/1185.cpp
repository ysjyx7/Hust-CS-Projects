#include <iostream>
#include <string>
#include <cmath>
#define MAXR 101
#define MAXC 12
using namespace std;
int r, c;
int g[MAXR]; // 存储二进制的地图
int state[MAXR]; // 存储所有可能的行状态，这里不考虑列之间的影响
int soldier[MAXR]; // 对于每一种状态，存储当前状态下这一行士兵的数量
int dp[MAXR][MAXR][MAXR]; // dp[i][j][k]表示第i行状态为j且第i-1行状态为k时的最大数量，这其实类似于枚举
int main()
{
    string in;
    cin >> r >> c;
    for (int i = 0; i < r; i++)
    {
        cin >> in;
        for (int j = 0; j < c; j++)
        {
            if (in[j] == 'H')
            {
                g[i] += (1 << j); // 这里将原地图中的山峰都用1表示
            }
        }
    }
    int nums = 0; // nums最终为行所有可能状态的数量
    for (int i = 0; i < (1 << c); i++) // 这一个循环用来枚举行的所有状态的可能性。
    {
        if ((i & i << 1) || (i & i << 2)) // 行中放炮手的位置设置成1，根据题意行间要想不冲突，炮手的距离应该大于2
            continue;    // 这个位运算就用来做这个事
        int k = i;
        while (k) // 如果这个状态可以的话就把他存到soldier和state数组里
        {
            soldier[nums] += (k & 1);
            k >>= 1;
        }
        state[nums++] = i;
    }
    for (int i = 0; i < nums; i++) // 这个循环用来初始化第一行
    {
        if (state[i] & g[0]) // 这里的判断就是判断这里和地形是否冲突
            continue;
        dp[0][i][0] = soldier[i];
    }
    for (int i = 0; i < nums; i++) // 这个循环用来初始化第二行
    {
        if (state[i] & g[1])
            continue;
        for (int j = 0; j < nums; j++)
        {
            if ((state[j] & g[0]) || (state[i] & state[j])) // 这里用来判断和地形是否冲突并且这两行状态是否冲突
                continue;
            dp[1][i][j] = max(dp[1][i][j], dp[0][j][0] + soldier[i]); // 更新。
        }
    }
    for (int nowr = 2; nowr < r; nowr++) // 从第二行开始递推，思路和前面是差不多的
    {
        for (int i = 0; i < nums; i++)
        {
            if (state[i] & g[nowr])
                continue;
            for (int j = 0; j < nums; j++)
            {
                if ((state[j] & g[nowr - 1]) || (state[i] & state[j]))
                    continue;
                for (int k = 0; k < nums; k++)
                {
                    if ((state[k] & g[nowr - 2]) || (state[j] & state[k]) || (state[i] & state[k]))
                        continue;
                    dp[nowr][i][j] = max(dp[nowr][i][j], dp[nowr - 1][j][k] + soldier[i]);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < nums; i++) // 统计最后一行对应的所有状态里的最大值，就是最终答案
    {
        for (int j = 0; j < nums; j++)
        {
            ans = max(ans, dp[r - 1][i][j]);
        }
    }
    cout << ans;
}