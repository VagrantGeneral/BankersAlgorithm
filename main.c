#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#if 1

static int x;//���巵�ص�״̬��

typedef struct {

	char name[10];//������
	char finish[10];//����״̬

}process;//����һ���ṹ�壬����������ͽ���״̬


//����Ƿ��Ѿ��������ݣ�
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
		printf("          δ��������,��ѡ����'1'�������ݣ�\n");
		x = -1;
	}
	else { x = 1; }
}

//���ð�ȫ���㷨��Ϊ3�ŷ�װ��
void  ASAalone(int m, int n, int M[][10], int Al[][10], int Av[10], process pc[]) {
	int max[10][10];//��������������
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
		printf("          δ�������ݣ����޷����õ������ð�ȫ���㷨��\n");
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
					printf("          �����д��󣬽���  %s  ����������Դ����С���Ѿ��������Դ������������NeedС��0��\n", mistake[j].name);
					number++;
					break;
				}
			}
		}
		if (number != 0) {
			printf("          �������������ݣ�\n");
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
			printf("          ϵͳΪ��ȫ״̬����ȫ����Ϊ��   ");
			for (int i = 0; i < kk; i++) {
				printf("  %s   ", Aquene[i].name);
			}
			printf("\n");
			printf("\n");
			printf("������     MAX��Դ     Allocation��Դ       Need��Դ     Available��Դ\n");
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
			printf("          ϵͳΪ����ȫ״̬!\n");
		}
	}
}

//��ȫ���㷨
int  ASA(int m, int n, int M[][10], int Al[][10], int Av[10], process pc[], int Re[], int f) {
	int max[10][10];   //�������
	int Need[10][10];   //�����������Դ
	int Alloction[10][10]; //�ѷ������Դ
	int Requst[10];    //������Դ
	int work[10];//ϵͳ�����ṩ�ĸ�����Դ��Դ��  ��Available��ͬ
	process Aquene[10];  //��ȫ����
	process mistake[10];   //
	int num = 0, number = 0;
	int k = 0;
	
	//�жϽ��̵�ǰ��״̬
	if (strcmp(pc[f].finish, "AAA") == 0) {
		printf("         ����%s�Ѿ����ͷţ�\n", pc[f].name);
		return -9;
	}

	for (int i = 0; i < m; i++) {
		if (strcmp(pc[i].finish, "AAA") == 0) {
			continue;
		}
		strcpy(pc[i].finish, "flase");
	}

	//�������о���
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			max[i][j] = M[i][j];
			Alloction[i][j] = Al[i][j];
			Need[i][j] = max[i][j] - Alloction[i][j];
			Requst[j] = Re[j];
			work[j] = Av[j];
		}
	}

	//���**************************��Max �� Allocation�� ��ϵ����Need��************************
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			//�Խ��� �������������Դ�� ���� ���м��
			if (Need[i][j] < 0) {
				mistake[number] = pc[i];//������������б�
				number++;//
				break;
			}
		}
	}

	//1.��Need������ȷ��ǰ�����ж�
	if (number == 0) {
		int H = 0;
		int P = 0;

		//***************************�ж� Need �� Requst �Ĺ�ϵ**************************
		for (int i = 0; i < n; i++) {
			if ((Need[f][i] >= Requst[i])) {
				H++;
			}
			else {
				printf("          �������Դ���������������Դ��������Need<Requst����Դ��ƥ�䣡\n");
				break;
			}
		}

		//2.���� ���̵�ÿ������ ȫ�� <= Need ʱ
		if (H == n) {

			//�ж���Դ���� �Ƿ�С�ڵ��� ϵͳ������Դ
			for (int i = 0; i < n; i++) {
				if (work[i] >= Requst[i]) {
					P++;
				}
			}
		}
		else { 
			return 3;
		}

		//3.���� ���̵�ÿ������ ȫ�� <= ϵͳ������Դ ʱ
		if (P == n) {

			//���Է�����Դ����������
			for (int i = 0; i < m; i++) {
				work[i] = work[i] - Requst[i];
				Alloction[f][i] = Alloction[f][i] + Requst[i];
				Need[f][i] = max[f][i] - Alloction[f][i];
			}
			//�Ұ�ȫ����
			for (int y = 0; y < m; y++) {
				for (int i = 0; i < m; i++) {
					k = 0;
					for (int j = 0; j < n; j++) {
						//�ж� ���̵�ÿ����Դ �Ƿ񶼱� ϵͳ������Դ ��
						if (Need[i][j] <= work[j]) {
							k++;
						}
					}

					//�ڱ�֤�ɷ��������£�ȥ��ȫΪ0�Ľ���
					if ((k == n) && (strcmp(pc[i].finish, "flase") == 0)) {
						//����
						strcpy(pc[i].finish, "true");
						Aquene[num++] = pc[i];
						for (int m = 0; m < n; m++) {
							work[m] = work[m] + Alloction[i][m];
						}

						break;
					}
				}
			}

			//���и���Ϊ������ʱ ˵��Ϊ��ȫ����
			if (num == m) {
				printf("\n");
				printf("          ϵͳΪ��ȫ״̬����ȫ����Ϊ��   ");
				for (int i = 0; i < m; i++) {
					printf("  %s   ", Aquene[i].name);
				}
				return 0;
			}
			//���򲻰�ȫ
			else {
				printf("          ϵͳΪ����ȫ״̬!\n");
				return -1;
			}
		}
		//������ ������ĵ���Դ <= ϵͳ���е���Դ
		else {
			printf("          ������ĵ���Դ��������ϵͳ���е���Դ�������� Available<Requst���޷����䣡\n");
			return 2;
		}
	}

	//Need��������ȷ
	else {
		for (int j = 0; j < number; j++) {
			printf("          �����д��󣬽��� %s ����������Դ����С���Ѿ��������Դ������\n", mistake[j].name);
		}
		printf("          �������������ݣ�\n");
		return 5;
	}

}


//���м��㷨
void  BankersAlgorithm(int m, int n, int M[][10], int Al[][10], int Av[10], process pc[]) {
	int Requst[10];//���̵�������Դ����
	char name[10];//
	int k, b = 0, mm = 0;

	examine(m, n, M);//�����ݱ�����м��
	if (x == -1) {
		printf("          δ�������ݣ����޷��������м��㷨\n");
	}
	else if (x == 1) {

		printf("          ��������������Դ�Ľ�������");
		scanf("%s", name);

		//����ָ������
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
			printf("          ���޴˽���,���������룺   \n");
		}
		else {
			printf("          �ҵ����̣����������Դ��Ŀ��");
			for (int i = 0; i < n; i++) {
				scanf("%d", &Requst[i]);
			}
			
			//���ð�ȫ���㷨*************************************
			int i = ASA(m, n, M, Al, Av, pc, Requst, k);   

			//ͨ������ֵ�ж��Ƿ�ȫ ���Ҵ�ӡ��Ӧ����
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
					printf("����%s����Ҫ����Դ�����Ѿ��õ�����,��������ͷţ�\n", pc[k].name);
					strcpy(pc[k].finish, "AAA");
					for (int i = 0; i < n; i++) {
						Av[i] = Al[k][i] + Av[i];
					}
				}
				printf("\n");
				printf("������     MAX��Դ     Allocation��Դ       Need��Դ     Available��Դ\n");
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
				printf("          ��Դ����ɹ�!\n");
			}
			else if (i == -1) {
				printf("          ��Դ����ʧ�ܣ�    \n");
				printf("������     MAX��Դ     Allocation��Դ       Need��Դ     Available��Դ\n");
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

//Ŀ¼
void List() {
	printf("--------------------------\n");
	printf("---0.�˳�-----------------\n");
	printf("---1.������̼�������-----\n");
	printf("---2.���м��㷨����-------\n");
	printf("---3.��ȫ���㷨-----------\n");
	printf("---4.�ı����������Դ��---\n");
	printf("--------------------------\n");
}

//���̵���������
void input(process pc[], int m, int n, int M[][10], int Al[][10], int Av[10]) {
	
	//�������飬��������Available����
	int transit[10] = { 0 };       
	printf("����������Դ������  ");
	int MAX[10];
	for (int i = 0; i < n; i++) {
		scanf("%d", &MAX[i]);
	}
	for (int i = 0; i < m; i++) {
		printf("�����������");
		scanf("%s", pc[i].name);
		strcpy(pc[i].finish, "flase");
		printf("     ");
		printf("������MAX��Դ��      ");
		for (int j = 0; j < n; j++) {
			scanf("%d", &M[i][j]);
		}
		printf("     ");
		printf("������Alloction��Դ��");
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
	printf("������     MAX��Դ     Allocation��Դ       Need��Դ     Available��Դ\n");
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
	//printf("������������е���Դ��Ŀ��");
	//	for (int i = 0; i < n; i++)
	//	{
	//		scanf("%d", &Av[i]);
	//	}
}

//ѡ��ģ��
void Choose(int k, int M[][10], int Al[][10], process pc[], int Av[10], int m, int n) {
	switch (k) {
	case 0:
		printf("�˳�����\n");
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
		printf("������Ч�����������룡\n");
		break;
	}
}


int main() {
	int m, n = 0;//����������Դ������
	int k ,l = 0;

	/*
	Need Max Alloction��������������������
	Need[] = Max[] - Alloction[]
	*/

	//����������-----------	���̶Բ�ͬ��Դ�����������
	int max[10][10] = { {7,5,3},
						{3,2,2},
						{9,0,2},
						{2,2,2},
						{4,3,3} 
	};

	//�������---------------���̶�Ӧ�Ĳ�ͬ��Դδ���������					
	int Need[10][10];

	//�ѷ�����Դ����---------	���̶�Ӧ�Ĳ�ͬ��Դ�ѷ��������
	int Alloction[10][10] = {	{0,1,0}, 
								{2,0,0}, 
								{3,0,2},
								{2,1,1},
								{0,0,2} 
	};
	


	//��������Դ����---------ϵͳ�в�ͬ��Դ�ֿ��õ�����
	int Available[10] = { 7,5,3 };

	//�����б�
	process pc[10] = {	{"p0","flase"},
						{"p1","flase"},
						{"p2","flase"},
						{"p3","flase"},
						{"p4","flase"} 
	};   

	printf("��������̸�����    ");
	scanf("%d", &m);
	printf("��������Դ���������    ");
	scanf("%d", &n);
	do {
		List();
		printf("������ѡ��");
		scanf("%d", &k);
		Choose(k, max, Alloction, pc, Available, m, n);
		printf("\n");
		if (k == 4) {
			printf("��������̸�����    ");
			scanf("%d", &m);
			printf("��������Դ���������    ");
			scanf("%d", &n);
			printf("�������޸��˽�����������Դ������ѡ��1���������룡\n");
		}
	} while (k != 0);

	return 0;
}

#endif