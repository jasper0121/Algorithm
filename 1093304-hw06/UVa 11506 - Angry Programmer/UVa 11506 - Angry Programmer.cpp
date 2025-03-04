#include<iostream>
#include<queue>
#include<climits>
using namespace std;

vector<int>layer; //所有點和0的最短距離，同時代表層數，若該點的層數非0則代表可以從起點走到該點(起點的0除外)
vector<vector<int>>graph;

int dinicBFS()
{
	queue<int>temp;
	layer.assign(graph.size(), int()); //初始各點的層數皆設為0
	temp.push(1); //初始將起點設為0
	layer[1] = 1; //起點的layer設為1
	for (int y; temp.size();) //y == 當前的點、若queue的size()不為0
	{
		y = temp.front(); //每次將queue最前面的元素拿出來
		temp.pop(); //之後將queue中的該元素刪掉
		for (int x = 1; x < graph[y].size(); x++) //每次從x = 1開始(若從0開始則帶入以下條件會有例外)
		{
			if (graph[y][x] && layer[x] == 0) //若y→x間還有容量，且還未設定x位於第幾層
			{
				layer[x] = layer[y] + 1; //則將x設為y的層數 + 1
				temp.push(x); //並將該點加入queue中
			}
		}
	}

	return layer.back(); //最後回傳終點的層數，若終點的層數為0，則代表從起點已經無法走到終點
}

int dinicDFS(int cur, int capacity) //當前的點、容量，初始傳入起點、容量無限
{
	if (cur == graph.size() - 1) //若走到終點
	{
		return capacity; //則回傳當前的容量(此時會是最小容量)
	}

	for (int minCapacity, x = 0; x < graph[cur].size(); x++) //從起點到當前點之間所經過的最小容量；目標從1開始
	{
		//若當前的容量非0，路線沿著階層的順序走，在該條路線上找出最小的容量，且該容量非0時
		if (graph[cur][x] && layer[x] == layer[cur] + 1 && (minCapacity = dinicDFS(x, min(graph[cur][x], capacity))))
		{
			graph[cur][x] -= minCapacity; //當前路線上的每個容量 - 路線上所找到的最小容量
			graph[x][cur] += minCapacity; //當前路線上的每個剩餘容量 + 路線上所找到的最小容量
			return minCapacity; //回傳該條路徑上所找到的最小容量
		}
	}

	return 0; //若當前已沒有任何路徑可以走到終點，則回傳0
}

void dinic()
{
	int maxflow = 0; //該網路的最大流量
	while (dinicBFS()) //每次先BFS一次，若回傳值非0，代表還能繼續算最大流量
	{
		for (int min; min = dinicDFS(1, INT_MAX); maxflow += min); //每次找出該路徑上的最小容量，並將其值加入最大流量中，若min == 0則代表結束
	}

	cout << maxflow << endl; //輸出最大流量
}

int main()
{
	for (int nodeNum, edgeNum, node, capacity; cin >> nodeNum >> edgeNum, nodeNum;)
	{
		graph.assign(2 * nodeNum + 1, vector<int>(2 * nodeNum + 1));
		for (int i = nodeNum - 2; i--;) //先做拆點
		{
			cin >> node >> capacity;
			graph[node][node + nodeNum] = graph[node + nodeNum][node] = capacity;
		}

		for (int start, end; edgeNum--;) //無向圖建圖
		{
			cin >> start >> end >> capacity;
			graph[start][end + nodeNum] = graph[end][start + nodeNum] = capacity;
		}

		dinic(); //使用dinic演算法找最大流量(綜合BFS和DFS)
	}

	system("pause");
}