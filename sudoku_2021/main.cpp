#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TRUE 1         //真值设为1
#define FALSE 0        //假值设为0
#define OK 1           //预处理定义
#define ERROR 0        //定义ERROR
#define INFEASTABLE -1 //定义报错
#define OVERFLOW -2    //定义溢出
int boolnum;
int flagflag;
int clausnum, firstdelx, firstdely;
int *firstline;
int shift[10] = {0, 3, 6, 1, 4, 7, 2, 5, 8};
typedef struct _charanode
{
    int data;
    struct _charanode *next;
} charanode;
typedef struct _cnf
{
    //int length;
    charanode *head;
    struct _cnf *next;
} cnf;
int readCNF(cnf *&CNF, char Filename[80]); //读取CNF文件
void deleteCNF(cnf *&CNF);
void showCNF(cnf *CNF); //逐行打印CNF范式
int isOneClause(charanode *chara);
int deleteClause(cnf *&CNF, cnf *&deleted);
int deletechara(charanode *&head, charanode *&CNF);
int iswithEmptyClause(cnf *CNF);
int betterDPLL(cnf *&CNF, int value[]);
void addClause(cnf *CNF, cnf *&root);
void copyclause(cnf *&CNF, cnf *CNF2);
int savedata(int value[], char Filename[], double time, int result);
void createsudoku(int sudoku[][9]);
void dfs();
int solveSudoku(int sudoku[][9]);
void dighole(int sudoku[][9], int n);
int check(int sudoku[][9], int x, int y);
int DPLL(cnf *&CNF, int value[]);
int main()
{
    cnf *CNF = NULL;
    int sudoku[9][9];
    int sudoku1[9][9];
    int opt = 1, opt1 = 1, opt2 = 1;
    int *value;
    clock_t start, finish;
    char Filename[80];
    while (opt)
    {
        // system("cls");
        opt1 = 1, opt2 = 1;
        printf("\n\n");
        printf("                    Menu Of options   \n");
        printf("-----------------------------------------------------\n");
        printf("             1. SAT              2. Sudoku           \n");
        printf("                      0. exit\n");
        printf("---------------------------------------------------- \n");
        printf("Please input your option[0-2]\n");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
        {
            while (opt1)
            {
                system("cls");
                printf("\n\n");
                printf("                   Menu of SAT      \n");
                printf("-------------------------------------------------\n");
                printf("          1. ReadCNF        2. ShowCNF           \n");
                printf("          3. BetterDPLL           4. DPLL        \n");
                printf("                      0. exit    \n");
                printf("Please input your option[0-4]");
                scanf("%d", &opt1);
                switch (opt1)
                {
                case 1:
                {
                    printf("Please input the path of the CNF file\n");
                    scanf("%s", Filename);
                    int ret = readCNF(CNF, Filename);
                    if (ret == 0)
                        printf("the path of file is error!\n");
                    else
                        printf("read the data from the CNF file successfully\n");
                    getchar();
                    getchar();
                    break;
                } // end of case1 in sat
                case 2:
                {
                    if (CNF == NULL)
                    {
                        printf("Please read the data first!\n");
                    }
                    else
                    {
                        printf("the clause in this file is as follows:\n");
                        showCNF(CNF);
                    }
                    getchar();
                    getchar();
                    break;
                } // end of case2 in sat
                case 3:
                {
                    if (CNF == NULL)
                    {
                        printf("Please read the data first!\n");
                    }
                    else
                    {
                        value = (int *)malloc(sizeof(int) * (boolnum + 1));
                        for (int i = 1; i <= boolnum; i++)
                            value[i] = 1;
                        start = clock();
                        int result = betterDPLL(CNF, value);
                        finish = clock();
                        printf("result: %d\n", result);
                        if (result)
                        {
                            printf("the answer is as follows:\n");
                            for (int i = 1; i <= boolnum; i++)
                            {
                                if (value[i])
                                    printf("%d ", i);
                                else
                                    printf("-%d ", i);
                            }
                        }
                        double time = (double)(finish - start) / CLOCKS_PER_SEC;
                        printf("\nruntime:%lf\n", time * 1000);
                        savedata(value, Filename, time, result);
                        printf("This file is saved with the same name of CNF\n");
                    }
                    getchar();
                    getchar();
                    break;
                } // end of case3 in sat
                case 4:
                {
                    if (CNF == NULL)
                    {
                        printf("Please read the data first\n");
                    }
                    else
                    {
                        value = (int *)malloc(sizeof(int) * (boolnum + 1));
                        for (int i = 1; i <= boolnum; i++)
                            value[i] = 1;
                        int result;
                        start = clock();
                        result = DPLL(CNF, value);
                        finish = clock();
                        printf("result: %d\n", result);
                        if (result)
                        {
                            printf("the answer is as follows:\n");
                            for (int i = 1; i <= boolnum; i++)
                            {
                                if (value[i])
                                    printf("%d ", i);
                                else
                                    printf("-%d ", i);
                            }
                        }
                        double time = (double)(finish - start) / CLOCKS_PER_SEC;
                        printf("\nruntime:%lf\n", time * 1000);
                        savedata(value, Filename, time, result);
                        printf("This file is saved with the same name of CNF\n");
                    }
                    getchar();
                    getchar();
                    break;
                } // end of case4 in sat
                case 0:
                {
                    break;
                } // end of case0 in sat
                } // end of the sat switch
            }     // end of the sat while
            break;
        } // end of case 1
        case 2:
        {
            while (opt2)
            {
                system("cls");
                printf("\n\n");
                printf("                Menu of sudoku\n");
                printf("------------------------------------------\n");
                printf("        1. CreateSudoku          2. PlaySudoku\n");
                printf("        3. SaveAns               0. exit\n");
                printf("----------------------------------------------\n");
                printf("\n\n");
                printf("Please input your option[0-3]");
                scanf("%d", &opt2);
                switch (opt2)
                {
                case 1:
                {
                    createsudoku(sudoku);
                    flagflag = 1;
                    printf("The sudoku chess is created successfully!\n");
                    printf("The whole chess is as follows:\n");
                    for (int i = 0; i < 9; i++)
                    {
                        for (int j = 0; j < 9; j++)
                            printf("%d ", sudoku[i][j]);
                        printf("\n");
                    }
                    for (int i = 0; i < 9; i++)
                        for (int j = 0; j < 9; j++)
                            sudoku1[i][j] = sudoku[i][j];
                    getchar();
                    getchar();
                    break;
                } //end of case 1 in sudoku
                case 2:
                {
                    if(flagflag){
                    int opt3 = 1;
                    int termsudoku[9][9];
                    for (int i = 0; i < 9; i++)
                        for (int j = 0; j < 9; j++)
                            termsudoku[i][j] = sudoku[i][j];
                    while (opt3)
                    {
                        system("cls");
                        printf("            Lets play the sudoku!\n");
                        printf("---------------------------------------------\n");
                        printf("       1. Add a num   2. Delete a num\n");
                        printf("               0. input answers\n");
                        printf("--------------------------------------------\n");
                        printf("Please input your options[0-2]\n");
                        scanf("%d", &opt3);
                        switch (opt3)
                        {
                        case 1:
                        {
                            for (int i = 0; i < 9; i++)
                            {
                                for (int j = 0; j < 9; j++)
                                    printf("%d ", termsudoku[i][j]);
                                printf("\n");
                            }
                            printf("Please input the position\n");
                            int x, y;
                            scanf("%d%d", &x, &y);
                            x--, y--;
                            printf("Please input the num\n");
                            int data;
                            scanf("%d", &data);
                            if (x >= 0 && x <= 8 && y >= 0 && y <= 8 && data >= 1 && data <= 9)
                            {
                                if (termsudoku[x][y] != 0)
                                    continue;
                                else
                                    termsudoku[x][y] = data;
                            }
                            else
                            {
                                printf("The input is error!\n");
                                printf("Please input again!\n");
                                continue;
                            }
                            getchar();
                            getchar();
                            break;
                        }
                        case 2:
                        {
                            for (int i = 0; i < 9; i++)
                            {
                                for (int j = 0; j < 9; j++)
                                    printf("%d ", termsudoku[i][j]);
                                printf("\n");
                            }
                            printf("Please input the position\n");
                            int x, y;
                            scanf("%d%d", &x, &y);
                            x--, y--;
                            if (x >= 0 && x <= 8 && y >= 0 && y <= 8)
                            {
                                if (termsudoku[x][y] == 0)
                                    continue;
                                termsudoku[x][y] = 0;
                            }
                            else
                            {
                                printf("The input is error!\n");
                                printf("Please input again!\n");
                                continue;
                            }
                            getchar();
                            getchar();
                            break;
                        }
                        case 0:
                        {
                            printf("the answer are as follows\n");
                            if (solveSudoku(sudoku))
                            {
                                for (int i = 0; i < 9; i++)
                                {
                                    for (int j = 0; j < 9; j++)
                                        printf("%d ", sudoku[i][j]);
                                    printf("\n");
                                }
                            }
                            getchar();
                            getchar();
                            break;
                        }
                        }
                    }}
                    else
                    {
                        printf("Please create a sudoku!\n");
                    }
                    getchar();
                    getchar();
                    break;
                }
                case 3:
                {
                    if(flagflag){
                    printf("Please input the path\n");
                    char filename[80];
                    FILE *fp;
                    scanf("%s", filename);
                    fp = fopen(filename, "w");
                    if (fp == NULL)
                    {
                        printf("ERROR!\n");
                        break;
                    }
                    fprintf(fp, "questions:\n");
                    for (int i = 0; i < 9; i++)
                    {
                        for (int j = 0; j < 9; j++)
                            fprintf(fp, "%d ", sudoku1[i][j]);
                        fprintf(fp, "\n");
                    }
                    if (solveSudoku(sudoku))
                    {
                        fprintf(fp, "answer:\n");
                        for (int i = 0; i < 9; i++)
                        {
                            for (int j = 0; j < 9; j++)
                                fprintf(fp, "%d ", sudoku[i][j]);
                            fprintf(fp, "\n");
                        }
                        fclose(fp);
                    }
                    else
                    {
                        fprintf(fp, "No answer!\n");
                        fclose(fp);
                    }
                    flagflag = 0;
                    }
                    else
                    {
                        printf("Please create a sudoku!\n");
                    }
                    getchar();
                    getchar();
                    break;
                }
                case 0:
                {
                    printf("Welcome to play again!\n");
                    getchar();
                    getchar();
                    break;
                }
                }
            }
            break;
        }
        case 0:
        {
            printf("welcome to this system next time!\n");
            break;
        }
        } // end of switch
    }     // end of while
}
int readCNF(cnf *&CNF, char Filename[80]) //读入CNF文件，存入数据结构
{
    FILE *fp;
    fp = fopen(Filename, "r");
    if (fp == NULL)
    {
        return 0;
    }
    char c;
    fscanf(fp, "%c", &c);
    while (c == 'c')
    {
        while (c != '\n' && c != '\r')
            fscanf(fp, "%c", &c);
        fscanf(fp, "%c", &c);
        if (c == '\n')
            fscanf(fp, "%c", &c);
    }
    fscanf(fp, " cnf ");
    fscanf(fp, "%d", &boolnum);
    fscanf(fp, "%d", &clausnum);
    CNF = (cnf *)malloc(sizeof(cnf));
    CNF->next = NULL;
    CNF->head = (charanode *)malloc(sizeof(charanode));
    CNF->head->next = NULL;
    cnf *tailcnf = CNF;
    charanode *tailbool = CNF->head;
    int key;
    for (int i = 0; i < clausnum; i++)
    {
        fscanf(fp, "%d", &key);
        while (key != 0)
        {
            //tailcnf->length++;
            tailbool->data = key;
            tailbool->next = (charanode *)malloc(sizeof(charanode));
            fscanf(fp, "%d", &key);
            if (key == 0)
                tailbool->next = NULL;
            tailbool = tailbool->next;
        }
        tailcnf->next = (cnf *)malloc(sizeof(cnf));
        //tailcnf->next->length = 0;
        tailcnf->next->head = (charanode *)malloc(sizeof(charanode));
        if (i == clausnum - 1)
        {
            tailcnf->next = NULL;
            break;
        }
        tailcnf = tailcnf->next;
        tailbool = tailcnf->head;
    }
    fclose(fp);
    return 1;
}
void showCNF(cnf *CNF) //遍历整个邻接表，逐行打印CNF范式
{
    cnf *p = CNF;
    for (int i = 1; i <= clausnum; i++)
    {
        charanode *q = p->head;
        while (q)
        {
            printf("%d ", q->data);
            q = q->next;
        }
        printf("\n");
        p = p->next;
    }
}
int isOneClause(charanode *chara) //判断该子句是否为单子句
{
    if (chara != NULL && chara->next == NULL)
        return 1;
    return 0;
}
int deleteClause(cnf *&CNF, cnf *&deleted) //删除邻接表中的deleted子句
{
    cnf *p = CNF;
    if (deleted == p) //是否为第一个
    {
        CNF = CNF->next; //直接指向下一个
        free(deleted);   //释放内存
        deleted = NULL;
        return 1;
    }
    else //如果不是第一个
    {
        while (p && p->next != deleted)
            p = p->next;
        p->next = p->next->next;
        free(deleted);
        deleted = NULL;
        return 1;
    }
    return 0;
}
int deletechara(charanode *&head, charanode *&deleted) //删除当前子句中的某个文字
{
    charanode *p = head;
    if (p == deleted)
    {
        head = head->next;
        free(deleted);
        deleted = NULL;
        return 1;
    }
    else
    {
        while (p != NULL && p->next != deleted)
            p = p->next;
        p->next = p->next->next;
        free(deleted);
        deleted = NULL;
        return 1;
    }
    return 0;
}
int iswithEmptyClause(cnf *CNF) //判断其是否含有空子句
{
    cnf *p = CNF;
    while (p != NULL)
    {
        if (p->head == NULL)
            return 1;
        p = p->next;
    }
    return 0;
}
void copyclause(cnf *&CNF, cnf *CNF2) //该函数将CNF2的值赋到CNF
{
    cnf *cocnf, *cocnf2;
    charanode *boolnode1, *boolnode2;
    CNF = (cnf *)malloc(sizeof(cnf));
    CNF->head = (charanode *)malloc(sizeof(charanode));
    CNF->next = NULL;
    CNF->head->next = NULL; //初始化当前的CNF范式
    for (cocnf = CNF, cocnf2 = CNF2; cocnf2; cocnf2 = cocnf2->next, cocnf = cocnf->next)
    { //逐行遍历邻接表进行复制
        for (boolnode1 = cocnf->head, boolnode2 = cocnf2->head; boolnode2; boolnode1 = boolnode1->next, boolnode2 = boolnode2->next)
        {
            boolnode1->data = boolnode2->data;
            boolnode1->next = (charanode *)malloc(sizeof(charanode));
            boolnode1->next->next = NULL;
            if (boolnode2->next == NULL) //特判一下，到达最后的话就进行处理
            {
                free(boolnode1->next);
                boolnode1->next = NULL;
            }
        }
        cocnf->next = (cnf *)malloc(sizeof(cnf)); //处理新的CNF范式
        cocnf->next->head = (charanode *)malloc(sizeof(charanode));
        cocnf->next->head->next = NULL;
        cocnf->next->next = NULL;
        if (cocnf2->next == NULL) //同样的特判
        {
            free(cocnf->next->head);
            free(cocnf->next);
            cocnf->next = NULL;
        }
    }
}
int betterDPLL(cnf *&CNF, int value[]) //用优化后的DPLL算法求解sat问题
{
    cnf *p, *q, *r;
    p = CNF, q = CNF;
    charanode *boolnode;
    int *num, max, maxpos; //num数组用来存储变元的出现次数
    while (p != NULL)
    {
        while (p && isOneClause(p->head) == 0)
            p = p->next;
        if (p)
        {
            int singlekey = p->head->data;
            if (singlekey > 0)
                value[singlekey] = 1;
            else
                value[-singlekey] = 0;
            for (q = CNF; q; q = r)
            {
                r = q->next;
                for (boolnode = q->head; boolnode; boolnode = boolnode->next)
                {
                    if (boolnode->data == singlekey)
                    {
                        deleteClause(CNF, q);
                        break;
                    }
                    if (boolnode->data == -singlekey)
                    {
                        deletechara(q->head, boolnode);
                        break;
                    }
                }
            }
            if (CNF == NULL)
            {
                return 1;
            }
            else if (iswithEmptyClause(CNF))
            {
                deleteCNF(CNF);
                return 0;
            }
            p = CNF;
        }
    }
    num = (int *)malloc(sizeof(int) * (2 * boolnum + 2));
    for (int i = 0; i <= 2 * boolnum; i++)
        num[i] = 0;
    for (p = CNF; p; p = p->next)
    {
        for (boolnode = p->head; boolnode; boolnode = boolnode->next)
            if (boolnode->data > 0)
                num[boolnode->data]++;
            else
                num[boolnum - boolnode->data]++;
    }
    max = 0;
    maxpos = 0;
    for (int i = 1; i <= boolnum; i++)
    {
        if (max < num[i])
        {
            max = num[i];
            maxpos = i;
        }
    }
    if (max == 0)
        for (int i = boolnum + 1; i <= 2 * boolnum; i++)
        {
            if (max < num[i])
            {
                max = num[i];
                maxpos = -i;
            }
        }
    free(num);
    p = (cnf *)malloc(sizeof(cnf));
    p->head = (charanode *)malloc(sizeof(charanode));
    p->head->data = maxpos;
    p->head->next = NULL;
    p->next = NULL;
    q = NULL;
    copyclause(q, CNF);
    if (p != NULL)
    {
        p->next = q;
        q = p;
    }
    if (betterDPLL(q, value) == 1)
        return 1;
    deleteCNF(q);
    p = (cnf *)malloc(sizeof(cnf));
    p->head = (charanode *)malloc(sizeof(charanode));
    p->head->data = -maxpos;
    p->head->next = NULL;
    p->next = NULL;
    if (p != NULL)
    {
        p->next = CNF;
        CNF = p;
    }
    int i = betterDPLL(CNF, value);
    deleteCNF(CNF);
    return i;
}
void deleteCNF(cnf *&CNF)
{
    cnf *p1, *p2;
    charanode *q1, *q2;
    for (p1 = CNF; p1 != NULL; p1 = p2)
    {
        p2 = p1->next;
        for (q1 = p1->head; q1 != NULL; q1 = q2)
        {
            q2 = q1->next;
            free(q1);
        }
        free(p1);
    }
    CNF = NULL;
}
int savedata(int value[], char Filename[], double time, int result)
{
    FILE *fp;
    for (int i = 0; Filename[i] != '\0'; i++)
    {
        if (Filename[i] == '.' && Filename[i + 4] == '\0')
        {
            Filename[i + 1] = 'r';
            Filename[i + 2] = 'e';
            Filename[i + 3] = 's';
            break;
        }
    }
    fp = fopen(Filename, "w");
    if (fp == NULL)
    {
        printf("can't open this file!\n");
        return 0;
    }
    fprintf(fp, "s %d\nv ", result);
    if (result == 1)
    {
        for (int i = 1; i <= boolnum; i++)
        {
            if (value[i])
                fprintf(fp, "%d ", i);
            else
                fprintf(fp, "-%d ", i);
        }
    }
    fprintf(fp, "\nt %lf", time * 1000);
    fclose(fp);
    return 1;
}
//求解sat问题的函数就到此结束了
//下面是求解数独游戏的函数
void createsudoku(int sudoku[][9])
{
    firstline = (int *)malloc(sizeof(int) * 10);
    dfs(); //生成第一行的一个随机全排列
    memcpy(sudoku[0], firstline, sizeof(int) * 9);
    for (int i = 1; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudoku[i][j] = firstline[(j + shift[i]) % 9];
            //通过轮换来得到一个数独
        }
    }
    free(firstline);
    firstline = NULL;
    int n;
    printf("Please enter the difficulty you want(my advice: 40~50)\n");
    scanf("%d", &n);
    dighole(sudoku, n);
}
void dfs()
{
    int a[10];
    for (int i = 1; i <= 9; i++)
        a[i] = i;
    int n = 9;
    int top = 0;
    srand((int)time(0));
    for (int i = 1; i <= 9; i++)
    {
        int x = 1 + rand() % n;
        firstline[top++] = a[x];
        int temp = a[x];
        a[x] = a[n];
        a[n] = temp;
        n--;
    }
    return;
}
//下面的函数调用DPLL算法求解数独游戏
int solveSudoku(int sudoku[][9])
{
    cnf *Sudoku = NULL, *clausep = NULL;
    charanode *BoolNode = NULL;
    int size = 9, size2 = 81;
    int i, j, k;
    //下面的循环加入自身约束
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            clausep = (cnf *)malloc(sizeof(cnf));
            clausep->head = (charanode *)malloc(sizeof(charanode));
            clausep->next = NULL;
            clausep->head->next = NULL;
            BoolNode = clausep->head;
            for (k = 1; k <= size; k++)
            {
                BoolNode->data = i * size2 + j * size + k;
                BoolNode->next = (charanode *)malloc(sizeof(charanode));
                if (k == size)
                {
                    BoolNode->next = NULL;
                    break;
                }
                BoolNode = BoolNode->next;
            }
            addClause(clausep, Sudoku);
            for (k = 1; k <= size; k++)
            {
                for (int t = k + 1; t <= size; t++)
                {
                    clausep = (cnf *)malloc(sizeof(cnf));
                    clausep->head = (charanode *)malloc(sizeof(charanode));
                    clausep->head->data = -(i * size2 + j * size + k);
                    clausep->head->next = (charanode *)malloc(sizeof(charanode));
                    clausep->head->next->data = -(i * size2 + j * size + t);
                    clausep->next = NULL;
                    clausep->head->next->next = NULL;
                    addClause(clausep, Sudoku);
                }
            }
        }
    }
    //下面的循环加入行约束
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            clausep = (cnf *)malloc(sizeof(cnf));
            clausep->head = (charanode *)malloc(sizeof(charanode));
            clausep->head->next = NULL;
            clausep->next = NULL;
            BoolNode = clausep->head;
            for (k = 0; k < size; k++)
            {
                BoolNode->data = i * size2 + k * size + j + 1;
                BoolNode->next = (charanode *)malloc(sizeof(charanode));
                if (k == size - 1)
                {
                    BoolNode->next = NULL;
                    break;
                }
                BoolNode = BoolNode->next;
            }
            addClause(clausep, Sudoku);
        }
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            for (int t = 0; t < size; t++)
                for (k = t + 1; k < size; k++)
                {
                    clausep = (cnf *)malloc(sizeof(cnf));
                    clausep->head = (charanode *)malloc(sizeof(charanode));
                    clausep->head->data = -(i * size2 + t * size + j + 1);
                    clausep->head->next = (charanode *)malloc(sizeof(charanode));
                    clausep->head->next->data = -(i * size2 + k * size + j + 1);
                    clausep->head->next->next = NULL;
                    clausep->next = NULL;
                    addClause(clausep, Sudoku);
                }
        }
    }
    //下面的循环加入列约束
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            clausep = (cnf *)malloc(sizeof(cnf));
            clausep->head = (charanode *)malloc(sizeof(charanode));
            clausep->head->next = NULL;
            clausep->next = NULL;
            BoolNode = clausep->head;
            for (k = 0; k < size; k++)
            {
                BoolNode->data = k * size2 + i * size + j + 1;
                BoolNode->next = (charanode *)malloc(sizeof(charanode));
                if (k == size - 1)
                {
                    BoolNode->next = NULL;
                    break;
                }
                BoolNode = BoolNode->next;
            }
            addClause(clausep, Sudoku);
        }
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            for (int t = 0; t < size; t++)
                for (k = t + 1; k < size; k++)
                {
                    clausep = (cnf *)malloc(sizeof(cnf));
                    clausep->head = (charanode *)malloc(sizeof(charanode));
                    clausep->head->data = -(t * size2 + i * size + j + 1);
                    clausep->head->next = (charanode *)malloc(sizeof(charanode));
                    clausep->head->next->data = -(k * size2 + i * size + j + 1);
                    clausep->head->next->next = NULL;
                    clausep->next = NULL;
                    addClause(clausep, Sudoku);
                }
        }
    }
    //列约束的部分到此结束
    //下面的循环加入3*3约束
    for (k = 0; k < 3; k++)
        for (int t = 0; t < 3; t++)
            for (int count = 1; count <= 9; count++)
            {
                clausep = (cnf *)malloc(sizeof(cnf));
                clausep->head = (charanode *)malloc(sizeof(charanode));
                clausep->head->next = NULL;
                clausep->next = NULL;
                BoolNode = clausep->head;
                for (int i = 3 * k + 1; i <= 3 * k + 3; i++)
                {
                    for (int j = 3 * t + 1; j <= 3 * t + 3; j++)
                    {
                        BoolNode->data = (i - 1) * size2 + (j - 1) * size + count;
                        BoolNode->next = (charanode *)malloc(sizeof(charanode));
                        if (i == 3 * k + 3 && j == 3 * t + 3)
                        {
                            BoolNode->next = NULL;
                            break;
                        }
                        BoolNode = BoolNode->next;
                    }
                }
                addClause(clausep, Sudoku);
            }
    //继续加入3*3约束
    for (k = 0; k < 3; k++)
    {
        for (int t = 0; t < 3; t++)
        {
            for (int count = 1; count <= 9; count++)
            {
                for (int l = 1; l <= 3; l++)
                    for (int y = 1; y <= 3; y++)
                        for (i = 3 * k + l; i <= 3 * k + 3; i++)
                        {
                            for (j = 3 * t + y; j <= 3 * t + 3; j++)
                            {
                                if (i == 3 * k + l && j == 3 * t + y)
                                    continue;
                                clausep = (cnf *)malloc(sizeof(cnf));
                                clausep->head = (charanode *)malloc(sizeof(charanode));
                                clausep->head->data = -((3 * k + l - 1) * size2 + (3 * t + y - 1) * size + count);
                                clausep->head->next = (charanode *)malloc(sizeof(charanode));
                                clausep->head->next->data = -((i - 1) * size2 + (j - 1) * size + count);
                                clausep->next = NULL;
                                clausep->head->next->next = NULL;
                                addClause(clausep, Sudoku);
                            }
                        }
            }
        }
    }
    //下面的循环加入当前所在的数
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (sudoku[i][j] != 0)
            {
                clausep = (cnf *)malloc(sizeof(cnf));
                clausep->head = (charanode *)malloc(sizeof(charanode));
                clausep->head->next = NULL;
                clausep->next = NULL;
                clausep->head->data = i * size2 + j * size + sudoku[i][j];
                addClause(clausep, Sudoku);
            }
        }
    }
    //下面的循环调用DPLL算法来求解sat问题
    int *ans;
    boolnum = 729;
    ans = (int *)malloc(sizeof(int) * 750);
    for (int i = 0; i <= boolnum; i++)
        ans[i] = 1;
    if (betterDPLL(Sudoku, ans))
    {
        for (int i = 1; i <= boolnum; i++)
        {
            if (ans[i] == 1)
            {
                int data = i % 9;
                if (data == 0)
                    data = 9;
                int x, y;
                x = (i - data) / 81;
                y = (i - 81 * x - data) / 9;
                sudoku[x][y] = data;
            }
        }
        free(ans);
        return 1;
    }
    else
    {
        free(ans);
        deleteCNF(Sudoku);
        return 0;
    }
}
void addClause(cnf *CNF, cnf *&root)
{
    if (CNF != NULL)
    {
        CNF->next = root;
        root = CNF;
        return;
    }
}
void dighole(int sudoku[][9], int n)
{
    int count = 0;
    int x, y;
    srand((int)time(0));
    firstdelx = rand() % 9;
    firstdely = rand() % 9;
    sudoku[firstdelx][firstdely] = 0;
    n--;
    while (count < n)
    {
        x = rand() % 9;
        y = rand() % 9;
        if (check(sudoku, x, y))
        {
            sudoku[x][y] = 0;
            count++;
        }
    }
    return;
}
int check(int sudoku[][9], int x, int y)
{

    int termsuduku[9][9];
    for (int i = 1; i <= 9; i++)
    {
        for (int ii = 0; ii < 9; ii++)
            for (int j = 0; j < 9; j++)
                termsuduku[ii][j] = sudoku[ii][j];
        int key = termsuduku[x][y], flag = 0;
        if (i != key)
        {
            for (int j = 0; j < 9; j++)
            {
                if (j == x)
                    continue;
                if (termsuduku[j][y] == i)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                continue;
            flag = 0;
            for (int j = 0; j < 9; j++)
            {
                if (j == y)
                    continue;
                if (termsuduku[x][j] == i)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                continue;
            flag = 0;
            int xx = x / 3, yy = y / 3;
            for (int ii = xx * 3; ii < xx * 3 + 3; ii++)
                for (int jj = yy * 3; jj < yy * 3 + 3; jj++)
                {
                    if (ii == x && jj == y)
                        continue;
                    if (termsuduku[ii][jj] == i)
                    {
                        flag = 1;
                        break;
                    }
                }
            if (flag)
            {
                continue;
            }
            termsuduku[x][y] = i;
            if (solveSudoku(termsuduku))
            {
                return 0;
            }
        }
    }
    return 1;
}
int DPLL(cnf *&CNF, int value[])
{
    cnf *p, *q, *r;
    p = CNF, q = CNF;
    charanode *boolnode;
    int *num, maxpos; //num用来记录各个变元出现的次数
    while (p != NULL)
    {
        while (p && isOneClause(p->head) == 0)
            p = p->next;
        if (p)
        {
            int singlekey = p->head->data;
            if (singlekey > 0)
                value[singlekey] = 1;
            else
                value[-singlekey] = 0;
            for (q = CNF; q; q = r)
            {
                r = q->next;
                for (boolnode = q->head; boolnode; boolnode = boolnode->next)
                {
                    if (boolnode->data == singlekey)
                    {
                        deleteClause(CNF, q);
                        break;
                    }
                    if (boolnode->data == -singlekey)
                    {
                        deletechara(q->head, boolnode);
                        break;
                    }
                }
            }
            if (CNF == NULL)
            {
                return 1;
            }
            else if (iswithEmptyClause(CNF))
            {
                deleteCNF(CNF);
                return 0;
            }
            p = CNF;
        }
    }
    num = (int *)malloc(sizeof(int) * (2 * boolnum + 2));
    for (int i = 0; i <= 2 * boolnum; i++)
        num[i] = 0;
    for (p = CNF; p; p = p->next)
    {
        for (boolnode = p->head; boolnode; boolnode = boolnode->next)
            if (boolnode->data > 0)
                num[boolnode->data]++;
            else
                num[boolnum - boolnode->data]++;
    }
    int max = 0;
    maxpos = 0;
    int ii;
    int max1 = 0, MaxWord1=0;

    //统计正变元出现的次数
    for (ii = 2; ii <= boolnum; ii++)
    {
        if (max1 < num[ii])
        {
            max1 = num[ii];
            MaxWord1 = ii;
        }
    }
    int max2 = 0, MaxWord2=0;
    //统计负变元出现的次数
    for (ii = boolnum + 1; ii <= boolnum * 2; ii++)
    {
        if (max2 < num[ii])
        {
            max2 = num[ii];
            MaxWord2 = -ii + boolnum;
        }
    }
    if (max1 >= max2)
    {
        max = max1;
        maxpos = MaxWord1;
    }
    else
    {
        max = max2;
        maxpos = MaxWord2;
    }

    free(num);
    p = (cnf *)malloc(sizeof(cnf));
    p->head = (charanode *)malloc(sizeof(charanode));
    p->head->data = maxpos;
    p->head->next = NULL;
    p->next = NULL;
    q = NULL;
    copyclause(q, CNF);
    if (p != NULL)
    {
        p->next = q;
        q = p;
    }
    if (DPLL(q, value) == 1)
        return 1;
    deleteCNF(q);
    p = (cnf *)malloc(sizeof(cnf));
    p->head = (charanode *)malloc(sizeof(charanode));
    p->head->data = -maxpos;
    p->head->next = NULL;
    p->next = NULL;
    if (p != NULL)
    {
        p->next = CNF;
        CNF = p;
    }
    int i = DPLL(CNF, value);
    deleteCNF(CNF);
    return i;
}