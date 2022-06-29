#include <stdio.h>
#include <stdlib.h>
int month[12];
int main()
{
    int d, s;
    while (scanf("%d", &s) == 1 && scanf("%d", &d) == 1)
    {
        d = -d;
        int i = 0;
        for (i = 0; i < 12; i++)
            month[i] = s;

        int j;
        for (i = 0; i < 8; i++)
        {
            for (j = 1; j <= 5; j++)
            {
                int sum=0;
                for (int k = i; k < i + 5; k++)
                {
                    sum += month[k];
                }
                if (sum >= 0)
                    month[i + 5 - j] = d;
                else
                    break;
            }
        }
        int all = 0;
        for (i = 0; i < 12; i++)
            all += month[i];
        if (all > 0)
            printf("%d\n", all);
        else
            printf("Deficit\n");
    }
    return 0;
}
