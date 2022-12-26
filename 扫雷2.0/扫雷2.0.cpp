#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "position.h"
#include <easyx.h>
#include <graphics.h>


#define LONG	10
#define WIDE	10
#define NUM		10
#define SIZE	70


int map[LONG + 2][WIDE + 2];
char game[LONG][WIDE];
IMAGE img[14];


void BornMap()//��ʼ����Ϸ
{
	srand((unsigned)time(NULL));//��������׵�����

	initgraph(WIDE*SIZE, LONG*SIZE, SHOWCONSOLE);

	loadimage(&img[0], L"./�ز�/0.jpg", SIZE, SIZE);
	loadimage(&img[1], L"./�ز�/1.jpg", SIZE, SIZE);
	loadimage(&img[2], L"./�ز�/2.jpg", SIZE, SIZE);
	loadimage(&img[3], L"./�ز�/3.jpg", SIZE, SIZE);
	loadimage(&img[4], L"./�ز�/4.jpg", SIZE, SIZE);
	loadimage(&img[5], L"./�ز�/5.jpg", SIZE, SIZE);
	loadimage(&img[6], L"./�ز�/6.jpg", SIZE, SIZE);
	loadimage(&img[7], L"./�ز�/7.jpg", SIZE, SIZE);
	loadimage(&img[8], L"./�ز�/8.jpg", SIZE, SIZE);
	loadimage(&img[9], L"./�ز�/9.jpg", SIZE, SIZE);
	loadimage(&img[10], L"./�ز�/10.jpg", SIZE, SIZE);
	loadimage(&img[11], L"./�ز�/11.jpg", SIZE, SIZE);
	int p = rand() % 3 + 1;
	switch (p)
	{
	case 1:loadimage(&img[12], L"./�ز�/win.jpg", WIDE * SIZE, LONG * SIZE); break;
	case 2:loadimage(&img[12], L"./�ز�/win1.jpg", WIDE * SIZE, LONG * SIZE); break;
	default:loadimage(&img[12], L"./�ز�/win2.jpg", WIDE * SIZE, LONG * SIZE); break;
	}
	
	loadimage(&img[13], L"./�ز�/GameOver.jpg", WIDE * SIZE, LONG * SIZE);


	for (int i = 0; i < LONG + 2; i++)
	{
		for (int j = 0; j < WIDE + 2; j++)
		{
			map[i][j] = 0;
		}
	}

	for (int i = 1; i <= NUM;)
	{
		int a = rand() % LONG + 1;//��������׵�����
		int b = rand() % WIDE + 1;//��������׵�����
		if (map[a][b] != -1)
		{
			map[a][b] = -1;
			i++;
		}
	}

	for (int i = 1; i < LONG + 1; i++)
	{
		for (int j = 1; j < WIDE + 1; j++)
		{
			if (map[i][j] == 0)
			{
				for (int x = i - 1; x <= i + 1; x++)
				{
					for (int y = j - 1; y <= j + 1; y++)
					{
						if (map[x][y] == -1) map[i][j] = map[i][j] + 1;
					}
				}
			}
		}
	}

	for (int i = 1; i < LONG + 1; i++)
	{
		for (int j = 1; j < WIDE + 1; j++)
		{
			map[i][j] += 20;
		}
	}

}

void SetGame()//������Ϸ����
{
	for (int i = 1; i < LONG + 1; i++)
	{
		for (int j = 1; j < WIDE + 1; j++)
		{
			if (map[i][j] == -1)
			{
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[10]);
			}
			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[9]);
			}
			else if (map[i][j] >= 29)
			{
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[11]);
			}
			else if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				if (map[i][j] == 0) putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[0]);
				else if (map[i][j] == 1) putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[1]);
				else if (map[i][j] == 2) putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[2]);
				else if (map[i][j] == 3) putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[3]);
				else if (map[i][j] == 4) putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[4]);
				else if (map[i][j] == 5) putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[5]);
				else if (map[i][j] == 6) putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[6]);
				else if (map[i][j] == 7) putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[7]);
				else if (map[i][j] == 8) putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[8]);
			}
		}
	}
}

bool Winif(int a)//��Ӯ
{
	int m = LONG * WIDE - NUM;
	for (int i = 1; i < LONG + 1; i++)
	{
		for (int j = 1; j < WIDE + 1; j++)
		{
			if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				m--;
				if (m == 0)
				{
					putimage(1, 1, &img[12]);
					Sleep(25);
					closegraph();
					return 0;
				}
			}
		}
	}
}


void AOBS(int e, int f)//Automatically Open Blank Spaces(�Զ�չ���ո�)
{
	if (map[e][f] == 0)//��������Ϊ0ʱ
	{
		for (int p = e - 1; p <= e + 1; p++)//�����Ź���
		{
			for (int q = f - 1; q <= f + 1; q++)
			{
				if (map[p][q] >= 20 && map[p][q] <= 28)
				{
					map[p][q] -= 20;
					if (map[p][q] == 0)//������0�����еݹ�
					{
						AOBS(p, q);
					}
					else//���Ǿ��˳�
					{
						break;
					}
				}
			}
		}
	}
}


int main()//������
{
	BornMap();//���õ�ͼ���� 
	SetGame();//���ý�������
	int n = 1;
	while (n != 0)
	{
		//void Gaming()
		//{
		MOUSEMSG msg = { 0 };
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (map[msg.y / SIZE + 1][msg.x / SIZE + 1] >= 19 && map[msg.y / SIZE + 1][msg.x / SIZE + 1] <= 28)
			{
				map[msg.y / SIZE + 1][msg.x / SIZE + 1] -= 20;
				if (map[msg.y / SIZE + 1][msg.x / SIZE + 1] == -1)
				{
					putimage((msg.x / SIZE + 1 - 1)*SIZE, (msg.y / SIZE + 1 - 1)*SIZE, &img[10]);
					//Sleep(1000);
					putimage(1, 1, &img[13]);
					Sleep(5000);
					break;
				}
			}
			int x = msg.y / SIZE + 1;
			int y = msg.x / SIZE + 1;
			AOBS(x, y);
		}
		else if (msg.uMsg == WM_RBUTTONDOWN)
		{
			if (map[msg.y / SIZE + 1][msg.x / SIZE + 1] >= 19 && map[msg.y / SIZE + 1][msg.x / SIZE + 1] <= 28)
			{
				map[msg.y / SIZE + 1][msg.x / SIZE + 1] += 30;
			}
			else if (map[msg.y / SIZE + 1][msg.x / SIZE + 1] >= 49 && map[msg.y / SIZE + 1][msg.x / SIZE + 1] <= 58)
			{
				map[msg.y / SIZE + 1][msg.x / SIZE + 1] -= 30;
			}
		}
		//}
		SetGame();
		n = Winif(n);
	}
	closegraph();
}