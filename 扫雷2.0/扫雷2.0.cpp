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


void BornMap()//初始化游戏
{
	srand((unsigned)time(NULL));//随机生成雷的坐标

	initgraph(WIDE*SIZE, LONG*SIZE, SHOWCONSOLE);

	loadimage(&img[0], L"./素材/0.jpg", SIZE, SIZE);
	loadimage(&img[1], L"./素材/1.jpg", SIZE, SIZE);
	loadimage(&img[2], L"./素材/2.jpg", SIZE, SIZE);
	loadimage(&img[3], L"./素材/3.jpg", SIZE, SIZE);
	loadimage(&img[4], L"./素材/4.jpg", SIZE, SIZE);
	loadimage(&img[5], L"./素材/5.jpg", SIZE, SIZE);
	loadimage(&img[6], L"./素材/6.jpg", SIZE, SIZE);
	loadimage(&img[7], L"./素材/7.jpg", SIZE, SIZE);
	loadimage(&img[8], L"./素材/8.jpg", SIZE, SIZE);
	loadimage(&img[9], L"./素材/9.jpg", SIZE, SIZE);
	loadimage(&img[10], L"./素材/10.jpg", SIZE, SIZE);
	loadimage(&img[11], L"./素材/11.jpg", SIZE, SIZE);
	int p = rand() % 3 + 1;
	switch (p)
	{
	case 1:loadimage(&img[12], L"./素材/win.jpg", WIDE * SIZE, LONG * SIZE); break;
	case 2:loadimage(&img[12], L"./素材/win1.jpg", WIDE * SIZE, LONG * SIZE); break;
	default:loadimage(&img[12], L"./素材/win2.jpg", WIDE * SIZE, LONG * SIZE); break;
	}
	
	loadimage(&img[13], L"./素材/GameOver.jpg", WIDE * SIZE, LONG * SIZE);


	for (int i = 0; i < LONG + 2; i++)
	{
		for (int j = 0; j < WIDE + 2; j++)
		{
			map[i][j] = 0;
		}
	}

	for (int i = 1; i <= NUM;)
	{
		int a = rand() % LONG + 1;//随机生成雷的坐标
		int b = rand() % WIDE + 1;//随机生成雷的坐标
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

void SetGame()//布置游戏界面
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

bool Winif(int a)//判赢
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


void AOBS(int e, int f)//Automatically Open Blank Spaces(自动展开空格)
{
	if (map[e][f] == 0)//当所处块为0时
	{
		for (int p = e - 1; p <= e + 1; p++)//遍历九宫格
		{
			for (int q = f - 1; q <= f + 1; q++)
			{
				if (map[p][q] >= 20 && map[p][q] <= 28)
				{
					map[p][q] -= 20;
					if (map[p][q] == 0)//发现是0，进行递归
					{
						AOBS(p, q);
					}
					else//不是就退出
					{
						break;
					}
				}
			}
		}
	}
}


int main()//主函数
{
	BornMap();//调用地图生成 
	SetGame();//调用界面设置
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