#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define U 1
#define D 2
#define R 3
#define L 4//分别代表着上下左右 
typedef struct Snake{
	int x;
	int y;
	Snake *next;
}Snake; 
int direction=R;//蛇的初始行进方向为右边 
int SleepTime=100;//蛇的初始行进速度为200 
int count=0; //吃到的个数
//int judge_count=0;// 
Snake *head,*food,*snake,*index;//定义全局变量，方便之后的创建 
void gotoxy(int x,int y){
	COORD pos;
	pos.X=x;
	pos.Y=y;
	HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
void color(int y)//蛇的颜色 
{
	if(y==7)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),y);
		return;
	}
	srand(time(NULL));
	int x=rand()%15+1;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}
//设计思路： /*全局采用的是坐标，不是数组*/
//创建一个地图 
//创建一条蛇（链表） ,从尾巴开始创建
//跳到该坐标输出蛇身 ，蛇的初始位置
//生成食物 ,蛇吃到食物时，增加长度，并刷新食物 
//蛇不能撞到墙壁和自己
void ready_game();//准备 
void creat_Snake();//创建蛇 
void creat_Map();//创建地图
void creat_Food();//随机生成食物
void rank();//得分 
void game_Over();//判断是否撞到墙壁
void gameover_body();//判断蛇是否撞到自己身体 
void control_Snake();//控制蛇
void move_Snake();//蛇移动，根据控制的方向 
int main()
{
		char y;
		ready_game();//准备游戏 
		creat_Food();//生成食物 
		creat_Snake();//创建蛇 
		creat_Map();//创建地图 
		if(count==0)//得分显示(ps：为了只改变数值) 
		{
			gotoxy(80,17);
			printf("当前得分：%d",count);
		}
		control_Snake();//控制蛇 
		return 0;
}
void ready_game()//准备游戏 
{
	for(int i=4;i>0;i--)//循环倒计时 
	{
		color(0); 
		if(i==4)
		{
			gotoxy(28,14);
			printf("准备游戏");
			Sleep(1000);
			system("cls");
			continue; 
		}
		gotoxy(28,14);
		printf("%d",i);
		Sleep(1000);
		system("cls");
	}
	color(7);
} 
void creat_Map()//创建地图 
{
	for(int i=0;i<60;i++)//地图的长 
	{
		gotoxy(i,0);//gotoxy(x,y):x表示横坐标,y表示纵坐标 
		printf("*");
		gotoxy(i,29);
		printf("*");
	} 
	for(int j=0;j<30;j++)//地图的宽 
	{
		gotoxy(0,j);
		printf("*");
		gotoxy(59,j);
		printf("*");
	}
	gotoxy(80,11);
	printf("蛇不能撞到墙壁和自身！");
	gotoxy(80,13);
	printf("按↑↓←→操作蛇"); 
	gotoxy(80,15);
	printf("吃的食物每吃到10个增加一次难度");
} 
void creat_Snake()//创建蛇 ，头插法 
{
	Snake *tail=(Snake *)malloc(sizeof(Snake));//尾巴
	tail->x=3;
	tail->y=3;
	tail->next=NULL;
	for(int i=0;i<4;i++)//蛇的初始长度为4 
	{
		head=(Snake *)malloc(sizeof(Snake));//新节点
		head->y=tail->y;
		head->x=tail->x+1;
		head->next=tail;
		tail=head; 
	} 
}
void creat_Food()//创建食物 
{
	if(food!=NULL)
	return ;//如果食物没被吃就不新建食物 
	srand(time(NULL));
	food=(Snake *)malloc(sizeof(Snake));
	food->x=rand()%58+1;//x轴坐标要在1到58之间 
	food->y=rand()%28+1;//y轴坐标要在1到28之间 
	food->next=NULL;
/*	index=head->next;
	while(index!=NULL)
	{
		if(index->x==food->x&&index->y==food->y)//判断蛇是否出现在身体里
		{
			creat_Food();//是的话重新生成食物
			break;
		}
		index=index->next;
	} */
	gotoxy(food->x,food->y);
	printf("@");
	
}
void rank()
{
		gotoxy(80,17);
		printf("当前得分：%d",count);
} 
void game_Over()
{
	index=head;
	if(index->x==0||index->y==0||index->x==59||index->y==29)//当头部撞到墙壁时 
	{
		gotoxy(30,15);
		printf("游戏结束\n");
		system("pause");
		exit(0);
	}

}
void gameover_body()//判断是否撞到自己身体 
{
	index=head->next;
	while(index!=NULL)
	{
	if(head->x==index->x&&head->y==index->y)//遍历身体，查看是否有身体坐标和头部坐标一样的结点，有的话说明撞倒身体，游戏结束 
	{
		gotoxy(30,15);
		printf("游戏结束\n");
		system("pause");
		exit(0);
	}
	index=index->next;
	}
} 
void move_Snake()
{
	Snake *nexthead=(Snake *)malloc(sizeof(Snake));
	game_Over();
	switch(direction)//判断移动方向 
	{
		case U:nexthead->x=head->x;//向上 
			   nexthead->y=head->y-1;
			   break;	
		case D:nexthead->x=head->x;//向下 
			   nexthead->y=head->y+1;
			   break;	
		case L:nexthead->x=head->x-1;//向左 
			   nexthead->y=head->y;
			   break;	
		case R:nexthead->x=head->x+1;//向右 
			   nexthead->y=head->y;
			   break;		   
	}
	nexthead->next=head;//新增一个结点，之后再去除末尾的结点就能实现蛇的移动效果
	head=nexthead;//使原来的头部向着某个方向移动 
	gameover_body();//判断是否撞到自己身体 
	index=head;//把头部地址复制一份给index，用于遍历链表，输出蛇
	if(nexthead->x==food->x&&nexthead->y==food->y)//当吃到食物的时候，增加一个结点 
	{
		while(index!=NULL)//利用头插法增加一个结点 
		{
			color(1);
			gotoxy(index->x,index->y);
			printf("#");
			index=index->next;
		}
		free(food);
		food=NULL;
		creat_Food();//并且释放原来的食物，再次随机生成一个食物
		count++;
		if(count==10)//根据吃到的食物个数增加难度 
		SleepTime=120;
		if(count==20)
		SleepTime=80;
		if(count==30)
		SleepTime=50; 
		rank();
	}
	else
	{
		while(index->next->next!=NULL)//因为要去除末尾结点，所以加上两个next 
	{
		gotoxy(index->x,index->y);//跳到该坐标输出 
		printf("#");
		index=index->next;//跳到下一结点 
	} 
	gotoxy(index->next->x,index->next->y);//把之前最后的结点替换成空格 
	printf(" ");
	
	free(index->next);//释放掉最后的结点 
	index->next=NULL;//使此时蛇末尾结点next指针指向NULL 
	}
	
}
void control_Snake()//控制蛇 
{
	while(1){
		if(GetAsyncKeyState(VK_UP)&&direction!=D)//控制蛇的方向且蛇的方向不能180度转变 
			direction=U;
		if(GetAsyncKeyState(VK_DOWN)&&direction!=U)
			direction=D;
		if(GetAsyncKeyState(VK_RIGHT)&&direction!=L)
			direction=R;
		 if(GetAsyncKeyState(VK_LEFT)&&direction!=R)
			direction=L;
		move_Snake();//移动蛇 
		Sleep(SleepTime);//刷新间隔 
		
	}
	
}



