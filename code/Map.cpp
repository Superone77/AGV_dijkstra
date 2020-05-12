#include"AGV.h"
#include"Map.h"




Map::Map()
{

}

int Map::G1[N][N];

Map::~Map()
{
	
}

void Map::addEdge(int from, int to, int cost, vector<Edge> G[N])//双向赋值，1-2和2-1是一样的cost
{
	Edge e(to, cost);
	G[from].push_back(e);

	Edge e1(from, cost);
	G[to].push_back(e1);
}

void Map::solve()
{
	int sta, finall;
	cout << "请输入起点:" << endl;
	cin >> sta;
	startpoint = sta;
	cout << "请输入终点:" << endl;
	cin >> finall;

	build();
	dijkstra(sta, G);

	int unsigned i, j;


	//vector<Ans> paths;
	Ans ans;
	memset(vis, false, sizeof(vis));

	dfs(sta, finall, ans, paths, sta);

	cout << endl << sta << "到" << finall << "的所有最短路径：" << endl;
	int tsize;
	tsize = paths.size();
	int *t = new int[tsize];
	for (i = 0; i < paths.size(); i++)
	{
		*(t + i) = 0;
		cout << sta << " - ";
		for (j = 0; j < paths[i].path.size(); j++)
		{
			cout << paths[i].path[j] << " - ";
			if (j > 1 && abs(paths[i].path[j] - paths[i].path[j - 2]) != 22 && abs(paths[i].path[j] - paths[i].path[j - 2]) != 2)
			{
				*(t + i) += 1;
			}
			else if (j == 1 && abs(paths[i].path[j] - sta) != 22 && abs(paths[i].path[j] - sta) != 2)
			{
				*(t + i) += 1;
			}
		}
		cout << "---cost：" << paths[i].cost << "   " << "转弯数：" << *(t + i) << endl;
	}
	cout << "     " << endl;
	cout << "     " << endl;
	turnMin = 1000;
	for (i = 0; i < paths.size(); i++) //寻找最小转弯数
	{
		if (turnMin > *(t + i))
		{
			turnMin = *(t + i);
		}
	}
	cout << "最优路径为：  " << endl;
	for (i = 0; i < paths.size(); i++) //输出最小转弯数所对应的路径
	{
		if (*(t + i) == turnMin)
		{
			cout << sta << " - ";
			for (j = 0; j < paths[i].path.size(); j++)
			{
				cout << paths[i].path[j] << " - ";
			}
			cout << "---cost：" << paths[i].cost << "   " << "转弯数：" << turnMin << endl;
		}
	}
	cout << "     " << endl;
	cout << "次优路径为：  " << endl;
	for (i = 0; i < paths.size(); i++) //输出次小转弯数所对应的路径
	{
		if (*(t + i) == turnMin + 1)
		{
			cout << sta << " -";
			for (j = 0; j < paths[i].path.size(); j++)
			{
				cout << paths[i].path[j] << " - ";
			}
			cout << "---cost：" << paths[i].cost << "   " << "转弯数：" << turnMin + 1 << endl;
		}
	}
}
void Map::build()
{
	int i;
	ifstream fin;
	fin.open("data.txt");
	fin >> nV;//输入顶点数
	fin >> nE;//输入边数

	// 输入图，初始化为所有两点距离为INF
	for (i = 0; i < nV; i++)
	{
		for (int j = i; j < nV; j++)
		{
			G1[i][j] = G1[j][i] = INF;
		}
	}
	int from, to, cost;//输入两点间距离
	for (i = 0; i < nE; i++)
	{
		fin >> from >> to >> cost;

		addEdge(from, to, cost, G);
		G1[from][to] = G1[to][from] = cost;
	}
	fin.close();
}

void Map::dijkstra(int s, vector<Edge> G[N]) // 求最短路径
{
	fill(dist, dist + nV + 1, INF);
	priority_queue<P, vector<P>, greater<P> > q;
	dist[s] = 0;
	q.push(P(0, s));
	while (!q.empty())
	{
		P p = q.top();   //从尚未使用的顶点中找到一个距离最小的顶点
		q.pop();
		int v = p.second;
		if (dist[v] < p.first)
			continue;
		for (int unsigned i = 0; i < G[v].size(); i++)
		{
			Edge &e = G[v][i];
			int dis = dist[v] + e.cost;
			if (dist[e.to] > dis)
			{
				dist[e.to] = dist[v] + e.cost;
				q.push(P(dist[e.to], e.to));
				G4[v].push_back(e);
			}
			else if (dist[e.to] == dis)
			{
				G4[v].push_back(e);
			}
		}
	}
}

void Map::dfs(int s, int t, Ans &A, vector< Ans > &paths, int start)
{
	if (s == t)
	{
		A.start = start;
		A.getCost();
		paths.push_back(A);
	}

	for (int unsigned i = 0; i < G4[s].size(); i++)
	{
		int u = G4[s][i].to;
		if (!vis[u])
		{
			vis[u] = true;
			A.path.push_back(u);
			dfs(u, t, A, paths, start);
			A.path.pop_back();
			vis[u] = false;
		}
	}
}