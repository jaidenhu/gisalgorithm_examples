#include "pch.h"
#include <iostream>
#include<stdio.h>
using namespace std;

int direction = 8;  //8个方向
int MAX = 50;  //最大步数
int num = 0;  //总方案数
int **path = new int* [MAX + 1];

int dx[9] = { 0,1,2,2,1,-1,-2,-2,-1 };  //表示横坐标的方向
int dy[9] = { 0,2,1,-1,-2,2,1,-1,-2 };  //表示纵坐标的方向

void Path(int max_x, int max_y, int step, int **xy) {
	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++)
			xy[i][j] = 0;
		for (int i = 1; i < step; i++)
			xy[path[i][1]][path[i][0]] = 1;
	}
}

int Judgment(int x,int y,int **xy) {
	int judge = 0;
	if (xy[y][x] != 0) //重复，错误
		judge = 1;
	else 
		xy[y][x] = 1;
	return judge;
}

void Jump(int max_x, int max_y, int x, int y, int step, int **xy) {
	bool t1, t2, t3, t4;
	int x1, y1;
	Path(max_x, max_y, step, xy);
	for (int k = 1; k <= direction; k++) {  //朝八个方向中的某个方向跳跃
		x1 = x + dx[k];
		y1 = y + dy[k];

		//跳出边界，进入下一种路径的查找
		if (x1 > max_x || y1 > max_y || x1 < 0 || y1 < 0)
			continue;

		t1 = (x1 >= 0) && (x1 <= max_x);  //左右边界内
		t2 = (y1 >= 0) && (y1 <= max_y);  //上下边界内

		t3 = (x1 == path[0][0]);
		t4 = (y1 == path[0][1]);

		if (t1 && t2) {  //在棋盘内
			if (!Judgment(x1, y1, xy)) {  //返回false表示没有重复，可以继续寻找路径
				path[step][0] = x1;
				path[step][1] = y1;
				if (t3 && t4) {
					num++;
					cout<<"方案"<<num;
					for (int i = 0; i <= step; i++) {
						printf("(%d, %d)", path[i][0], path[i][1]);
						if (i != step)
							printf("->");
					}
					printf("\n");
				}
				else
					Jump(max_x, max_y, x1, y1, step + 1, xy);
			}
		}
	}
}

int main()
{
	for (int i = 0; i < MAX + 1; i++) {
	    path[i] = new int[2];
    }
	int max_x, max_y;
	int a, b;
	a = path[0][0];
	b = path[0][1];
	printf("有一m*n的棋盘(即棋盘由m行和n列)，一马放在棋盘中任意位置，马按中国象棋跳法，从初始位置起跳，跳至边界后返回，求所有能返回初始位置的周游路线。\n");
	printf("输入棋盘行列数 m, n: ");
	scanf_s("%d %d", &max_x, &max_y);
	printf("输入起始点所在行列数:");
    
	scanf_s("%d %d", &a, &b);
	if (max_x > 10 || max_y > 10 || a > 10 || b > 10 || (a + 1) > max_x || (b + 1) > max_y)
	{
		printf("请按照要求输入数据！");
	}
	int **xy=new int* [max_y + 1];
	for (int i = 0; i < max_y + 1; i++) {
		xy[i] = new int[max_y + 1];
	}
	for (int i = 0; i < max_y + 1; i++) {
		for (int j = 0; j < max_x + 1; j++) {
			xy[i][j] = 0;
		}
	}
	Jump(max_x, max_y, 0, 0, 1, xy);
	printf("总方案数 %d", num);
	delete[] xy;
	delete[] path;
}


