#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define U 1
#define D 2
#define R 3
#define L 4//�ֱ�������������� 
typedef struct Snake{
	int x;
	int y;
	Snake *next;
}Snake; 
int direction=R;//�ߵĳ�ʼ�н�����Ϊ�ұ� 
int SleepTime=100;//�ߵĳ�ʼ�н��ٶ�Ϊ200 
int count=0; //�Ե��ĸ���
//int judge_count=0;// 
Snake *head,*food,*snake,*index;//����ȫ�ֱ���������֮��Ĵ��� 
void gotoxy(int x,int y){
	COORD pos;
	pos.X=x;
	pos.Y=y;
	HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
void color(int y)//�ߵ���ɫ 
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
//���˼·�� /*ȫ�ֲ��õ������꣬��������*/
//����һ����ͼ 
//����һ���ߣ����� ,��β�Ϳ�ʼ����
//����������������� ���ߵĳ�ʼλ��
//����ʳ�� ,�߳Ե�ʳ��ʱ�����ӳ��ȣ���ˢ��ʳ�� 
//�߲���ײ��ǽ�ں��Լ�
void ready_game();//׼�� 
void creat_Snake();//������ 
void creat_Map();//������ͼ
void creat_Food();//�������ʳ��
void rank();//�÷� 
void game_Over();//�ж��Ƿ�ײ��ǽ��
void gameover_body();//�ж����Ƿ�ײ���Լ����� 
void control_Snake();//������
void move_Snake();//���ƶ������ݿ��Ƶķ��� 
int main()
{
		char y;
		ready_game();//׼����Ϸ 
		creat_Food();//����ʳ�� 
		creat_Snake();//������ 
		creat_Map();//������ͼ 
		if(count==0)//�÷���ʾ(ps��Ϊ��ֻ�ı���ֵ) 
		{
			gotoxy(80,17);
			printf("��ǰ�÷֣�%d",count);
		}
		control_Snake();//������ 
		return 0;
}
void ready_game()//׼����Ϸ 
{
	for(int i=4;i>0;i--)//ѭ������ʱ 
	{
		color(0); 
		if(i==4)
		{
			gotoxy(28,14);
			printf("׼����Ϸ");
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
void creat_Map()//������ͼ 
{
	for(int i=0;i<60;i++)//��ͼ�ĳ� 
	{
		gotoxy(i,0);//gotoxy(x,y):x��ʾ������,y��ʾ������ 
		printf("*");
		gotoxy(i,29);
		printf("*");
	} 
	for(int j=0;j<30;j++)//��ͼ�Ŀ� 
	{
		gotoxy(0,j);
		printf("*");
		gotoxy(59,j);
		printf("*");
	}
	gotoxy(80,11);
	printf("�߲���ײ��ǽ�ں�����");
	gotoxy(80,13);
	printf("����������������"); 
	gotoxy(80,15);
	printf("�Ե�ʳ��ÿ�Ե�10������һ���Ѷ�");
} 
void creat_Snake()//������ ��ͷ�巨 
{
	Snake *tail=(Snake *)malloc(sizeof(Snake));//β��
	tail->x=3;
	tail->y=3;
	tail->next=NULL;
	for(int i=0;i<4;i++)//�ߵĳ�ʼ����Ϊ4 
	{
		head=(Snake *)malloc(sizeof(Snake));//�½ڵ�
		head->y=tail->y;
		head->x=tail->x+1;
		head->next=tail;
		tail=head; 
	} 
}
void creat_Food()//����ʳ�� 
{
	if(food!=NULL)
	return ;//���ʳ��û���ԾͲ��½�ʳ�� 
	srand(time(NULL));
	food=(Snake *)malloc(sizeof(Snake));
	food->x=rand()%58+1;//x������Ҫ��1��58֮�� 
	food->y=rand()%28+1;//y������Ҫ��1��28֮�� 
	food->next=NULL;
/*	index=head->next;
	while(index!=NULL)
	{
		if(index->x==food->x&&index->y==food->y)//�ж����Ƿ������������
		{
			creat_Food();//�ǵĻ���������ʳ��
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
		printf("��ǰ�÷֣�%d",count);
} 
void game_Over()
{
	index=head;
	if(index->x==0||index->y==0||index->x==59||index->y==29)//��ͷ��ײ��ǽ��ʱ 
	{
		gotoxy(30,15);
		printf("��Ϸ����\n");
		system("pause");
		exit(0);
	}

}
void gameover_body()//�ж��Ƿ�ײ���Լ����� 
{
	index=head->next;
	while(index!=NULL)
	{
	if(head->x==index->x&&head->y==index->y)//�������壬�鿴�Ƿ������������ͷ������һ���Ľ�㣬�еĻ�˵��ײ�����壬��Ϸ���� 
	{
		gotoxy(30,15);
		printf("��Ϸ����\n");
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
	switch(direction)//�ж��ƶ����� 
	{
		case U:nexthead->x=head->x;//���� 
			   nexthead->y=head->y-1;
			   break;	
		case D:nexthead->x=head->x;//���� 
			   nexthead->y=head->y+1;
			   break;	
		case L:nexthead->x=head->x-1;//���� 
			   nexthead->y=head->y;
			   break;	
		case R:nexthead->x=head->x+1;//���� 
			   nexthead->y=head->y;
			   break;		   
	}
	nexthead->next=head;//����һ����㣬֮����ȥ��ĩβ�Ľ�����ʵ���ߵ��ƶ�Ч��
	head=nexthead;//ʹԭ����ͷ������ĳ�������ƶ� 
	gameover_body();//�ж��Ƿ�ײ���Լ����� 
	index=head;//��ͷ����ַ����һ�ݸ�index�����ڱ������������
	if(nexthead->x==food->x&&nexthead->y==food->y)//���Ե�ʳ���ʱ������һ����� 
	{
		while(index!=NULL)//����ͷ�巨����һ����� 
		{
			color(1);
			gotoxy(index->x,index->y);
			printf("#");
			index=index->next;
		}
		free(food);
		food=NULL;
		creat_Food();//�����ͷ�ԭ����ʳ��ٴ��������һ��ʳ��
		count++;
		if(count==10)//���ݳԵ���ʳ����������Ѷ� 
		SleepTime=120;
		if(count==20)
		SleepTime=80;
		if(count==30)
		SleepTime=50; 
		rank();
	}
	else
	{
		while(index->next->next!=NULL)//��ΪҪȥ��ĩβ��㣬���Լ�������next 
	{
		gotoxy(index->x,index->y);//������������� 
		printf("#");
		index=index->next;//������һ��� 
	} 
	gotoxy(index->next->x,index->next->y);//��֮ǰ���Ľ���滻�ɿո� 
	printf(" ");
	
	free(index->next);//�ͷŵ����Ľ�� 
	index->next=NULL;//ʹ��ʱ��ĩβ���nextָ��ָ��NULL 
	}
	
}
void control_Snake()//������ 
{
	while(1){
		if(GetAsyncKeyState(VK_UP)&&direction!=D)//�����ߵķ������ߵķ�����180��ת�� 
			direction=U;
		if(GetAsyncKeyState(VK_DOWN)&&direction!=U)
			direction=D;
		if(GetAsyncKeyState(VK_RIGHT)&&direction!=L)
			direction=R;
		 if(GetAsyncKeyState(VK_LEFT)&&direction!=R)
			direction=L;
		move_Snake();//�ƶ��� 
		Sleep(SleepTime);//ˢ�¼�� 
		
	}
	
}



