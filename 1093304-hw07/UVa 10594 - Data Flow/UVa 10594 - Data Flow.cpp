#include<iostream>
#include<queue>
#include<climits>
using  ll_int = long long;
using namespace std;

struct Edge //每一條edge存有起點、終點、容量、消耗
{
	int start, end, capacity;
	ll_int cost;
	Edge(const int& s, const int& e, const int& ca, const ll_int& co)
	{
		start = s;
		end = e;
		capacity = ca;
		cost = co;
	}
};

int  nodeNum, edgeNum, dataSize, capacitySize; //點個數、邊總數、要傳送的資料大小、每條邊的容量
vector<Edge>edge; //對於無向圖，每2點間要存4條邊
vector<vector<int>>graph; //outgoingEdges，存每個點連到下個點在edge中的位置(index)
vector<ll_int>dis, parent; //dis相當於，距離原點到當前點所需的總cost
vector<bool>inQueue; //當前的元素是否在Queue中

void addEdge(const int& start, const int& end, const int& capacity, const ll_int& cost, int& edgeNo) //建立邊
{
	edge.push_back({ end,start, 0,-cost }); //先建立反向的邊
	graph[start].push_back(edgeNo++); //這樣才能在graph用start連到end(這裡push_back的是剛剛建的edge index)
	edge.push_back({ start, end,capacity,cost }); //再來建正向邊
	graph[end].push_back(edgeNo++); //在graph用end連到start
}

bool SPFA(const int& start, const int& end)
{
	parent.assign(nodeNum + 1, -1); //parent初始化
	dis.assign(nodeNum + 1, LLONG_MAX); //距離初始為最大
	inQueue.assign(nodeNum + 1, false); //所有在queue中的狀態都預設為false
	queue<int>q;
	dis[start] = 0; //起點的距離為0
	q.push(start);
	for (int u, v; q.size();)
	{
		u = q.front();
		q.pop();
		inQueue[u] = false;
		for (int e : graph[u]) //對於u點連接到的所有邊(e == 邊的編號)
		{
			v = edge[e].start; //每次將queue最前面的元素拿出來，每個邊的start就是u所連接到的點
			if (edge[e].capacity && dis[v] > dis[u] + edge[e].cost) //若該邊上還有容量，且接下來要走到的點，其cost > 當前點累積的cost + 2點間的cost
			{
				dis[v] = dis[u] + edge[e].cost; //則更新dis[v]到原點所花的cost
				parent[v] = e; //將當前edge的start的parent設為所在的index
				if (inQueue[v] == false) //若對象v不在Queue
				{
					q.push(v); //則將其加入queue中
					inQueue[v] = true; //在queue中的狀態設為true
				}
			}
		}
	}

	return dis[nodeNum] != LLONG_MAX; //若終點的dis == 最大值，代表已經無路可走到終點，回傳false
}

void MCMF(const int& start, const int& end)
{
	ll_int maxflow = 0, minCost = 0; //最大流量，最小花費
	while (SPFA(start, end))
	{
		int minCapacity = INT_MAX; //初始將最小容量設為最大值
		//v從終點開始；若v還沒走到起點；parent[v] == 該邊所在index，所以edge[parent[v]].end == 該邊的start
		for (int v = end; v != start; v = edge[parent[v]].end)
		{
			minCapacity = min(minCapacity, edge[parent[v]].capacity); //2容量取最小
		}

		maxflow += minCapacity; //當次路徑上最小的capacity == 當次路徑上所能產生的最大流量
		minCost += minCapacity * dis[nodeNum]; //dis[nodeNum] == 1單位capacity從起點到終點所需的最小花費
		//v從終點開始；若v還沒走到起點；parent[v] == 該邊所在index，所以edge[parent[v]].end == 該邊的start
		for (int v = end; v != start; v = edge[parent[v]].end)
		{
			edge[parent[v]].capacity -= minCapacity; //該條路徑上所有的capacity - 最小的capacity
			edge[parent[v] ^ 1].capacity += minCapacity; //該條路線上的反向capacity + 最小的capacity
		}
	}

	if (maxflow >= dataSize) //若maxflow最後 >= 資料大小，代表整個資料都能夠藉由此網路傳輸
	{
		cout << minCost << "\n"; //故輸出最小的花費
		return;
	}

	cout << "Impossible.\n";
}

int main()
{
	for (int start, end, cost, edgeNo; cin >> nodeNum >> edgeNum; edge.clear()) //對於之後要存的所有邊給予一個編號、每次輸入點個數和邊個數
	{
		graph.assign(nodeNum + 1, vector<int>()); //點個數 + 起點
		for (addEdge(0, 1, 1, 0, edgeNo = 0); edgeNum--;) //建圖(存邊的方式)，初始建立原點，其capacity == 之後要輸入的dataSize
		{
			cin >> start >> end >> cost;
			addEdge(start, end, 1, cost, edgeNo); //正向建邊
			addEdge(end, start, 1, cost, edgeNo); //反向建邊
		}

		cin >> dataSize >> capacitySize; //輸入要傳輸的資料大小、所有路上的capacity大小
		edge[0].capacity = dataSize; //原點的capacity == 資料大小
		for (int i = 2; i < edge.size(); i++)
		{
			edge[i].capacity *= capacitySize; //原本基礎容量只有1或0，所以要全部 * capacitySize才是真正的capacity
		}

		MCMF(0, nodeNum); //從0號點跑到nodeNum號點
	}

	system("pause");
}