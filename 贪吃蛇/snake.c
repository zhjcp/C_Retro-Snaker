
#define _CRT_SECURE_NO_WARNINGS 1

#include"snake.h";
#include<stdio.h>			
#include<time.h>			
#include<windows.h>		
#include<stdlib.h>			
#include<conio.h>			//接收键盘输入输出



#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4B00
#define Right 0x4D00      //蛇的状态，U：上 ；D：下；L:左 R：右



int Wall[54][26];
int status;
int score = 0, scoreChange = 10;
int status, sleeptime = 200;	//蛇前进状态，每次运行的时间间隔
Head snakeHead;	//蛇头指针
Tail snakeTail;//蛇尾指针
snake* itemSnakeNode;		//蛇节点指针中间变量
foodPtrTo food;  //食物指针
minePtrTo mine1;  //地雷指针
minePtrTo mine2;  //地雷指针2
int mineCount = 0;
poisonousWeedPtrTo poisonousWeed; //毒草指针
int gameOverWay = 0;		//游戏结束
static int gameWhich = 0;
int randNum=0;
HANDLE controlHandle;				//控制台句柄





/*******函  数  声  明 *******/

void getXOY(int x, int y);   //设置光标位置

int color(int c);           //更改文字颜色

void welcomeToGame();       //开始界面

void dataReInit();          //数据再次初始化

void createMap();           //绘制地图

void createMap_2();         //绘制地图2
  
void createMap_3();        //绘制地图2

void score_and_Tips();		//游戏界面右侧的得分和小提示

void initSnake();           //初始化蛇身，画蛇身

void createFood();          //创建并随机出现食物

void createPoisonousWeed();     //创建并随机出现毒草

void createMine();         //创建并随机出现地雷

int biteSelf();             //判断是否咬到了自己

void hitWall();       //设置蛇撞墙的情况

void speedUp();				//加速

void speedDown();			//减速

void snakeMove();           //控制蛇前进方向

void keyboardControl();     //控制键盘按键

void overGame();             //游戏结束

void saveData(int score);

void readData();

void PaiXu();

void setChoice();				//游戏失败之后的选择

void explationGame();           //游戏说明



/* 设置光标位置*/
void getXOY(int x, int y)
{
	COORD currentPlace;
	currentPlace.X = x;
	currentPlace.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPlace);//使光标到current位置
}



/* 文字颜色函数*/
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);   //更改文字颜色 
	return 0;   //GetStdHandle（）返回标准的输出的设备的句柄（用来标识不同设备的数值）
}


//开始界面
void welcomeToGame()
{ 
    char menuOperate;
	getXOY(39, 2);
	color(6);
	printf("贪   吃   蛇");

	color(12);
	getXOY(40, 6);
	printf("1.简单模式");

	getXOY(40, 8);
	printf("2.急速模式");

	getXOY(40, 10);
	printf("3.困难模式");

	getXOY(40, 14);
	printf("4.排行榜");

	getXOY(40, 16);
	printf("5.游戏说明");

	getXOY(40, 18);
	printf("6.退出游戏");

	getXOY(40, 27);
	color(3);
	printf("输入操作数1/2/3: ");

	color(14);
	scanf("%c", &menuOperate);    		//输入选项

	switch (menuOperate)
	{
	   case '1':
	  {
		  gameWhich = 1;
		  system("cls");  //清空屏幕(准备初始化屏幕）
		  createMap();    //创建地图
		  initSnake();    //初始化蛇身
		  createFood();       //创建食物
		  createPoisonousWeed();//创建毒草
		  createMine(mine1);    //创建地雷
		  keyboardControl();  //按键控制
		  break;
	  }

	   case '2':
	   {
		   gameWhich = 2;
		   sleeptime = 100;
		   system("cls");  //清空屏幕(准备初始化屏幕）
		   createMap_2();    //创建地图
		   initSnake();    //初始化蛇身
		   createFood();       //创建食物
		   createPoisonousWeed();//创建毒草
		   createMine(mine1);    //创建地雷
		   keyboardControl();  //按键控制
		   break;
	   }

	   case '3':
	   {
		   gameWhich = 3;
		   sleeptime = 120;
		   system("cls");  //清空屏幕(准备初始化屏幕）
		   createMap_3();    //创建地图
		   initSnake();    //初始化蛇身
		   createFood();       //创建食物
		   createPoisonousWeed();//创建毒草
		   createMine(mine1);    //创建地雷
		   createMine(mine2);    //创建地雷
		   keyboardControl();  //按键控制
		   break;
	   }

	   case '4':
	   {
		   readData();      	//打开排行榜
		   break;
	   }

	   case '6':
	   {
		   exit(0);     		//退出游戏
		   break;
	   }

	  default:
	  {
		system("cls");		//清屏
		welcomeToGame();
	  }
	}
}

//创建地图
void createMap()
{
	for (int x = 0; x < 58; x +=2)		//上下边界（一格间隔为2）
	{
		color(5);

		getXOY(x, 0);		
		printf("□");

		getXOY(x, 26);
		printf("□");
	}

	for (int y = 1; y< 26; y++)		//左右边界（一格间隔为1）
	{
		getXOY(0, y);
		printf("□");

		getXOY(56, y);
		printf("□");
	}

	for (int x = 2; x < 56; x += 2)	//中间网格
	{
		for (int y = 1; y < 26; y++)
		{
			getXOY(x, y);
			color(8);
			printf("■");
		}
	}
}

//创建地图2
void createMap_2()
{
	for (int x = 0; x < 58; x += 2)		//上下边界（一格间隔为2）
	{
		color(5);

		getXOY(x, 0);
		printf("□");

		getXOY(x, 26);
		printf("□");
	}

	for (int y = 1; y < 26; y++)		//左右边界（一格间隔为1）
	{
		getXOY(0, y);
		printf("□");

		getXOY(56, y);
		printf("□");
	}

	for (int x = 2; x < 56; x += 2)	//中间网格
	{
		for (int y = 1; y < 26; y++)
		{
			getXOY(x, y);
			color(8);
			printf("■");
		}
	}

	for (int x = 20; x < 36; x+=2)
	{
		getXOY(x, 5);
		color(5);
		printf("□");

		getXOY(x, 20);
		color(5);
		printf("□");

		Wall[x][5] = 1;
		Wall[x][20] = 1;
	}
}


//创建地图3
void createMap_3()
{
	for (int x = 0; x < 58; x += 2)		//上下边界（一格间隔为2）
	{
		color(5);

		getXOY(x, 0);
		printf("□");

		getXOY(x, 26);
		printf("□");
	}

	for (int y = 1; y < 26; y++)		//左右边界（一格间隔为1）
	{
		getXOY(0, y);
		printf("□");

		getXOY(56, y);
		printf("□");
	}

	for (int x = 2; x < 56; x += 2)	//中间网格
	{
		for (int y = 1; y < 26; y++)
		{
			getXOY(x, y);
			color(8);
			printf("■");
		}
	}

	for (int x = 20; x < 36; x += 2)
	{
		getXOY(x, 5);
		color(5);
		printf("□");

		getXOY(x, 20);
		color(5);
		printf("□");

		Wall[x][5] = 1;
		Wall[x][20] = 1;
	}

	for (int y = 7; y < 18; y++)
	{
		getXOY(8, y);
		color(5);
		printf("□");

		getXOY(46, y);
		color(5);
		printf("□");

		Wall[8][y] = 1;
		Wall[46][y] = 1;
	}
}




/*  游戏界面右侧的得分和小提示（需要修改！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！）*/
void score_and_Tips()
{
	color(14);
	getXOY(64, 8);	
	printf("得分：%d  ", score);

	getXOY(64, 14);
	printf("空格：暂停游戏");

	getXOY(64, 16);
	printf("ESC ：退出游戏");
}


void dataReInit()
{
	for (int i = 0; i < 40; i += 2)
	{
		for (int j = 0; j < 26; j++)
			Wall[i][j] = 0;
	}
    score = 0, scoreChange = 10;			//总得分与每次吃食物得分
	if(gameWhich==1)
    sleeptime = 200;
	if (gameWhich == 2)
		sleeptime = 100;
	if (gameWhich == 3)
		sleeptime = 150;
}


/*初始化蛇身(双链表）*/
void initSnake()
{
	/*双链表*/
	snakeTail = (Tail)malloc(sizeof(snake));//从蛇尾开始插入，每次插入都是新的头部
	snakeTail->pos_x = 24;         	//蛇的初始位置（24,5）
	snakeTail->pos_y = 10;

    snakeHead = (Head)malloc(sizeof(snake)); //初始化蛇头
	snakeTail->previous = snakeHead;
	snakeHead->next = snakeTail;
	snakeHead->pos_x = 24 + 2 * 1;  //设置全局蛇头位置
	snakeHead->pos_y =10;
	snakeTail->next = NULL;
	

    getXOY(snakeTail->pos_x, snakeTail->pos_y);
	color(14);
	printf("★");       //输出蛇身，蛇身使用★组成

	getXOY(snakeHead->pos_x, snakeHead->pos_y);
	color(14);
	printf("★");       //输出蛇身，蛇身使用★组成
}



/* 随机创建食物*/
void createFood()
{
	foodPtrTo currentFood;
	currentFood = (foodPtrTo)malloc(sizeof(Food));   //初始化food_1

	while ((currentFood->pos_x % 2) != 0)    				//保证其为偶数，使得食物能与蛇头对其，然后食物会出现在网格线上
	{
		currentFood->pos_x = (3*snakeHead->pos_x) % 52 + 2;              //食物随机出现
	}

	currentFood->pos_y = (7* snakeTail->pos_y) % 24 + 1;
	itemSnakeNode = snakeHead;

	while (itemSnakeNode != NULL)
	{
		if (itemSnakeNode->pos_x == currentFood->pos_x && itemSnakeNode->pos_y == currentFood->pos_y) //判断蛇身是否与食物重合
		{
			free(currentFood);               //如果蛇身和食物重合，那么释放食物指针
			createFood();                   //重新创建食物
		}
		if (poisonousWeed != NULL && poisonousWeed->pos_x == currentFood->pos_x && poisonousWeed->pos_y == currentFood->pos_y)
		{
			free(currentFood);         //如果食物和毒草重合，那么释放食物指针
			createFood();            //重新创建食物
		}
		if (mine1 != NULL && currentFood->pos_x == mine1->pos_x && currentFood->pos_y == mine1->pos_y)
		{
			free(currentFood);         //如果食物和毒草重合，那么释放食物指针
			createFood();            //重新创建食物
		}
		itemSnakeNode = itemSnakeNode->next;
	}

	for (int i = 0; i < 40; i += 2)//障碍物检测
	{
		for (int j = 0; j < 26; j++)
		{
			if (Wall[i][j] == 1 && currentFood->pos_x == i && currentFood->pos_y == j)
			{
				free(currentFood);         //如果食物和障碍物重合，那么释放食物指针
				createFood();            //重新创建食物
			}
		}
	}
	getXOY(currentFood->pos_x, currentFood->pos_y);
	food = currentFood;          //成功创建食物
	//free(currentFood);
	currentFood = NULL;
	color(12);
	printf("●");           //输出食物

}

/* 随机创建毒草*/
void createPoisonousWeed()
{
	poisonousWeedPtrTo currentWeed;
	currentWeed = (poisonousWeedPtrTo)malloc(sizeof(PoisonousWeed));   //初始化food_1

	while ((currentWeed->pos_x % 2) != 0)    				//保证其为偶数，使得毒草能与蛇头对其，然后毒草会出现在网格线上
	{
		currentWeed->pos_x = (5*snakeHead->pos_x) % 52 + 2;              //毒草随机出现
	}

	currentWeed->pos_y = (11* snakeTail->pos_y) % 24 + 1;
	itemSnakeNode = snakeHead;

	while (itemSnakeNode != NULL)
	{
		if (itemSnakeNode->pos_x == currentWeed->pos_x && itemSnakeNode->pos_y == currentWeed->pos_y) //判断蛇身是否与毒草重合
		{
			free(currentWeed);               //如果蛇身和毒草重合，那么释放毒草指针
			itemSnakeNode = itemSnakeNode->next;//遍历蛇的身体防止重合
			createPoisonousWeed();            //重新创建毒草
		}

		if (food != NULL && currentWeed->pos_x == food->pos_x && currentWeed->pos_y == food->pos_y)
		{
			free(currentWeed);               //如果毒草和食物重合，那么释放毒草指针
			createPoisonousWeed();            //重新创建毒草
		}
		if (mine1 != NULL && currentWeed->pos_x == mine1->pos_x && currentWeed->pos_y == mine1->pos_y)
		{
			free(currentWeed);               //如果毒草和食物重合，那么释放毒草指针
			createPoisonousWeed();            //重新创建毒草
		}
		itemSnakeNode = itemSnakeNode->next;
	}

	for (int i = 0; i < 40; i += 2)//障碍物检测
	{
		for (int j = 0; j < 26; j++)
		{
			if (Wall[i][j] == 1 && currentWeed->pos_x == i && currentWeed->pos_y == j)
			{
				free(currentWeed);         //如果食物和障碍物重合，那么释放食物指针
				createPoisonousWeed();            //重新创建食物
			}
		}
	}
	getXOY(currentWeed->pos_x, currentWeed->pos_y);
	poisonousWeed = currentWeed;          //成功创建毒草
	//free(currentWeed);
	currentWeed = NULL;
	color(5);
	printf("▲");           //输出毒草

}



/* 随机创建地雷*/
void createMine()
{
	minePtrTo currentMine;
	currentMine = (minePtrTo)malloc(sizeof(Mine));   //初始化food_1

	while ((currentMine->pos_x % 2) != 0)    				//保证其为偶数，使得毒草能与蛇头对其，然后毒草会出现在网格线上
	{
		currentMine->pos_x = (13*snakeHead->pos_x) % 52 + 2;              //毒草随机出现
	}

	currentMine->pos_y = (17*snakeTail->pos_y) % 24 + 1;
	itemSnakeNode = snakeHead;

	while (itemSnakeNode != NULL)
	{
		if (itemSnakeNode->pos_x == currentMine->pos_x && itemSnakeNode->pos_y == currentMine->pos_y) //判断蛇身是否与地雷重合
		{
			itemSnakeNode = itemSnakeNode->next;//遍历蛇的身体防止重合
			free(currentMine);        //如果蛇身和地雷重合，那么释放地雷指针
			createMine();            //重新创建地雷
		}

		if (food != NULL && currentMine->pos_x == food->pos_x && currentMine->pos_y == food->pos_y)
		{
			free(currentMine);          //如果地雷和食物重合，那么释放地雷指针
			createMine();              //重新创建地雷
		}
		if (poisonousWeed != NULL && currentMine->pos_x == poisonousWeed->pos_x && currentMine->pos_y == poisonousWeed->pos_y)
		{
			free(currentMine);         //如果地雷和食物重合，那么释放地雷指针
			createMine();            //重新创建地雷
		}
		itemSnakeNode = itemSnakeNode->next;
	}

	for (int i = 0; i < 40; i += 2)//障碍物检测
	{
		for (int j = 0; j < 26; j++)
		{
			if (Wall[i][j] == 1 && currentMine->pos_x == i && currentMine->pos_y == j)
			{
				free(currentMine);         //如果食物和障碍物重合，那么释放食物指针
				createMine();            //重新创建食物
			}
		}
	}
	getXOY(currentMine->pos_x, currentMine->pos_y);
	mine1 = currentMine;          //成功创建地雷
	//free(currentMine);
	currentMine = NULL;
	color(0);
	printf("●");           //输出地雷

}




/*判断是否咬到了自己*/

int biteSelf()
{
	snake* snakeNode;                  //定义snakeNode为蛇身上的一个节点
	snakeNode = snakeHead->next;        //snakeNode是蛇头之外的蛇身上的节点

	while (snakeNode != NULL)   //迭代判断是否重合
	{
		if (snakeNode->pos_x == snakeHead->pos_x && snakeNode->pos_y == snakeHead->pos_y)    //如果snakeNode和蛇身上的节点重合
		{
			return 1;       //返回1表示重合
		}
		snakeNode = snakeNode->next;
	}
	return 0;   //返回0表示没重合

}



/* 撞墙*/
void hitWall()
{
	if (snakeHead->pos_x == 0 || snakeHead->pos_x == 56 || snakeHead->pos_y == 0 || snakeHead->pos_y == 26) //如果蛇头碰壁
	{
		gameOverWay = 1;         //返回状态1
		overGame();              //结束界面
	}
	for (int i = 0; i < 54; i += 2)
	{
		for (int j = 0; j < 26; j++)
		{
			if (Wall[i][j] == 1 && snakeHead->pos_x == i && snakeHead->pos_y == j)
			{
				gameOverWay = 1;         //返回状态1
				overGame();              //结束界面
			}
		}
	}
}

int countHalfLength()
{
	int length=0;
	Head ptrl;
	ptrl = (Head)malloc(sizeof(snake));
	ptrl = snakeHead;
	while (ptrl != NULL)
	{
		length++;
		ptrl = ptrl->next;
	}
	length -= 1;//去除新增头
	//printf("长度是%d\n!", length);没问题
	return (length / 2);
}

/*撞到地雷*/
boolean hitMine(Head headPtr)
{
	
	if (mine1!=NULL&&headPtr->pos_x == mine1->pos_x && headPtr->pos_y == mine1->pos_y)	//如果遇到地雷
	{				
		int length = countHalfLength();
		if (headPtr==snakeTail->previous)//2个节点防止交叉(只有一个是基础节点)
		{
			//printf("刚好是前一个\n");
			overGame();
			return(TRUE);
		}
		else
		{
			while (length>=0&&snakeTail!=NULL)
			{
				//printf("执行过了碰撞\n");
				getXOY(snakeTail->pos_x, snakeTail->pos_y);
				color(8);
				printf("■");
				snakeTail = snakeTail->previous;
				free(snakeTail->next);
				snakeTail->next = NULL;
				length--;
			}			
		}
		while (itemSnakeNode!=NULL&&itemSnakeNode!=snakeTail)
		{
			getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
			color(14);
			printf("★");                          //原来食物的位置，从●换成★(由于之前已经增加了头结点，所以可以直接打印新的蛇身体)
			itemSnakeNode = itemSnakeNode->next;   //迭代打印蛇的身体
		}
		createMine(mine1);//重新创建地雷
		return(TRUE);
	}
	itemSnakeNode = headPtr;
	if (mine2!=NULL&&headPtr->pos_x == mine2->pos_x && headPtr->pos_y == mine2->pos_y)	//如果遇到地雷
	{
		int length2 = countHalfLength();
		if (headPtr == snakeTail->previous)//2个节点防止交叉(只有一个是基础节点)
		{
			//printf("刚好是前一个\n");
			overGame();
			return(TRUE);
		}
		else
		{
			while (length2 >= 0 && snakeTail != NULL)
			{
				//printf("执行过了碰撞\n");
				getXOY(snakeTail->pos_x, snakeTail->pos_y);
				color(8);
				printf("■");
				snakeTail = snakeTail->previous;
				free(snakeTail->next);
				snakeTail->next = NULL;
				length2--;
			}
		}
		while (itemSnakeNode != NULL && itemSnakeNode != snakeTail)
		{
			getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
			color(14);
			printf("★");                          //原来食物的位置，从●换成★(由于之前已经增加了头结点，所以可以直接打印新的蛇身体)
			itemSnakeNode = itemSnakeNode->next;   //迭代打印蛇的身体
		}
		createMine(mine2);//重新创建地雷
		return(TRUE);
	}
	
	return(FALSE);
}



/*吃到食物*/
boolean eatFood(Head headPtr)
{
	if (headPtr->pos_x == food->pos_x && headPtr->pos_y == food->pos_y)	//如果遇到食物
	{
		while (itemSnakeNode != NULL)
		{
			getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
			color(14);
			printf("★");                          //原来食物的位置，从●换成★(由于之前已经增加了头结点，所以可以直接打印新的蛇身体)
			itemSnakeNode = itemSnakeNode->next;   //迭代打印蛇的身体
		}
		score = score + scoreChange;        //吃了一个食物，在总分增加
		speedUp();                 //吃到食物的后续效果
		createFood();           //创建食物
		return(TRUE);
	}
	return(FALSE);
}

/*吃到毒草*/
boolean eatPoisonousWeed(Head headPtr)
{
	int flag = 0;
	if (headPtr->pos_x == poisonousWeed->pos_x && headPtr->pos_y == poisonousWeed->pos_y)	//如果遇到毒草
	{
		
		 score =2*score/3;       //吃了一个毒草，总分减少
		 if (headPtr == snakeTail->previous)//2个节点防止交叉(只有一个是基础节点)
		 {
			 //printf("刚好是前一个\n");
			 overGame();
			 return(TRUE);
		 }

		while (itemSnakeNode->next->next != NULL)
		{
			getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
			color(14);
			printf("★");                        //原来毒草的位置
			itemSnakeNode = itemSnakeNode->next; //迭代打印蛇的身体
			flag++;
		}

		if (flag == 0)
			overGame();

		getXOY(snakeTail->previous->pos_x, snakeTail->previous->pos_y);
		color(8);
		printf("■");
		getXOY(snakeTail->pos_x, snakeTail->pos_y);
		color(8);
		printf("■");

		snakeTail = snakeTail->previous->previous; 
		free(snakeTail->next->next);  //删除蛇尾
		snakeTail->next->next = NULL;

		free(snakeTail->next);  //删除蛇尾
		snakeTail->next = NULL;

		speedDown();                       //吃到毒草减速
		createPoisonousWeed();            //创建毒草
		return(TRUE);
	}
	return(FALSE);
}





/* 加速，蛇吃到食物会自动提速且修改食物分数，并且按F1会加速（有待修改！！！！！！！！！！！！！！！！！！！！！！！！！！！）*/
void speedUp()
{
	if (sleeptime >= 50)
	{
		sleeptime = sleeptime - 10;
		scoreChange = scoreChange + 6;
	}
}



/*加速，按F2会减速（有待修改！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！）*/
void speedDown()
{
	if (sleeptime < 350)               //如果时间间隔小于350
	{
		sleeptime = sleeptime + 30;     //时间间隔加上30
		scoreChange = scoreChange - 2;                  //每吃一次食物的得分减2
	}
}



/* 控制方向（双链表连接蛇的各个节点）*/
void snakeMove()	//蛇前进,上U,下D,左L,右R
{	
	hitWall();   //碰撞墙体检测
	Head nexthead;
	nexthead = (Head)malloc(sizeof(snake));		//为下一步开辟内存空间
	/*思想：每次移动过后都要重新打印蛇的身体*/

	if (status == UP)
	{
		nexthead->pos_x = snakeHead->pos_x;        //向上前进时，x坐标不动，y坐标-1
		nexthead->pos_y = snakeHead->pos_y - 1;
		snakeHead->previous = nexthead;
		nexthead->next = snakeHead;
		snakeHead = nexthead;            //无论中间过程如何head最终总要指向蛇头
		itemSnakeNode = snakeHead;      //指针itemSnakeNode指向新蛇头

		if (!eatFood(nexthead)&&!eatPoisonousWeed(nexthead)&&!hitMine(nexthead))
		{
			while (itemSnakeNode->next->next != NULL)//打印新增头结点，舍弃原来的尾节点（用两个next，删除尾结点时才不会删除itemSnakeNode（一直要用！））	
			{
				getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
				color(14);
				printf("★");           //蛇正常往前走，输出当前位置的蛇身
				itemSnakeNode = itemSnakeNode->next;            //迭代打印蛇的身体
			}
			snakeTail = snakeTail->previous;   //记录尾部节点
			getXOY(snakeTail->pos_x, snakeTail->pos_y);  //经过上面的循环，itemSnakeNode指向蛇尾
			color(14);
			printf("★");

			getXOY(snakeTail->next->pos_x, snakeTail->next->pos_y);  //经过上面的循环，itemSnakeNode指向蛇尾
			color(8);
			printf("■");                  //覆盖即将删除的尾节点（很重要，否则蛇会很长！！）
			free(snakeTail->next);      //进行输出■之后，释放指向尾节点的指针
			snakeTail->next = NULL;     //置空指向已经删除的尾结点的指针
		}
	}


	if (status == DOWN)
	{
		nexthead->pos_x = snakeHead->pos_x;        //向下前进时，x坐标不动，y坐标+1
		nexthead->pos_y = snakeHead->pos_y + 1;
		snakeHead->previous = nexthead;
		nexthead->next = snakeHead;
		snakeHead = nexthead;
		itemSnakeNode = snakeHead;

		if (!eatFood(nexthead) && !eatPoisonousWeed(nexthead) && !hitMine(nexthead))
		{
			while (itemSnakeNode->next->next != NULL)
			{
				getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
				color(14);
				printf("★");
				itemSnakeNode = itemSnakeNode->next;
			}
			snakeTail = snakeTail->previous;   //记录尾部节点
			getXOY(snakeTail->pos_x, snakeTail->pos_y);  //经过上面的循环，itemSnakeNode指向蛇尾
			color(14);
			printf("★");

			getXOY(snakeTail->next->pos_x, snakeTail->next->pos_y);  //经过上面的循环，itemSnakeNode指向蛇尾
			color(8);
			printf("■");                  //覆盖即将删除的尾节点（很重要，否则蛇会很长！！）
			free(snakeTail->next);      //进行输出■之后，释放指向尾节点的指针
			snakeTail->next = NULL;     //置空指向已经删除的尾结点的指针

		}
	}

	if (status == LEFT)
	{
		nexthead->pos_x = snakeHead->pos_x - 2;        //向左前进时，x坐标向左移动-2，y坐标不动
		nexthead->pos_y = snakeHead->pos_y;
		snakeHead->previous = nexthead;
     	nexthead->next = snakeHead;
		snakeHead = nexthead;
		itemSnakeNode = snakeHead;

		if (!eatFood(nexthead) && !eatPoisonousWeed(nexthead) && !hitMine(nexthead))
		{
			while (itemSnakeNode->next->next != NULL)
			{
				getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
				color(14);
				printf("★");
				itemSnakeNode = itemSnakeNode->next;
			}
			snakeTail = snakeTail->previous;   //记录尾部节点
			getXOY(snakeTail->pos_x, snakeTail->pos_y);  //经过上面的循环，itemSnakeNode指向蛇尾
			color(14);
			printf("★");

			getXOY(snakeTail->next->pos_x, snakeTail->next->pos_y);  //经过上面的循环，itemSnakeNode指向蛇尾
			color(8);
			printf("■");                  //覆盖即将删除的尾节点（很重要，否则蛇会很长！！）
			free(snakeTail->next);      //进行输出■之后，释放指向尾节点的指针
			snakeTail->next = NULL;     //置空指向已经删除的尾结点的指针
		}
	}

	if (status == Right)
	{
		nexthead->pos_x = snakeHead->pos_x + 2;        //向右前进时，x坐标向右移动+2，y坐标不动
		nexthead->pos_y = snakeHead->pos_y;
		snakeHead->previous = nexthead;
		nexthead->next = snakeHead;
		snakeHead = nexthead;
		itemSnakeNode = snakeHead;

		if (!eatFood(nexthead) && !eatPoisonousWeed(nexthead) && !hitMine(nexthead))
		{
			while (itemSnakeNode->next->next != NULL)
			{
				getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
				color(14);
				printf("★");
				itemSnakeNode = itemSnakeNode->next;
			}
			snakeTail = snakeTail->previous;   //记录尾部节点
			getXOY(snakeTail->pos_x, snakeTail->pos_y);  //经过上面的循环，itemSnakeNode指向蛇尾
			color(14);
			printf("★");

			getXOY(snakeTail->next->pos_x, snakeTail->next->pos_y);  //经过上面的循环，itemSnakeNode指向蛇尾
			color(8);
			printf("■");                  //覆盖即将删除的尾节点（很重要，否则蛇会很长！！）
			free(snakeTail->next);      //进行输出■之后，释放指向尾节点的指针
			snakeTail->next = NULL;     //置空指向已经删除的尾结点的指针
		}
	}

	if (biteSelf() == 1)       //判断是否咬到自身
	{
		gameOverWay = 2;
		overGame();
	}
}





/* 控制键盘按键 */
void keyboardControl()
{
	status = Right;       //初始蛇向右移动
	/*原则：不能反向转向*///GetAsyncKeyState函数用来判断函数调用时指定虚拟键的状态
	while (1)
	{
		score_and_Tips();
		if (GetAsyncKeyState(VK_UP) && status != DOWN)            
			status = UP;           

		else if (GetAsyncKeyState(VK_DOWN) && status != UP) 
			status = DOWN;

		else if (GetAsyncKeyState(VK_LEFT) && status != Right)    
			status = LEFT;

		else if (GetAsyncKeyState(VK_RIGHT) && status != LEFT)    
			status = Right;

		if (GetAsyncKeyState(VK_SPACE))		//按空格键暂停
		{
			for(;;)
			{
				Sleep(1000); //进程暂停1000s
				if (GetAsyncKeyState(VK_SPACE))  //再按空格解除暂停
					break;
			}
		}

		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			gameOverWay = 3;    //按esc键，直接到结束界面
			break;
		}

		Sleep(sleeptime);   //通过控制程序休眠来控制蛇运动的速度
		snakeMove();       //除非暂停，否则永远执行
	}
}




/*结束游戏*/
void overGame()
{
	
	system("cls");//清屏

	if (gameOverWay == 1)
	{
		getXOY(43, 9);
		color(12);
		printf("GAME  OVER !");
	}

	else if (gameOverWay == 2)
	{
		getXOY(43, 9);
		color(12);
		printf("GAME  OVER !");
	}

	else if (gameOverWay == 3)
	{
		getXOY(40, 9);
		color(12);
		printf("------成功退出游戏------");
	}

	getXOY(43, 12);
	color(13);
	printf("最终得分： %d", score);
	saveData(score);
	setChoice();
}



/* 边框下面的分支选项 */
void setChoice()
{
	int operateNum;

start:	
	getXOY(25, 23);
	color(12);
	printf("ReturnMenu ------ 1");

	getXOY(52, 23);
	printf("RestartGame ------ 2");

	getXOY(45, 25);
	color(11);
	printf("输入操作数1/2： ");
	scanf("%d", &operateNum);

	switch (operateNum)
	{
	case 1:
	{
		dataReInit();        //重新初始化数据
		welcomeToGame();
		break;
	}

	case 2:
	{
		//重新初始化游戏
		system("cls");       //清屏
		dataReInit();        //重新初始化数据

		if (gameWhich == 1)
		{
			createMap();    //创建地图1
			createMine();    //创建地雷
		}
		if (gameWhich == 2)
		{
			createMap_2();    //创建地图2
			createMine();    //创建地雷
		}
		if (gameWhich == 3)
		{
			createMap_3();    //创建地图3
			createMine();    //创建地雷
			createMine();    //创建地雷
		}
		initSnake();    //初始化蛇身
		createFood();       //创建食物
		createPoisonousWeed();//创建毒草
		
		keyboardControl();  //按键控制
		break;
	}

	default:
	{
		system("cls");
		overGame();
		//goto start;//goto switch的开始
		break;
	}
    }
}


/*主函数*/
int main()
{
	system("mode con cols=100 lines=30");   //设置控制台的宽高
	welcomeToGame();
	keyboardControl();
	return 0;
}


void saveData(int scoreNow) 
{
	struct DataStruct currentData;
	currentData.score = scoreNow;
	FILE* inFile;
	if ((inFile = fopen("score.dat", "a+")) == NULL)//报空文件
	{
		printf("OPEN FAIL!\n");
	}
	if (fwrite(&currentData, sizeof(struct DataStruct), 1, inFile) != 1)//没读到数据就报空文件
			printf("WRITE Fail!");
		fclose(inFile);		
}

void readData()
{
	system("cls");//清屏
	color(9);
	FILE* outFile;
	struct DataStruct dataArray[50],*ptr=dataArray;
	if ((outFile = fopen("score.dat", "rb")) == NULL)
		printf("ERROR READ");
	int count = 0;

	color(4);
	getXOY(30, 4);
	printf("分数排行榜");

	while (!feof(outFile))
	{
		if(fread(&dataArray[count], sizeof(struct DataStruct), 1, outFile)==1);
		{	
			
		}	
		count++;
	}
	
	PaiXu(ptr, count-1);
	if (count == 0)
	{
		color(3);
		getXOY(30, 10);
		printf("还没有游戏数据");
	}
		//显示数据		
		for (int i = 8; i < 18&& dataArray[i].score>=0; i++)//前面几次玩家刚开始熟悉游戏的数据不加入排行榜
		{		
			color(3);
			getXOY(30, 8 + 2 * i-12-4);
			printf("第%d名:%d", i + 1-8, dataArray[i].score);
		}
	

	color(4);
	getXOY(30, 24);
	printf("按任意键返回主菜单");

	_getch();                
	fclose(outFile);
	welcomeToGame();
}

 void PaiXu(struct DataStruct A[], int N)//适合小数据量的插入排序
{
	int j, p;
	int tmp;
	for (p = 1; p < N; p++)
	{
		tmp = A[p].score;
		for (j = p; j > 0 && A[j - 1].score < tmp; j--)
		{
			A[j].score= A[j - 1].score;
		}
		A[j].score = tmp;
	}
}
