//2019年3月16日 17:29:07
//2048
//1、地图数据结构   2、合并和移动？   3、判断胜负
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<string.h> 
#define N 5//地图大小 
#define M 13//table表的长度 
#define WINFLAG 11


char map[N][N];//地图 
int table[M];//查表使用


void Init();
void Run();
void Print();
int Win();
void Lose();
int IsLose();
int Up(int *isChange);
int Down(int *isChange);
int Left(int *isChange);
int Right(int *isChange);
void Generator(int dir);


void gotoxy(int x, int y); //将光标调整到(x,y)的位置


//光标隐藏
void HideCursor() ; //隐藏光标显示

int main(void)
{
	srand((unsigned)time(NULL));
	HideCursor();
	Init(); 
	Run();
	return 0;
}


void Generator(int dir)
{
	//按下右，就按列扫，从左往右随机选一个数生成
	//按下上，就按行扫，从下网上随机选一个数生成	
//	int begin;
//	int end;
//	int mul;//增量
//	for(int i = begin;i != end;i += mul) 
//	for(int i = 0;i < N;++i)
//		for(j = N-1;j >= 0;--j) 
	int flag = 0;
	int i1 = -1,i2 = -1; 
	if(dir == 1 || dir == 2)
	{
		int begin,end,mul;
		dir == 1?begin = 0,end = N,mul = 1:begin = N-1,end = -1,mul = -1;
		for(int i = 0;i < N;++i)
			for(int j = begin;j != end;j += mul) 
			{
				//保证选一个数，然后其他的随机
				if(map[i][j] == 0)//选到了一个数
				{
					if(flag == 0)//之前没选到过
					{
						i1 = i;
						i2 = j;
						flag = 1;  
					}
					else
					{
						if(rand()%3 < 2)
						{
							i1 = i;
							i2 = j;
						}
					}	
				} 
			}
	}
	else if(dir == 3 ||  dir == 4)
	{
		int begin,end,mul;
		dir == 3?begin = 0,end = N,mul = 1:begin = N-1,end = -1,mul = -1;
		for(int j = begin;j != end;j += mul)
			for(int i = 0;i < N;++i)
			{
				//保证选一个数，然后其他的随机
				if(map[i][j] == 0)//选到了一个数
				{
					if(flag == 0)//之前没选到过
					{
						i1 = i;
						i2 = j;
						flag = 1;  
					}
					else
					{
						if(rand()%3 < 2)
						{
							i1 = i;
							i2 = j;
						}
					}	
				} 
			}
	}
	if(i1 == i2 && i2 == -1)
		return;
	map[i1][i2] = 1;
}

int Up(int *isChange)
{
	//往上，所以是从上往下扫描
	//一列一列的算 

	for(int j = 0;j < N;++j)
	{
		int k = 0;
		for(int i = 1;i < N;++i)
		{
			if(map[i][j] != 0)//当前处理的这一位是有数字的 
			{
				//只要是非0，且没有合并，则相加 
				//这里保证map[i][j]是有数字的 
				if(map[i][j] == map[k][j])
				{
					//与那个数字进行交互。合并操作 
					map[k][j] += 1;
					map[i][j] = 0; 
					if(map[k][j] == 12)
						return 5;
					*isChange = 1;
				} 
				else if(map[k][j] == 0)//我们是说k是第一个非零的，但初始的时候我们为了好运算，是没做判断的
				{
					//把当前位置上的数移过去   特判的移动操作 
					map[k][j] = map[i][j];
					map[i][j] = 0; 
					*isChange = 1;
				}
				else if(k+1 != i)//移动操作 
				{
					map[k+1][j] = map[i][j];//2 0 0 4  2 4 0 0     
					map[i][j] = 0;//4 2 0 0
					++k; 
					*isChange = 1;
				}
				
				else//没有合并，且不是特判的 
					++k; 
			}
		}
	}
	return 1;
}
int Down(int *isChange)
{
	for(int j = 0;j < N;++j)
	{
		int k = N-1;
		for(int i = N-2;i >= 0;--i)
		{
			if(map[i][j] != 0)//当前处理的这一位是有数字的 
			{
				//只要是非0，且没有合并，则相加 
				//这里保证map[i][j]是有数字的 
				if(map[i][j] == map[k][j])
				{
					//与那个数字进行交互。合并操作 
					map[k][j] += 1;
					map[i][j] = 0; 
					if(map[k][j] == 12)
						return 5;
					*isChange = 1;
				} 
				else if(map[k][j] == 0)//我们是说k是第一个非零的，但初始的时候我们为了好运算，是没做判断的
				{
					//把当前位置上的数移过去   特判的移动操作 
					map[k][j] = map[i][j];
					map[i][j] = 0; 
					*isChange = 1;
				}
				else if(k-1 != i)//移动操作 
				{
					map[k-1][j] = map[i][j];//2 0 0 4  2 4 0 0     
					map[i][j] = 0;//4 2 0 0
					--k; 
					*isChange = 1;
				}
				else//没有合并，且不是特判的 
					--k; 
			}
		}
	}
	return 2;
}
int Left(int *isChange)
{
	//合并？什么情况下合并？什么情况下移动？
	//一行一行处理
	//从左往右处理
	//这个有数字，我们才需要处理，没数字不用管  2 0 4 8    2 4 0 8    2 4 8 0
	for(int i = 0;i < N;++i)
	{
		int k = 0;
		for(int j = 1;j < N;++j)
		{
			if(map[i][j] != 0)//当前处理的这一位是有数字的 
			{
				//这里保证map[i][j]是有数字的 
				if(map[i][j] == map[i][k])
				{
					//与那个数字进行交互。合并操作 
					map[i][k] += 1;
					map[i][j] = 0; 
					if(map[i][k] == 12)
						return 5;
					*isChange = 1;
				}
				else if(map[i][k] == 0)//我们是说k是第一个非零的，但初始的时候我们为了好运算，是没做判断的
				{
					//把当前位置上的数移过去   特判的移动操作 
					map[i][k] = map[i][j];
					map[i][j] = 0; 
					*isChange = 1;
				} 
				else if(k+1 != j)//移动操作 
				{
					map[i][k+1] = map[i][j];//2 0 0 4  2 4 0 0     
					map[i][j] = 0;//4 2 0 0
					++k; 
					*isChange = 1;
				}
				else
					++k; 
			}
		}
	}
	return 3;
}
int Right(int *isChange)
{
	//从右至左 
	for(int i = 0;i < N;++i)
	{
		int k = N-1;
		for(int j = N-2;j >= 0;--j)
		{
			if(map[i][j] != 0)//当前处理的这一位是有数字的 
			{
				//这里保证map[i][j]是有数字的 
				if(map[i][j] == map[i][k])
				{
					//与那个数字进行交互。合并操作 
					map[i][k] += 1;
					map[i][j] = 0; 
					if(map[i][k] == 12)
						return 5;
					*isChange = 1;
				}
				else if(map[i][k] == 0)//我们是说k是第一个非零的，但初始的时候我们为了好运算，是没做判断的
				{ 
					map[i][k] = map[i][j];
					map[i][j] = 0; 
					*isChange = 1;
				} 
				else if(k-1 != j)//移动操作 
				{
					map[i][k-1] = map[i][j];    
					map[i][j] = 0;
					--k; 
					*isChange = 1;
				}
				else
					--k;
			}
		}
	}
	return 4;
}


void Init()
{
	int n = 16;//随机地图的数目 
	//先求table
	table[0] = 1;
	for(int i = 1;i < M;++i) 
		table[i] = table[i-1]<<1;//等同于*2 
//	for(int i = 0;i < M;++i)
//		printf("%5d",table[i]);
//及时测试，验证正确性，免得日后找bug麻烦
	
	//随机地图   随机生成3个2？ 
	memset(map,0,sizeof(map));
	for(int i = 0;i < n;++i)
	{
		int i1 = rand()%N;
		int i2 = rand()%N;
		//随机一组下标，让地图那个位置变成1
		map[i1][i2] = 1; //这个1代表2的一次，最终展现的是2 
	}
}
void Run()
{
	int isChange = 0;//检测是否发生了变化 
	int flag = 0;
	while(1)
	{
		Print();
		isChange = 0;
		switch(getch())
		{
			case 'w':flag = Up(&isChange);break;
			case 's':flag = Down(&isChange);break;
			case 'a':flag = Left(&isChange);break;
			case 'd':flag = Right(&isChange);break;
		}
		if(flag != 5 && isChange)
			Generator(flag);
		if(flag == 5)
		{
			Win();
			break;
		}
		else if(IsLose())
		{
			Print();
			Lose();
			break;
		}	
	}
}
void Print()
{
	gotoxy(0,0);
	for(int i = 0;i < N;++i)
	{
		for(int j = 0;j < N;++j)
			if(map[i][j] != 0)
				printf("%3d  ",table[map[i][j]]);
			else
				printf("     ");
		putchar('\n');
	}
}
int Win()
{
	printf("You are winner!\n");
}
void Lose()
{
	printf("You are loser!\n");
}
int IsLose()
{
	//判断是否还具备可操作空间
	for(int i = 0;i < N;++i)
	 	for(int j = 0;j < N-1;++j)
	 	{
	 		if(map[i][j] == map[i][j+1])
			 	return 0;
			else if(map[i][j]*map[i][j+1] == 0)
				return 0;	
		}
	for(int j = 0;j < N;++j)
	 	for(int i = 0;i < N-1;++i)
	 	{
	 		if(map[i][j] == map[i+1][j])
			 	return 0;
			else if(map[i][j]*map[i+1][j] == 0)
				return 0;	
		}
	Print();
	return 1;
}
//光标跳转
void gotoxy(int x, int y) //将光标调整到(x,y)的位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}


//光标隐藏
void HideCursor()  //隐藏光标显示
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
