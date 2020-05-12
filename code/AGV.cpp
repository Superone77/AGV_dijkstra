#include"AGV.h"
#include<iostream>

using namespace std;


AGV::~AGV()
{
	delete agvMap;
	agvMap=NULL;
}

void
AGV::move() //移动
{
	if (checkFree)
		next_point = this_point;
	else 
	{
		this_point = next_point;
		if (i != 1)
		{
			next_point = agv_path.front();
			agv_path.pop(); 
		}
		
	}
	if (agv_path.empty())
	{
		if (i == 1)
		{
			checkFree = true;
			i = 0;
			delete agvMap;
			agvMap = NULL;
		}
		i++;
	}

	    
	cout << this_point << endl;
}

void
AGV::setStart(bool (&isFull)[N][N],int t) 
{
	cout << "setStart" << endl;
	checkFree = false;  
	next_point = agvMap->startpoint;
	int time = t;
	for (int k = 0; i < agvMap->paths.size(); i++) //通过换路径防止碰撞
	{
		for (int j = 0; j < agvMap->paths[k].path.size(); j++)
		{
			if (isFull[agvMap->paths[k].path[j]][time])
			{
				cout << "已被占用的节点" << agvMap->paths[k].path[j] << "---" << "第" << time << "s" << endl;
				while (!agv_path.empty())
				{
					agv_path.pop();
					cout << "删除尾节点" << endl;
				}
				for (j=j-1;j >=0; j--)
				{
					cout << "释放占用的节点" << endl;
					isFull[agvMap->paths[k].path[j]][time] = false;
					time--;
				}
				if (j == 0)
					time = t;
				break;
			}
			agv_path.push(agvMap->paths[k].path[j]);
			cout << "成功占用节点：" << agvMap->paths[k].path[j] << "---" << "第" << time << "s" << endl;
			isFull[agvMap->paths[k].path[j]][time] = true;
			time++;
		}

		if (!agv_path.empty())
			break;
	}
	if (agv_path.empty()) //通过碰撞前停止防止碰撞
	{
		for (int j = 0; j < agvMap->paths[0].path.size(); j++)
		{
			if (isFull[agvMap->paths[0].path[j]][time])
			{
				j--;
				agv_path.push(agvMap->paths[0].path[j]);
				isFull[agvMap->paths[0].path[j]][time] = true;
				time++;
				continue;
				

			}
			agv_path.push(agvMap->paths[0].path[j]);
			isFull[agvMap->paths[0].path[j]][time] = true;
			time++;
		}
	}
	i = 0;
		

	
}