typedef struct snake 		//蛇身的一个节点
{
	int pos_x;
	int pos_y;
	struct snake* previous;
	struct snake* next;	
}snake,*Head, * Tail;

typedef struct Food
{
	int pos_x;
	int pos_y;
}Food,*foodPtrTo;

typedef struct Mine
{
	int pos_x;
	int pos_y;
}Mine, * minePtrTo;

typedef struct PoisonousWeed
{
	int pos_x;
	int pos_y;
}PoisonousWeed, * poisonousWeedPtrTo;

typedef struct WisedomGrass
{
	int pos_x;
	int pos_y;
}WisedomGrass,* wisedomGrassPtrTo;

typedef struct DataStruct
{
	int score;
};