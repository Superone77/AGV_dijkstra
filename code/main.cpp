#include <iostream>
#include "string"
#include "fstream"
#include "vector"
#include "queue"
#include "sstream"
#include "set"
#include "string.h"
#include "math.h"
#include <functional>
#include "AGV.h"
#include"Map.h"

using namespace std;

int main()
{
	bool isFull[N][N]; // 前一个参数是点，后一个参数是时间，表示什么时间什么点被占据
	AGV agv1;
	AGV agv2;
	int time = 1; //初始化时间
	Map map;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			isFull[i][j] = false; 
		}
	}
	
	while (true)
	{
		cout << "第" << time << "秒：" << endl;
		if (agv1.checkFree)
		{
			int n;
			cout << "是有否任务给1号车（0.是，1.否）" << endl;
			cin >> n;
			if (n == 0)
			{
				
				agv1.agvMap = new Map;
				agv1.agvMap->solve();
				agv1.setStart(isFull,time);
				

			}
		}
		if (agv2.checkFree)
		{
			int n;
			cout << "是否有任务给2号车（0.是，1.否）" << endl;
			cin >> n;
			if (n == 0)
			{
				
				agv2.agvMap = new Map;
				agv2.agvMap->solve();
				agv2.setStart(isFull,time);
			}

		}
		cout << "A:";
		agv1.move();
		cout << "B:";
		agv2.move();
		
		time++;
		if (time == 10)
			exit(0);
	}



	return 0;
}

