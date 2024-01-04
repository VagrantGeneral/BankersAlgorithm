#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#if 1

static int x;//整体返回的状态量

typedef struct {

	char name[10];//进程名
	char finish[10];//进程状态

}process;//定义一个结构体，保存进程名和进程状态


//检测是否已经输入数据！
void examine(int m, int n, int M[][10]) {
	int f = 0;
	int k = 0;
	for (int i = 0; i < m; i++) {
		f = 0;
		for (int j = 0; j < n; j++) {
			if (M[i][j] == 0) {
				f++;
			}
		}
		if (f == n) {
			k++;
		}
	}
	if (k == m) {
		printf("          未输入数据,请选择功能'1'输入数据！\n");
		x = -1;
	}
	else { x = 1; }
}

//调用安全性算法（为3号封装）
void  ASAalone(int m, int n, int M[][10], int Al[][10], int Av[10], process pc[]) {
	int max[10][10];//进程最大需求矩阵
	int Need[10][10];//
	int Alloction[10][10];//
	int work[10];
	process Aquene[10];
	process mistake[10];
	int num = 0, number = 0;
	int i, j;
	int k = 0, mm = 0;
	int kk = m;
	examine(m, n, M);
	if (x == -1) {
		printf("          未输入数据！，无法调用单独调用安全性算法！\n");
	}
	else if (x == 1) {
		for (int i = 0; i < m; i++) {
			if (strcmp(pc[i].finish, "AAA") == 0) {
				kk--;
				continue;
			}
			strcpy(pc[i].finish, "flase");
		}
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				max[i][j] = M[i][j];
				Alloction[i][j] = Al[i][j];
				Need[i][j] = max[i][j] - Alloction[i][j];
				work[j] = Av[j];
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (Need[i][j] < 0) {
					mistake[number] = pc[i];
					printf("          数据有错误，进程  %s  所需的最大资源个数小于已经分配的资源个数，即就是Need小于0！\n", mistake[j].name);
					number++;
					break;
				}
			}
		}
		if (number != 0) {
			printf("          请重新输入数据：\n");
			return;
		}

		for (int y = 0; y < m; y++) {
			for (int i = 0; i < m; i++) {
				k = 0;
				for (int j = 0; j < n; j++) {
					if (Need[i][j] <= work[j]) {
						k++;
					}
				}
				if ((k == n) && (strcmp(pc[i].finish, "flase") == 0)) {
					strcpy(pc[i].finish, "true");
					Aquene[num++] = pc[i];
					for (int m = 0; m < n; m++) {
						work[m] = work[m] + Alloction[i][m];
					}
					break;
				}
			}
		}

		if (num == kk) {
			printf("\n");
			printf("          系统为安全状态，安全序列为：   ");
			for (int i = 0; i < kk; i++) {
				printf("  %s   ", Aquene[i].name);
			}
			printf("\n");
			printf("\n");
			printf("进程名     MAX资源     Allocation资源       Need资源     Available资源\n");
			for (int i = 0; i < m; i++) {
				if (strcmp(pc[i].finish, "AAA") == 0) {
					continue;
				}
				printf("%3s", pc[i].name);
				printf("       ");
				for (int j = 0; j < n; j++) {
					printf("%3d", M[i][j]);
				}
				printf("       ");
				for (int j = 0; j < n; j++) {
					printf("%3d", Al[i][j]);
				}
				printf("       ");
				for (int j = 0; j < n; j++) {
					printf("%3d", M[i][j] - Al[i][j]);
				}
				printf("       ");
				for (int j = 0; j < n; j++) {
					if (i == 0) {
						printf("%3d", Av[j]);
					}
				}
				printf("\n");
			}
		}
		else {
			printf("          系统为不安全状态!\n");
		}
	}
}

//安全性算法
int  ASA(int m, int n, int M[][10], int Al[][10], int Av[10], process pc[], int Re[], int f) {
	int max[10][10];   //最大需求
	int Need[10][10];   //现在仍需的资源
	int Alloction[10][10]; //已分配的资源
	int Requst[10];    //请求资源
	int work[10];//系统可以提供的各类资源资源数  与Available相同
	process Aquene[10];  //安全序列
	process mistake[10];   //
	int num = 0, number = 0;
	int k = 0;
	
	//判断进程当前的状态
	if (strcmp(pc[f].finish, "AAA") == 0) {
		printf("         进程%s已经被释放！\n", pc[f].name);
		return -9;
	}

	for (int i = 0; i < m; i++) {
		if (strcmp(pc[i].finish, "AAA") == 0) {
			continue;
		}
		strcpy(pc[i].finish, "flase");
	}

	//拷贝所有矩阵
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			max[i][j] = M[i][j];
			Alloction[i][j] = Al[i][j];
			Need[i][j] = max[i][j] - Alloction[i][j];
			Requst[j] = Re[j];
			work[j] = Av[j];
		}
	}

	//检错**************************（Max 和 Allocation的 关系，即Need）************************
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			//对进程 现在仍所需的资源数 本身 进行检错
			if (Need[i][j] < 0) {
				mistake[number] = pc[i];//出错后加入错误列表
				number++;//
				break;
			}
		}
	}

	//1.在Need数量正确的前提下判断
	if (number == 0) {
		int H = 0;
		int P = 0;

		//***************************判断 Need 和 Requst 的关系**************************
		for (int i = 0; i < n; i++) {
			if ((Need[f][i] >= Requst[i])) {
				H++;
			}
			else {
				printf("          请求的资源个数大于所需的资源个数，即Need<Requst，资源不匹配！\n");
				break;
			}
		}

		//2.满足 进程的每种请求 全部 <= Need 时
		if (H == n) {

			//判断资源请求 是否小于等于 系统现有资源
			for (int i = 0; i < n; i++) {
				if (work[i] >= Requst[i]) {
					P++;
				}
			}
		}
		else { 
			return 3;
		}

		//3.满足 进程的每种请求 全部 <= 系统现有资源 时
		if (P == n) {

			//尝试分配资源，更改数据
			for (int i = 0; i < m; i++) {
				work[i] = work[i] - Requst[i];
				Alloction[f][i] = Alloction[f][i] + Requst[i];
				Need[f][i] = max[f][i] - Alloction[f][i];
			}
			//找安全序列
			for (int y = 0; y < m; y++) {
				for (int i = 0; i < m; i++) {
					k = 0;
					for (int j = 0; j < n; j++) {
						//判断 进程的每种资源 是否都比 系统可用资源 少
						if (Need[i][j] <= work[j]) {
							k++;
						}
					}

					//在保证可分配的情况下，去除全为0的进程
					if ((k == n) && (strcmp(pc[i].finish, "flase") == 0)) {
						//分配
						strcpy(pc[i].finish, "true");
						Aquene[num++] = pc[i];
						for (int m = 0; m < n; m++) {
							work[m] = work[m] + Alloction[i][m];
						}

						break;
					}
				}
			}

			//序列个数为进程数时 说明为安全序列
			if (num == m) {
				printf("\n");
				printf("          系统为安全状态，安全序列为：   ");
				for (int i = 0; i < m; i++) {
					printf("  %s   ", Aquene[i].name);
				}
				return 0;
			}
			//否则不安全
			else {
				printf("          系统为不安全状态!\n");
				return -1;
			}
		}
		//不满足 所申请的的资源 <= 系统现有的资源
		else {
			printf("          所申请的的资源个数大于系统现有的资源个数，即 Available<Requst，无法分配！\n");
			return 2;
		}
	}

	//Need数量不正确
	else {
		for (int j = 0; j < number; j++) {
			printf("          数据有错误，进程 %s 所需的最大资源个数小于已经分配的资源个数！\n", mistake[j].name);
		}
		printf("          请重新输入数据：\n");
		return 5;
	}

}


//银行家算法
void  BankersAlgorithm(int m, int n, int M[][10], int Al[][10], int Av[10], process pc[]) {
	int Requst[10];//进程的请求资源矩阵
	char name[10];//
	int k, b = 0, mm = 0;

	examine(m, n, M);//对数据本身进行检错
	if (x == -1) {
		printf("          未输入数据！，无法调用银行家算法\n");
	}
	else if (x == 1) {

		printf("          请输入所申请资源的进程名：");
		scanf("%s", name);

		//查找指定进程
		for (int i = 0; i < m; i++) {
			if (strcmp(pc[i].name, name) == 0) {
				k = i;
				break;
			}
			else {
				b++;
			}
		}

		if (b == m) {
			printf("          查无此进程,请重新输入：   \n");
		}
		else {
			printf("          找到进程，所申请的资源数目：");
			for (int i = 0; i < n; i++) {
				scanf("%d", &Requst[i]);
			}
			
			//调用安全性算法*************************************
			int i = ASA(m, n, M, Al, Av, pc, Requst, k);   

			//通过返回值判断是否安全 并且打印相应内容
			if (i == 0) {
				for (int i = 0; i < n; i++) {
					Al[k][i] = Al[k][i] + Requst[i];
					Av[i] = Av[i] - Requst[i];
				}
				for (int i = 0; i < n; i++) {
					if (Al[k][i] == M[k][i]) {
						mm++;
					}
				}
				printf("\n");
				if (mm == n) {
					printf("进程%s所需要的资源个数已经得到满足,对其进行释放！\n", pc[k].name);
					strcpy(pc[k].finish, "AAA");
					for (int i = 0; i < n; i++) {
						Av[i] = Al[k][i] + Av[i];
					}
				}
				printf("\n");
				printf("进程名     MAX资源     Allocation资源       Need资源     Available资源\n");
				for (int i = 0; i < m; i++) {
					if (i == k)
					{
						continue;
					}
					printf("%3s", pc[i].name);
					printf("       ");
					for (int j = 0; j < n; j++) {
						printf("%3d", M[i][j]);
					}
					printf("       ");
					for (int j = 0; j < n; j++) {
						printf("%3d", Al[i][j]);
					}
					printf("       ");
					for (int j = 0; j < n; j++) {
						printf("%3d", M[i][j] - Al[i][j]);
					}
					printf("       ");
					for (int j = 0; j < n; j++) {
						if (i == 0) {
							printf("%3d", Av[j]);
						}
					}
					printf("\n");
				}
				printf("\n");
				printf("          资源分配成功!\n");
			}
			else if (i == -1) {
				printf("          资源分配失败！    \n");
				printf("进程名     MAX资源     Allocation资源       Need资源     Available资源\n");
				for (int i = 0; i < m; i++) {
					printf("%3s", pc[i].name);
					printf("       ");
					for (int j = 0; j < n; j++) {
						printf("%3d", M[i][j]);
					}
					printf("       ");
					for (int j = 0; j < n; j++) {
						printf("%3d", Al[i][j]);
					}
					printf("       ");
					for (int j = 0; j < n; j++) {
						printf("%3d", M[i][j] - Al[i][j]);
					}
					printf("       ");
					for (int j = 0; j < n; j++) {
						if (i == 0) {
							printf("%3d", Av[j]);
						}
					}
					printf("\n");
				}
			}
		}
	}
}

//目录
void List() {
	printf("--------------------------\n");
	printf("---0.退出-----------------\n");
	printf("---1.输入进程及其数据-----\n");
	printf("---2.银行家算法调用-------\n");
	printf("---3.安全性算法-----------\n");
	printf("---4.改变进程数及资源数---\n");
	printf("--------------------------\n");
}

//进程的数据输入
void input(process pc[], int m, int n, int M[][10], int Al[][10], int Av[10]) {
	
	//过渡数组，用来计算Available数组
	int transit[10] = { 0 };       
	printf("请输入总资源个数：  ");
	int MAX[10];
	for (int i = 0; i < n; i++) {
		scanf("%d", &MAX[i]);
	}
	for (int i = 0; i < m; i++) {
		printf("请输入进程名");
		scanf("%s", pc[i].name);
		strcpy(pc[i].finish, "flase");
		printf("     ");
		printf("请输入MAX资源：      ");
		for (int j = 0; j < n; j++) {
			scanf("%d", &M[i][j]);
		}
		printf("     ");
		printf("请输入Alloction资源：");
		for (int j = 0; j < n; j++) {
			scanf("%4d", &Al[i][j]);
		}
	}
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			transit[j] = transit[j] + Al[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		Av[i] = MAX[i] - transit[i];
	}
	printf("进程名     MAX资源     Allocation资源       Need资源     Available资源\n");
	for (int i = 0; i < m; i++) {
		printf("%3s", pc[i].name);
		printf("       ");
		for (int j = 0; j < n; j++) {
			printf("%3d", M[i][j]);
		}
		printf("       ");
		for (int j = 0; j < n; j++) {
			printf("%3d", Al[i][j]);
		}
		printf("       ");
		for (int j = 0; j < n; j++) {
			printf("%3d", M[i][j] - Al[i][j]);
		}
		printf("       ");
		for (int j = 0; j < n; j++) {
			if (i == 0) {
				printf("%3d", Av[j]);
			}
		}
		printf("\n");
	}
	//printf("请输入程序现有的资源数目：");
	//	for (int i = 0; i < n; i++)
	//	{
	//		scanf("%d", &Av[i]);
	//	}
}

//选择模块
void Choose(int k, int M[][10], int Al[][10], process pc[], int Av[10], int m, int n) {
	switch (k) {
	case 0:
		printf("退出程序！\n");
		break;
	case 1:
		input(pc, m, n, M, Al, Av);
		break;
	case 2:
		BankersAlgorithm(m, n, M, Al, Av, pc);
		break;
	case 3:
		ASAalone(m, n, M, Al, Av, pc);
		break;
	case 4:
		break;
	default:
		printf("输入无效，请重新输入！\n");
		break;
	}
}


int main() {
	int m, n = 0;//进程数和资源种类数
	int k ,l = 0;

	/*
	Need Max Alloction三个矩阵满足以下条件
	Need[] = Max[] - Alloction[]
	*/

	//最大需求矩阵-----------	进程对不同资源的最大需求数
	int max[10][10] = { {7,5,3},
						{3,2,2},
						{9,0,2},
						{2,2,2},
						{4,3,3} 
	};

	//需求矩阵---------------进程对应的不同资源未分配的数量					
	int Need[10][10];

	//已分配资源矩阵---------	进程对应的不同资源已分配的数量
	int Alloction[10][10] = {	{0,1,0}, 
								{2,0,0}, 
								{3,0,2},
								{2,1,1},
								{0,0,2} 
	};
	


	//可利用资源矩阵---------系统中不同资源现可用的数量
	int Available[10] = { 7,5,3 };

	//进程列表
	process pc[10] = {	{"p0","flase"},
						{"p1","flase"},
						{"p2","flase"},
						{"p3","flase"},
						{"p4","flase"} 
	};   

	printf("请输入进程个数：    ");
	scanf("%d", &m);
	printf("请输入资源种类个数：    ");
	scanf("%d", &n);
	do {
		List();
		printf("请输入选择：");
		scanf("%d", &k);
		Choose(k, max, Alloction, pc, Available, m, n);
		printf("\n");
		if (k == 4) {
			printf("请输入进程个数：    ");
			scanf("%d", &m);
			printf("请输入资源种类个数：    ");
			scanf("%d", &n);
			printf("由于你修改了进程数及其资源数，请选择‘1’重新输入！\n");
		}
	} while (k != 0);

	return 0;
}

#endif