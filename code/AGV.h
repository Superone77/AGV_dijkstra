#include"Map.h"
#include<queue>

using namespace std;

class AGV
{
public:
	~AGV();
	Map *agvMap;
	int next_point;
	int this_point;
	bool checkFree = true;//是否有任务给AGV
	queue<int> agv_path;
	int i=0;
public:
	void setStart(bool (&isFull)[N][N] ,int t); //将路径输入AGV
	void move(); //移动
};