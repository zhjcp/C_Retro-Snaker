
#define _CRT_SECURE_NO_WARNINGS 1

#include"snake.h";
#include<stdio.h>			
#include<time.h>			
#include<windows.h>		
#include<stdlib.h>			
#include<conio.h>			//���ռ����������



#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4B00
#define Right 0x4D00      //�ߵ�״̬��U���� ��D���£�L:�� R����



int Wall[54][26];
int status;
int score = 0, scoreChange = 10;
int status, sleeptime = 200;	//��ǰ��״̬��ÿ�����е�ʱ����
Head snakeHead;	//��ͷָ��
Tail snakeTail;//��βָ��
snake* itemSnakeNode;		//�߽ڵ�ָ���м����
foodPtrTo food;  //ʳ��ָ��
minePtrTo mine1;  //����ָ��
minePtrTo mine2;  //����ָ��2
int mineCount = 0;
poisonousWeedPtrTo poisonousWeed; //����ָ��
int gameOverWay = 0;		//��Ϸ����
static int gameWhich = 0;
int randNum=0;
HANDLE controlHandle;				//����̨���





/*******��  ��  ��  �� *******/

void getXOY(int x, int y);   //���ù��λ��

int color(int c);           //����������ɫ

void welcomeToGame();       //��ʼ����

void dataReInit();          //�����ٴγ�ʼ��

void createMap();           //���Ƶ�ͼ

void createMap_2();         //���Ƶ�ͼ2
  
void createMap_3();        //���Ƶ�ͼ2

void score_and_Tips();		//��Ϸ�����Ҳ�ĵ÷ֺ�С��ʾ

void initSnake();           //��ʼ������������

void createFood();          //�������������ʳ��

void createPoisonousWeed();     //������������ֶ���

void createMine();         //������������ֵ���

int biteSelf();             //�ж��Ƿ�ҧ�����Լ�

void hitWall();       //������ײǽ�����

void speedUp();				//����

void speedDown();			//����

void snakeMove();           //������ǰ������

void keyboardControl();     //���Ƽ��̰���

void overGame();             //��Ϸ����

void saveData(int score);

void readData();

void PaiXu();

void setChoice();				//��Ϸʧ��֮���ѡ��

void explationGame();           //��Ϸ˵��



/* ���ù��λ��*/
void getXOY(int x, int y)
{
	COORD currentPlace;
	currentPlace.X = x;
	currentPlace.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPlace);//ʹ��굽currentλ��
}



/* ������ɫ����*/
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);   //����������ɫ 
	return 0;   //GetStdHandle�������ر�׼��������豸�ľ����������ʶ��ͬ�豸����ֵ��
}


//��ʼ����
void welcomeToGame()
{ 
    char menuOperate;
	getXOY(39, 2);
	color(6);
	printf("̰   ��   ��");

	color(12);
	getXOY(40, 6);
	printf("1.��ģʽ");

	getXOY(40, 8);
	printf("2.����ģʽ");

	getXOY(40, 10);
	printf("3.����ģʽ");

	getXOY(40, 14);
	printf("4.���а�");

	getXOY(40, 16);
	printf("5.��Ϸ˵��");

	getXOY(40, 18);
	printf("6.�˳���Ϸ");

	getXOY(40, 27);
	color(3);
	printf("���������1/2/3: ");

	color(14);
	scanf("%c", &menuOperate);    		//����ѡ��

	switch (menuOperate)
	{
	   case '1':
	  {
		  gameWhich = 1;
		  system("cls");  //�����Ļ(׼����ʼ����Ļ��
		  createMap();    //������ͼ
		  initSnake();    //��ʼ������
		  createFood();       //����ʳ��
		  createPoisonousWeed();//��������
		  createMine(mine1);    //��������
		  keyboardControl();  //��������
		  break;
	  }

	   case '2':
	   {
		   gameWhich = 2;
		   sleeptime = 100;
		   system("cls");  //�����Ļ(׼����ʼ����Ļ��
		   createMap_2();    //������ͼ
		   initSnake();    //��ʼ������
		   createFood();       //����ʳ��
		   createPoisonousWeed();//��������
		   createMine(mine1);    //��������
		   keyboardControl();  //��������
		   break;
	   }

	   case '3':
	   {
		   gameWhich = 3;
		   sleeptime = 120;
		   system("cls");  //�����Ļ(׼����ʼ����Ļ��
		   createMap_3();    //������ͼ
		   initSnake();    //��ʼ������
		   createFood();       //����ʳ��
		   createPoisonousWeed();//��������
		   createMine(mine1);    //��������
		   createMine(mine2);    //��������
		   keyboardControl();  //��������
		   break;
	   }

	   case '4':
	   {
		   readData();      	//�����а�
		   break;
	   }

	   case '6':
	   {
		   exit(0);     		//�˳���Ϸ
		   break;
	   }

	  default:
	  {
		system("cls");		//����
		welcomeToGame();
	  }
	}
}

//������ͼ
void createMap()
{
	for (int x = 0; x < 58; x +=2)		//���±߽磨һ����Ϊ2��
	{
		color(5);

		getXOY(x, 0);		
		printf("��");

		getXOY(x, 26);
		printf("��");
	}

	for (int y = 1; y< 26; y++)		//���ұ߽磨һ����Ϊ1��
	{
		getXOY(0, y);
		printf("��");

		getXOY(56, y);
		printf("��");
	}

	for (int x = 2; x < 56; x += 2)	//�м�����
	{
		for (int y = 1; y < 26; y++)
		{
			getXOY(x, y);
			color(8);
			printf("��");
		}
	}
}

//������ͼ2
void createMap_2()
{
	for (int x = 0; x < 58; x += 2)		//���±߽磨һ����Ϊ2��
	{
		color(5);

		getXOY(x, 0);
		printf("��");

		getXOY(x, 26);
		printf("��");
	}

	for (int y = 1; y < 26; y++)		//���ұ߽磨һ����Ϊ1��
	{
		getXOY(0, y);
		printf("��");

		getXOY(56, y);
		printf("��");
	}

	for (int x = 2; x < 56; x += 2)	//�м�����
	{
		for (int y = 1; y < 26; y++)
		{
			getXOY(x, y);
			color(8);
			printf("��");
		}
	}

	for (int x = 20; x < 36; x+=2)
	{
		getXOY(x, 5);
		color(5);
		printf("��");

		getXOY(x, 20);
		color(5);
		printf("��");

		Wall[x][5] = 1;
		Wall[x][20] = 1;
	}
}


//������ͼ3
void createMap_3()
{
	for (int x = 0; x < 58; x += 2)		//���±߽磨һ����Ϊ2��
	{
		color(5);

		getXOY(x, 0);
		printf("��");

		getXOY(x, 26);
		printf("��");
	}

	for (int y = 1; y < 26; y++)		//���ұ߽磨һ����Ϊ1��
	{
		getXOY(0, y);
		printf("��");

		getXOY(56, y);
		printf("��");
	}

	for (int x = 2; x < 56; x += 2)	//�м�����
	{
		for (int y = 1; y < 26; y++)
		{
			getXOY(x, y);
			color(8);
			printf("��");
		}
	}

	for (int x = 20; x < 36; x += 2)
	{
		getXOY(x, 5);
		color(5);
		printf("��");

		getXOY(x, 20);
		color(5);
		printf("��");

		Wall[x][5] = 1;
		Wall[x][20] = 1;
	}

	for (int y = 7; y < 18; y++)
	{
		getXOY(8, y);
		color(5);
		printf("��");

		getXOY(46, y);
		color(5);
		printf("��");

		Wall[8][y] = 1;
		Wall[46][y] = 1;
	}
}




/*  ��Ϸ�����Ҳ�ĵ÷ֺ�С��ʾ����Ҫ�޸ģ�������������������������������������������������������������������*/
void score_and_Tips()
{
	color(14);
	getXOY(64, 8);	
	printf("�÷֣�%d  ", score);

	getXOY(64, 14);
	printf("�ո���ͣ��Ϸ");

	getXOY(64, 16);
	printf("ESC ���˳���Ϸ");
}


void dataReInit()
{
	for (int i = 0; i < 40; i += 2)
	{
		for (int j = 0; j < 26; j++)
			Wall[i][j] = 0;
	}
    score = 0, scoreChange = 10;			//�ܵ÷���ÿ�γ�ʳ��÷�
	if(gameWhich==1)
    sleeptime = 200;
	if (gameWhich == 2)
		sleeptime = 100;
	if (gameWhich == 3)
		sleeptime = 150;
}


/*��ʼ������(˫����*/
void initSnake()
{
	/*˫����*/
	snakeTail = (Tail)malloc(sizeof(snake));//����β��ʼ���룬ÿ�β��붼���µ�ͷ��
	snakeTail->pos_x = 24;         	//�ߵĳ�ʼλ�ã�24,5��
	snakeTail->pos_y = 10;

    snakeHead = (Head)malloc(sizeof(snake)); //��ʼ����ͷ
	snakeTail->previous = snakeHead;
	snakeHead->next = snakeTail;
	snakeHead->pos_x = 24 + 2 * 1;  //����ȫ����ͷλ��
	snakeHead->pos_y =10;
	snakeTail->next = NULL;
	

    getXOY(snakeTail->pos_x, snakeTail->pos_y);
	color(14);
	printf("��");       //�����������ʹ�á����

	getXOY(snakeHead->pos_x, snakeHead->pos_y);
	color(14);
	printf("��");       //�����������ʹ�á����
}



/* �������ʳ��*/
void createFood()
{
	foodPtrTo currentFood;
	currentFood = (foodPtrTo)malloc(sizeof(Food));   //��ʼ��food_1

	while ((currentFood->pos_x % 2) != 0)    				//��֤��Ϊż����ʹ��ʳ��������ͷ���䣬Ȼ��ʳ����������������
	{
		currentFood->pos_x = (3*snakeHead->pos_x) % 52 + 2;              //ʳ���������
	}

	currentFood->pos_y = (7* snakeTail->pos_y) % 24 + 1;
	itemSnakeNode = snakeHead;

	while (itemSnakeNode != NULL)
	{
		if (itemSnakeNode->pos_x == currentFood->pos_x && itemSnakeNode->pos_y == currentFood->pos_y) //�ж������Ƿ���ʳ���غ�
		{
			free(currentFood);               //��������ʳ���غϣ���ô�ͷ�ʳ��ָ��
			createFood();                   //���´���ʳ��
		}
		if (poisonousWeed != NULL && poisonousWeed->pos_x == currentFood->pos_x && poisonousWeed->pos_y == currentFood->pos_y)
		{
			free(currentFood);         //���ʳ��Ͷ����غϣ���ô�ͷ�ʳ��ָ��
			createFood();            //���´���ʳ��
		}
		if (mine1 != NULL && currentFood->pos_x == mine1->pos_x && currentFood->pos_y == mine1->pos_y)
		{
			free(currentFood);         //���ʳ��Ͷ����غϣ���ô�ͷ�ʳ��ָ��
			createFood();            //���´���ʳ��
		}
		itemSnakeNode = itemSnakeNode->next;
	}

	for (int i = 0; i < 40; i += 2)//�ϰ�����
	{
		for (int j = 0; j < 26; j++)
		{
			if (Wall[i][j] == 1 && currentFood->pos_x == i && currentFood->pos_y == j)
			{
				free(currentFood);         //���ʳ����ϰ����غϣ���ô�ͷ�ʳ��ָ��
				createFood();            //���´���ʳ��
			}
		}
	}
	getXOY(currentFood->pos_x, currentFood->pos_y);
	food = currentFood;          //�ɹ�����ʳ��
	//free(currentFood);
	currentFood = NULL;
	color(12);
	printf("��");           //���ʳ��

}

/* �����������*/
void createPoisonousWeed()
{
	poisonousWeedPtrTo currentWeed;
	currentWeed = (poisonousWeedPtrTo)malloc(sizeof(PoisonousWeed));   //��ʼ��food_1

	while ((currentWeed->pos_x % 2) != 0)    				//��֤��Ϊż����ʹ�ö���������ͷ���䣬Ȼ�󶾲ݻ��������������
	{
		currentWeed->pos_x = (5*snakeHead->pos_x) % 52 + 2;              //�����������
	}

	currentWeed->pos_y = (11* snakeTail->pos_y) % 24 + 1;
	itemSnakeNode = snakeHead;

	while (itemSnakeNode != NULL)
	{
		if (itemSnakeNode->pos_x == currentWeed->pos_x && itemSnakeNode->pos_y == currentWeed->pos_y) //�ж������Ƿ��붾���غ�
		{
			free(currentWeed);               //�������Ͷ����غϣ���ô�ͷŶ���ָ��
			itemSnakeNode = itemSnakeNode->next;//�����ߵ������ֹ�غ�
			createPoisonousWeed();            //���´�������
		}

		if (food != NULL && currentWeed->pos_x == food->pos_x && currentWeed->pos_y == food->pos_y)
		{
			free(currentWeed);               //������ݺ�ʳ���غϣ���ô�ͷŶ���ָ��
			createPoisonousWeed();            //���´�������
		}
		if (mine1 != NULL && currentWeed->pos_x == mine1->pos_x && currentWeed->pos_y == mine1->pos_y)
		{
			free(currentWeed);               //������ݺ�ʳ���غϣ���ô�ͷŶ���ָ��
			createPoisonousWeed();            //���´�������
		}
		itemSnakeNode = itemSnakeNode->next;
	}

	for (int i = 0; i < 40; i += 2)//�ϰ�����
	{
		for (int j = 0; j < 26; j++)
		{
			if (Wall[i][j] == 1 && currentWeed->pos_x == i && currentWeed->pos_y == j)
			{
				free(currentWeed);         //���ʳ����ϰ����غϣ���ô�ͷ�ʳ��ָ��
				createPoisonousWeed();            //���´���ʳ��
			}
		}
	}
	getXOY(currentWeed->pos_x, currentWeed->pos_y);
	poisonousWeed = currentWeed;          //�ɹ���������
	//free(currentWeed);
	currentWeed = NULL;
	color(5);
	printf("��");           //�������

}



/* �����������*/
void createMine()
{
	minePtrTo currentMine;
	currentMine = (minePtrTo)malloc(sizeof(Mine));   //��ʼ��food_1

	while ((currentMine->pos_x % 2) != 0)    				//��֤��Ϊż����ʹ�ö���������ͷ���䣬Ȼ�󶾲ݻ��������������
	{
		currentMine->pos_x = (13*snakeHead->pos_x) % 52 + 2;              //�����������
	}

	currentMine->pos_y = (17*snakeTail->pos_y) % 24 + 1;
	itemSnakeNode = snakeHead;

	while (itemSnakeNode != NULL)
	{
		if (itemSnakeNode->pos_x == currentMine->pos_x && itemSnakeNode->pos_y == currentMine->pos_y) //�ж������Ƿ�������غ�
		{
			itemSnakeNode = itemSnakeNode->next;//�����ߵ������ֹ�غ�
			free(currentMine);        //�������͵����غϣ���ô�ͷŵ���ָ��
			createMine();            //���´�������
		}

		if (food != NULL && currentMine->pos_x == food->pos_x && currentMine->pos_y == food->pos_y)
		{
			free(currentMine);          //������׺�ʳ���غϣ���ô�ͷŵ���ָ��
			createMine();              //���´�������
		}
		if (poisonousWeed != NULL && currentMine->pos_x == poisonousWeed->pos_x && currentMine->pos_y == poisonousWeed->pos_y)
		{
			free(currentMine);         //������׺�ʳ���غϣ���ô�ͷŵ���ָ��
			createMine();            //���´�������
		}
		itemSnakeNode = itemSnakeNode->next;
	}

	for (int i = 0; i < 40; i += 2)//�ϰ�����
	{
		for (int j = 0; j < 26; j++)
		{
			if (Wall[i][j] == 1 && currentMine->pos_x == i && currentMine->pos_y == j)
			{
				free(currentMine);         //���ʳ����ϰ����غϣ���ô�ͷ�ʳ��ָ��
				createMine();            //���´���ʳ��
			}
		}
	}
	getXOY(currentMine->pos_x, currentMine->pos_y);
	mine1 = currentMine;          //�ɹ���������
	//free(currentMine);
	currentMine = NULL;
	color(0);
	printf("��");           //�������

}




/*�ж��Ƿ�ҧ�����Լ�*/

int biteSelf()
{
	snake* snakeNode;                  //����snakeNodeΪ�����ϵ�һ���ڵ�
	snakeNode = snakeHead->next;        //snakeNode����ͷ֮��������ϵĽڵ�

	while (snakeNode != NULL)   //�����ж��Ƿ��غ�
	{
		if (snakeNode->pos_x == snakeHead->pos_x && snakeNode->pos_y == snakeHead->pos_y)    //���snakeNode�������ϵĽڵ��غ�
		{
			return 1;       //����1��ʾ�غ�
		}
		snakeNode = snakeNode->next;
	}
	return 0;   //����0��ʾû�غ�

}



/* ײǽ*/
void hitWall()
{
	if (snakeHead->pos_x == 0 || snakeHead->pos_x == 56 || snakeHead->pos_y == 0 || snakeHead->pos_y == 26) //�����ͷ����
	{
		gameOverWay = 1;         //����״̬1
		overGame();              //��������
	}
	for (int i = 0; i < 54; i += 2)
	{
		for (int j = 0; j < 26; j++)
		{
			if (Wall[i][j] == 1 && snakeHead->pos_x == i && snakeHead->pos_y == j)
			{
				gameOverWay = 1;         //����״̬1
				overGame();              //��������
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
	length -= 1;//ȥ������ͷ
	//printf("������%d\n!", length);û����
	return (length / 2);
}

/*ײ������*/
boolean hitMine(Head headPtr)
{
	
	if (mine1!=NULL&&headPtr->pos_x == mine1->pos_x && headPtr->pos_y == mine1->pos_y)	//�����������
	{				
		int length = countHalfLength();
		if (headPtr==snakeTail->previous)//2���ڵ��ֹ����(ֻ��һ���ǻ����ڵ�)
		{
			//printf("�պ���ǰһ��\n");
			overGame();
			return(TRUE);
		}
		else
		{
			while (length>=0&&snakeTail!=NULL)
			{
				//printf("ִ�й�����ײ\n");
				getXOY(snakeTail->pos_x, snakeTail->pos_y);
				color(8);
				printf("��");
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
			printf("��");                          //ԭ��ʳ���λ�ã��ӡ񻻳ɡ�(����֮ǰ�Ѿ�������ͷ��㣬���Կ���ֱ�Ӵ�ӡ�µ�������)
			itemSnakeNode = itemSnakeNode->next;   //������ӡ�ߵ�����
		}
		createMine(mine1);//���´�������
		return(TRUE);
	}
	itemSnakeNode = headPtr;
	if (mine2!=NULL&&headPtr->pos_x == mine2->pos_x && headPtr->pos_y == mine2->pos_y)	//�����������
	{
		int length2 = countHalfLength();
		if (headPtr == snakeTail->previous)//2���ڵ��ֹ����(ֻ��һ���ǻ����ڵ�)
		{
			//printf("�պ���ǰһ��\n");
			overGame();
			return(TRUE);
		}
		else
		{
			while (length2 >= 0 && snakeTail != NULL)
			{
				//printf("ִ�й�����ײ\n");
				getXOY(snakeTail->pos_x, snakeTail->pos_y);
				color(8);
				printf("��");
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
			printf("��");                          //ԭ��ʳ���λ�ã��ӡ񻻳ɡ�(����֮ǰ�Ѿ�������ͷ��㣬���Կ���ֱ�Ӵ�ӡ�µ�������)
			itemSnakeNode = itemSnakeNode->next;   //������ӡ�ߵ�����
		}
		createMine(mine2);//���´�������
		return(TRUE);
	}
	
	return(FALSE);
}



/*�Ե�ʳ��*/
boolean eatFood(Head headPtr)
{
	if (headPtr->pos_x == food->pos_x && headPtr->pos_y == food->pos_y)	//�������ʳ��
	{
		while (itemSnakeNode != NULL)
		{
			getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
			color(14);
			printf("��");                          //ԭ��ʳ���λ�ã��ӡ񻻳ɡ�(����֮ǰ�Ѿ�������ͷ��㣬���Կ���ֱ�Ӵ�ӡ�µ�������)
			itemSnakeNode = itemSnakeNode->next;   //������ӡ�ߵ�����
		}
		score = score + scoreChange;        //����һ��ʳ����ܷ�����
		speedUp();                 //�Ե�ʳ��ĺ���Ч��
		createFood();           //����ʳ��
		return(TRUE);
	}
	return(FALSE);
}

/*�Ե�����*/
boolean eatPoisonousWeed(Head headPtr)
{
	int flag = 0;
	if (headPtr->pos_x == poisonousWeed->pos_x && headPtr->pos_y == poisonousWeed->pos_y)	//�����������
	{
		
		 score =2*score/3;       //����һ�����ݣ��ּܷ���
		 if (headPtr == snakeTail->previous)//2���ڵ��ֹ����(ֻ��һ���ǻ����ڵ�)
		 {
			 //printf("�պ���ǰһ��\n");
			 overGame();
			 return(TRUE);
		 }

		while (itemSnakeNode->next->next != NULL)
		{
			getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
			color(14);
			printf("��");                        //ԭ�����ݵ�λ��
			itemSnakeNode = itemSnakeNode->next; //������ӡ�ߵ�����
			flag++;
		}

		if (flag == 0)
			overGame();

		getXOY(snakeTail->previous->pos_x, snakeTail->previous->pos_y);
		color(8);
		printf("��");
		getXOY(snakeTail->pos_x, snakeTail->pos_y);
		color(8);
		printf("��");

		snakeTail = snakeTail->previous->previous; 
		free(snakeTail->next->next);  //ɾ����β
		snakeTail->next->next = NULL;

		free(snakeTail->next);  //ɾ����β
		snakeTail->next = NULL;

		speedDown();                       //�Ե����ݼ���
		createPoisonousWeed();            //��������
		return(TRUE);
	}
	return(FALSE);
}





/* ���٣��߳Ե�ʳ����Զ��������޸�ʳ����������Ұ�F1����٣��д��޸ģ�������������������������������������������������������*/
void speedUp()
{
	if (sleeptime >= 50)
	{
		sleeptime = sleeptime - 10;
		scoreChange = scoreChange + 6;
	}
}



/*���٣���F2����٣��д��޸ģ�����������������������������������������������������������������������������*/
void speedDown()
{
	if (sleeptime < 350)               //���ʱ����С��350
	{
		sleeptime = sleeptime + 30;     //ʱ��������30
		scoreChange = scoreChange - 2;                  //ÿ��һ��ʳ��ĵ÷ּ�2
	}
}



/* ���Ʒ���˫���������ߵĸ����ڵ㣩*/
void snakeMove()	//��ǰ��,��U,��D,��L,��R
{	
	hitWall();   //��ײǽ����
	Head nexthead;
	nexthead = (Head)malloc(sizeof(snake));		//Ϊ��һ�������ڴ�ռ�
	/*˼�룺ÿ���ƶ�����Ҫ���´�ӡ�ߵ�����*/

	if (status == UP)
	{
		nexthead->pos_x = snakeHead->pos_x;        //����ǰ��ʱ��x���겻����y����-1
		nexthead->pos_y = snakeHead->pos_y - 1;
		snakeHead->previous = nexthead;
		nexthead->next = snakeHead;
		snakeHead = nexthead;            //�����м�������head������Ҫָ����ͷ
		itemSnakeNode = snakeHead;      //ָ��itemSnakeNodeָ������ͷ

		if (!eatFood(nexthead)&&!eatPoisonousWeed(nexthead)&&!hitMine(nexthead))
		{
			while (itemSnakeNode->next->next != NULL)//��ӡ����ͷ��㣬����ԭ����β�ڵ㣨������next��ɾ��β���ʱ�Ų���ɾ��itemSnakeNode��һֱҪ�ã�����	
			{
				getXOY(itemSnakeNode->pos_x, itemSnakeNode->pos_y);
				color(14);
				printf("��");           //��������ǰ�ߣ������ǰλ�õ�����
				itemSnakeNode = itemSnakeNode->next;            //������ӡ�ߵ�����
			}
			snakeTail = snakeTail->previous;   //��¼β���ڵ�
			getXOY(snakeTail->pos_x, snakeTail->pos_y);  //���������ѭ����itemSnakeNodeָ����β
			color(14);
			printf("��");

			getXOY(snakeTail->next->pos_x, snakeTail->next->pos_y);  //���������ѭ����itemSnakeNodeָ����β
			color(8);
			printf("��");                  //���Ǽ���ɾ����β�ڵ㣨����Ҫ�������߻�ܳ�������
			free(snakeTail->next);      //���������֮���ͷ�ָ��β�ڵ��ָ��
			snakeTail->next = NULL;     //�ÿ�ָ���Ѿ�ɾ����β����ָ��
		}
	}


	if (status == DOWN)
	{
		nexthead->pos_x = snakeHead->pos_x;        //����ǰ��ʱ��x���겻����y����+1
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
				printf("��");
				itemSnakeNode = itemSnakeNode->next;
			}
			snakeTail = snakeTail->previous;   //��¼β���ڵ�
			getXOY(snakeTail->pos_x, snakeTail->pos_y);  //���������ѭ����itemSnakeNodeָ����β
			color(14);
			printf("��");

			getXOY(snakeTail->next->pos_x, snakeTail->next->pos_y);  //���������ѭ����itemSnakeNodeָ����β
			color(8);
			printf("��");                  //���Ǽ���ɾ����β�ڵ㣨����Ҫ�������߻�ܳ�������
			free(snakeTail->next);      //���������֮���ͷ�ָ��β�ڵ��ָ��
			snakeTail->next = NULL;     //�ÿ�ָ���Ѿ�ɾ����β����ָ��

		}
	}

	if (status == LEFT)
	{
		nexthead->pos_x = snakeHead->pos_x - 2;        //����ǰ��ʱ��x���������ƶ�-2��y���겻��
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
				printf("��");
				itemSnakeNode = itemSnakeNode->next;
			}
			snakeTail = snakeTail->previous;   //��¼β���ڵ�
			getXOY(snakeTail->pos_x, snakeTail->pos_y);  //���������ѭ����itemSnakeNodeָ����β
			color(14);
			printf("��");

			getXOY(snakeTail->next->pos_x, snakeTail->next->pos_y);  //���������ѭ����itemSnakeNodeָ����β
			color(8);
			printf("��");                  //���Ǽ���ɾ����β�ڵ㣨����Ҫ�������߻�ܳ�������
			free(snakeTail->next);      //���������֮���ͷ�ָ��β�ڵ��ָ��
			snakeTail->next = NULL;     //�ÿ�ָ���Ѿ�ɾ����β����ָ��
		}
	}

	if (status == Right)
	{
		nexthead->pos_x = snakeHead->pos_x + 2;        //����ǰ��ʱ��x���������ƶ�+2��y���겻��
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
				printf("��");
				itemSnakeNode = itemSnakeNode->next;
			}
			snakeTail = snakeTail->previous;   //��¼β���ڵ�
			getXOY(snakeTail->pos_x, snakeTail->pos_y);  //���������ѭ����itemSnakeNodeָ����β
			color(14);
			printf("��");

			getXOY(snakeTail->next->pos_x, snakeTail->next->pos_y);  //���������ѭ����itemSnakeNodeָ����β
			color(8);
			printf("��");                  //���Ǽ���ɾ����β�ڵ㣨����Ҫ�������߻�ܳ�������
			free(snakeTail->next);      //���������֮���ͷ�ָ��β�ڵ��ָ��
			snakeTail->next = NULL;     //�ÿ�ָ���Ѿ�ɾ����β����ָ��
		}
	}

	if (biteSelf() == 1)       //�ж��Ƿ�ҧ������
	{
		gameOverWay = 2;
		overGame();
	}
}





/* ���Ƽ��̰��� */
void keyboardControl()
{
	status = Right;       //��ʼ�������ƶ�
	/*ԭ�򣺲��ܷ���ת��*///GetAsyncKeyState���������жϺ�������ʱָ���������״̬
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

		if (GetAsyncKeyState(VK_SPACE))		//���ո����ͣ
		{
			for(;;)
			{
				Sleep(1000); //������ͣ1000s
				if (GetAsyncKeyState(VK_SPACE))  //�ٰ��ո�����ͣ
					break;
			}
		}

		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			gameOverWay = 3;    //��esc����ֱ�ӵ���������
			break;
		}

		Sleep(sleeptime);   //ͨ�����Ƴ����������������˶����ٶ�
		snakeMove();       //������ͣ��������Զִ��
	}
}




/*������Ϸ*/
void overGame()
{
	
	system("cls");//����

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
		printf("------�ɹ��˳���Ϸ------");
	}

	getXOY(43, 12);
	color(13);
	printf("���յ÷֣� %d", score);
	saveData(score);
	setChoice();
}



/* �߿�����ķ�֧ѡ�� */
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
	printf("���������1/2�� ");
	scanf("%d", &operateNum);

	switch (operateNum)
	{
	case 1:
	{
		dataReInit();        //���³�ʼ������
		welcomeToGame();
		break;
	}

	case 2:
	{
		//���³�ʼ����Ϸ
		system("cls");       //����
		dataReInit();        //���³�ʼ������

		if (gameWhich == 1)
		{
			createMap();    //������ͼ1
			createMine();    //��������
		}
		if (gameWhich == 2)
		{
			createMap_2();    //������ͼ2
			createMine();    //��������
		}
		if (gameWhich == 3)
		{
			createMap_3();    //������ͼ3
			createMine();    //��������
			createMine();    //��������
		}
		initSnake();    //��ʼ������
		createFood();       //����ʳ��
		createPoisonousWeed();//��������
		
		keyboardControl();  //��������
		break;
	}

	default:
	{
		system("cls");
		overGame();
		//goto start;//goto switch�Ŀ�ʼ
		break;
	}
    }
}


/*������*/
int main()
{
	system("mode con cols=100 lines=30");   //���ÿ���̨�Ŀ��
	welcomeToGame();
	keyboardControl();
	return 0;
}


void saveData(int scoreNow) 
{
	struct DataStruct currentData;
	currentData.score = scoreNow;
	FILE* inFile;
	if ((inFile = fopen("score.dat", "a+")) == NULL)//�����ļ�
	{
		printf("OPEN FAIL!\n");
	}
	if (fwrite(&currentData, sizeof(struct DataStruct), 1, inFile) != 1)//û�������ݾͱ����ļ�
			printf("WRITE Fail!");
		fclose(inFile);		
}

void readData()
{
	system("cls");//����
	color(9);
	FILE* outFile;
	struct DataStruct dataArray[50],*ptr=dataArray;
	if ((outFile = fopen("score.dat", "rb")) == NULL)
		printf("ERROR READ");
	int count = 0;

	color(4);
	getXOY(30, 4);
	printf("�������а�");

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
		printf("��û����Ϸ����");
	}
		//��ʾ����		
		for (int i = 8; i < 18&& dataArray[i].score>=0; i++)//ǰ�漸����Ҹտ�ʼ��Ϥ��Ϸ�����ݲ��������а�
		{		
			color(3);
			getXOY(30, 8 + 2 * i-12-4);
			printf("��%d��:%d", i + 1-8, dataArray[i].score);
		}
	

	color(4);
	getXOY(30, 24);
	printf("��������������˵�");

	_getch();                
	fclose(outFile);
	welcomeToGame();
}

 void PaiXu(struct DataStruct A[], int N)//�ʺ�С�������Ĳ�������
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
