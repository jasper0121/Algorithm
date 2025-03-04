#include<iostream>
#include<vector>
#include<climits>
#include<cmath>
#include<set>
using namespace std;

struct edge //邊長(權重)、終點
{
	int weight = 0, end = 0;
};

int testNum = 1, nodeNum, lineNum, endNum; //測資、點個數、邊個數、終點個數
vector<int>nodeVal, dis; //每個點的初始預設值、距離(為(起點 - 終點)^3)
vector<vector<edge>>graph;
set<int> negative_ring; //將負環上的點存起來

void Bellman_Ford()
{
	dis[1] = 0; //初始將起點設為0
	for (nodeNum--; nodeNum--;) //Bellman_Ford的重點，總共跑nodeNum - 1次(除了起始點一開始就設為0)，每次都能使其中一點確定為最短路徑
	{
		for (int y = 1; y < graph.size(); y++)
		{
			for (int x = 0; x < graph[y].size(); x++)
			{
				//若當前點的值不是最大值，且之後連接到的點 > 當前的點 + 權重後的值
				if (dis[y] != INT_MAX && dis[graph[y][x].end] > dis[y] + graph[y][x].weight)
				{
					dis[graph[y][x].end] = dis[y] + graph[y][x].weight; //則將該值給之後連接到的點
				}
			}
		}
	}

	for (int y = 1; y < graph.size(); y++) //此時所有點的值皆為最短路徑(然而若有負環則無法確定最短路徑的值，但可藉此判斷是否有負環)
	{
		for (int x = 0; x < graph[y].size(); x++)
		{
			if (dis[graph[y][x].end] > dis[y] + graph[y][x].weight) //若之後連接到的點的值還能再更短
			{
				dis[graph[y][x].end] = dis[y] + graph[y][x].weight; //則繼續將值改更小
				negative_ring.insert(graph[y][x].end); //並加入set中(在負環之中則總有一天值一定會小於3)
			}
		}
	}
}

int main()
{
	for (; cin >> nodeNum; negative_ring.clear())
	{
		graph.assign(nodeNum + 1, vector<edge>()); //不用0
		nodeVal.assign(nodeNum + 1, int()); //不用0
		dis.assign(nodeNum + 1, INT_MAX); //不用0
		for (int i = 1; i <= nodeNum; cin >> nodeVal[i++]); //存入每個點的值
		cin >> lineNum;	
		for (int y; lineNum--;) //建圖
		{
			cin >> y;
			graph[y].push_back(edge());
			cin >> graph[y].back().end;
			graph[y].back().weight = pow(nodeVal[graph[y].back().end] - nodeVal[y], 3); //題目要求權重為(起點 - 終點)^3
		}

		if (nodeNum) //若點個數非0就跑演算法
		{
			Bellman_Ford();
		}

		cin >> endNum; //輸入要走到的終點個數
		cout << "Set #" << testNum++ << endl;
		for (int end; endNum--;)
		{
			cin >> end;
			if (negative_ring.count(end) || dis[end] < 3 || dis[end] == INT_MAX) //若所求的終點存在於負環 || 值 < 3 || 無法走到
			{
				cout << "?" << endl; //則輸出問號
				continue;
			}

			cout << dis[end] << endl; //否則輸出最短路徑
		}
	}

	system("pause");
}