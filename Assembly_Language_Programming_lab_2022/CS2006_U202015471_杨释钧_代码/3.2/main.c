#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#pragma pack(1)
typedef struct S
{
	char SAMID[9];
	int SA;
	int SB;
	int SC;
	int SF;
}S;
#pragma pack()
int lownum;
int f;
int midnum;
int highnum;
S LOWF[7];
S MIDF[7];
S HIGHF[7];
S INIT[7] = {
	[0] = {
		.SAMID = "00000000",
		.SA = 2539,
		.SB = 6,
		.SC = 1,
		.SF = 0
},
	[1] = {
		.SAMID = "00000001",
		.SA = 2539,
		.SB = 6,
		.SC = 1,
		.SF = 0
},
	[2] = {
		.SAMID = "00000002",
		.SA = 2540,
		.SB = 1,
		.SC = 1,
		.SF = 0
},
	[3] = {
		.SAMID = "00000003",
		.SA = 2540,
		.SB = 1000,
		.SC = 1,
		.SF = 0
},
	[4] = {
		.SAMID = "00000004",
		.SA = 2540,
		.SB = 44,
		.SC = 44,
		.SF = 0
},
	[5] = {
		.SAMID = "00000005",
		.SA = 2540,
		.SB = 666,
		.SC = 666,
		.SF = 0
},
	[6] = {
		.SAMID = "00000006",
		.SA = 5,
		.SB = 4,
		.SC = 1,
		.SF = 0
},
};
const char username[4] = "ysj";
const char password[7] = "123456";
void func1();
void func3();
void func4();
extern void Scopy(S*, S*);
extern void func(S*);
int main()
{
	func1();
	func4();
}
void func1()
{
	char input[20];
	int flag=0;
	for (int i = 0; i < 3; i++)
	{
		printf("Please input the username\n");
		scanf("%s", input);
		int j;
		flag = 0;
		for (j = 0; input[j] != 0 && username[j] != 0; j++)
		{
			if (input[j] != username[j])
			{
				flag = 1;
				break;
			}
		}
		if (flag==0)
		{
			printf("OK!\n");
			for (int j = 0; j < 3; j++)
			{
				printf("Please input your password\n");
				scanf("%s", input);
				int k;
				flag = 0;
				for (k = 0; input[k] != 0 && password[k] != 0; k++)
				{
					if (input[k] != password[k])
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					printf("OK\n");
					break;
				}
				else
				{
					printf("ERROR\n");
				}
			}
			break;
		}
		printf("ERROR!\n");
	}
	if (flag == 1)
	{
		exit(0);
	}
}
void func3()
{
	for (int i = 0; i < midnum; i++)
	{
		printf("ID:%s\n", MIDF[i].SAMID);
		printf("a:%d\n", MIDF[i].SA);
		printf("b:%d\n", MIDF[i].SB);
		printf("c:%d\n", MIDF[i].SC);
	}
}
void func4()
{
	do
	{
		lownum = 0;
		midnum = 0;
		highnum = 0;
		//a = 0;
		f = 0;
		for (int i = 0; i < 7; i++)
		{
			func(&INIT[i]);
			if (INIT[i].SF < 100)
				Scopy(&LOWF[lownum++], &INIT[i]);
			else if (INIT[i].SF > 100)
				Scopy(&HIGHF[highnum++], &INIT[i]);
			else
				Scopy(&MIDF[midnum++], &INIT[i]);
		}
		func3();
		printf("please input R/M/Q\n");
		getchar();
		char c = getchar();
		getchar();
		if (c == 'R')
			continue;
		if (c == 'Q')
			break;
		if (c == 'M')
		{
			S temp;
			printf("SAMID:\n");
			scanf_s("%s", temp.SAMID, 8);
			printf("SA:\n");
			scanf_s("%d", &temp.SA);
			printf("SB:\n");
			scanf_s("%d", &temp.SB);
			printf("SC:\n");
			scanf_s("%d", &temp.SC);
			temp.SF = 0;
			Scopy(&INIT[0], &temp);
			continue;
		}
	} while (1);
}