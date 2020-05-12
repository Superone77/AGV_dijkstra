#pragma once
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

using namespace std;

#define INF 200000000
#define N 100



class Map
{
public:
	struct  Edge
	{
		int to;          // 边终止节点
		int cost;        // 花费

		Edge(int to1, int cost1)
		{
			to = to1;
			cost = cost1;
		}
	};
	struct Ans
	{
		vector<int> path;
		int cost;
		int start;

		void getCost()
		{
			cost = G1[start][path[0]];
			for (int unsigned i = 0; i < path.size() - 1; i++)
			{
				cost += G1[path[i]][path[i + 1]];
			}
		}
	};
	int startpoint;
	int turnMin;
	vector<Ans> paths;
	static int G1[N][N];                // 图的邻接矩阵形式
	int dist[N];                 // 从源点出发的最短距离
	int nV;                      // 顶点数
	int nE;
	vector<Edge> G[N];
	vector<Edge> G4[N];
	bool vis[N];
	typedef pair<int, int> P;    // first是最短距离，second是顶点编号
public:
	Map();
	~Map();
	void solve();
	void build();
	void dijkstra(int s, vector<Edge> G[N]);            // 求最短路径
	void addEdge(int from, int to, int cost, vector<Edge> G[N]);//双向赋值，1-2和2-1是一样的cost
	void dfs(int s, int t, Ans &A, vector< Ans > &paths, int start);

};