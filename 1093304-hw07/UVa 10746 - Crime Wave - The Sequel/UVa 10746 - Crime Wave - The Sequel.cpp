#include<iostream>
#include<iomanip>
#include<queue>
#include<climits>
using namespace std;

struct edge //容量和花費
{
	double capacity, cost;
};

int car, bank; //車數、銀行數
vector<bool>inQueue; //當前的元素是否在Queue中
vector<int>parent;
vector<double>dis;  //距離原點到當前點所需的總cost
vector<vector<edge>>graph; //每個邊存有容量與花費

bool SPFA(const int& start, const int& end)
{
	parent.assign(graph.size(), 0); //parent初始化
	dis.assign(graph.size(), INT_MAX); //距離初始為最大
	inQueue.assign(graph.size(), false); //所有在queue中的狀態都預設為false
	queue<int>q;
	dis[start] = 0.0; //起點的距離為0
	q.push(start);
	for (int u; q.size();)
	{
		u = q.front();
		q.pop();
		inQueue[u] = false;
		for (int v = start; v <= end; v++) //對於所有的點
		{
			//若u → v 有容量(代表2點間建立邊)，且接下來要走到的點，其cost > 當前2點間的cost
			if (graph[u][v].capacity && dis[v] > dis[u] + graph[u][v].cost)
			{
				dis[v] = dis[u] + graph[u][v].cost; //則更新dis[v]到原點所花的cost
				parent[v] = u; //v的parent設為u
				if (inQueue[v] == false) //若對象v不在Queue
				{
					q.push(v); //則將其加入queue中
					inQueue[v] = true; //在queue中的狀態設為true
				}
			}
		}
	}

	return dis[end] != INT_MAX; //若終點的dis == 最大值，代表已經無路可走到終點，回傳false
}

void MCMF(const int& start, const int& end)
{
	double minCost = 0.0; //最小花費
	while (SPFA(start, end))
	{
		double minCapacity = INT_MAX; //初始將最小容量設為最大值
		for (int v = end; v != start; v = parent[v]) //v從終點開始；若v還沒走到起點；每次往前走到v的parent
		{
			minCapacity = min(minCapacity, graph[parent[v]][v].capacity); //2容量取最小
		}

		minCost += minCapacity * dis[end]; //dis[nodeNum] == 1單位capacity從起點到終點所需的最小花費
		for (int v = end; v != start; v = parent[v]) //v從終點開始；若v還沒走到起點；每次往前走到v的parent
		{
			graph[parent[v]][v].capacity -= minCapacity; //該條路徑上所有的capacity - 最小的capacity
			graph[v][parent[v]].capacity += minCapacity; //該條路線上的反向capacity + 最小的capacity
		}
	}

	cout << fixed << setprecision(2) << minCost / bank + 0.001 << endl; //最後輸出平均時間
}

int main()
{
	while (cin >> bank >> car, bank) //初始先輸入銀行和車的數量
	{
		graph.assign(car + bank + 2, vector<edge>(car + bank + 2));
		for (int b = 1; b <= bank; b++) //建圖，此題為有向邊
		{
			for (int c = 1; c <= car; c++)
			{
				cin >> graph[c][car + b].cost;
				graph[car + b][c].cost = -graph[c][car + b].cost; //反向的cost為負
				graph[c][car + b].capacity = 1; //所有capacity都預設為1
			}
		}

		for (int i = 1; i <= car; i++) //從最初原點對於每台車的capacity也都設為1
		{
			graph[0][i].capacity = 1;
		}

		for (int i = car + 1; i < graph.size() - 1; i++) //編號從car + 1起就是銀行位置編號
		{
			graph[i][graph.size() - 1].capacity = 1; //對於所有的銀行都連線至一個終點
		}

		MCMF(0, graph.size() - 1); //起點為0
	}

	system("pause");
}