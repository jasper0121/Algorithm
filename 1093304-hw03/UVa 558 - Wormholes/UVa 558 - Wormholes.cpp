#include<iostream>
#include<vector>
#include<climits>
using namespace std;

struct edge //邊的長度(權重)及終點
{
	int weight = 0, end = 0;
};

int testCase, nodeNum, lineNum; //測資、點個數、邊個數
vector<vector<edge>>graph; //每一格內有邊長及終點

void Bellman_Ford()
{
	vector<int>dis(nodeNum, INT_MAX); //初始各個點的值都設為最大值
	dis[0] = 0; //初始將起點設為0
	for (nodeNum--; nodeNum--; ) //Bellman_Ford的重點，總共跑nodeNum - 1次(除了起始點一開始就設為0)，每次都能使其中一點確定為最短路徑
	{
		for (int y = 0; y < graph.size(); y++)
		{
			for (int x = 0; x < graph[y].size(); x++)
			{
				if (dis[y] != INT_MAX && dis[graph[y][x].end] > dis[y] + graph[y][x].weight) //若當前點的值不是最大值
				{
					//若之後連接到的點 > 當前的點 + 權重後的值，則將該值給之後連接到的點
					dis[graph[y][x].end] = dis[y] + graph[y][x].weight;
				}
			}
		}
	}

	for (int y = 0; y < graph.size(); y++) //此時所有點的值皆為最短路徑(然而若有負環則無法確定最短路徑的值，但可藉此判斷是否有負環)
	{
		for (int x = 0; x < graph[y].size(); x++)
		{
			if (dis[graph[y][x].end] > dis[y] + graph[y][x].weight) //若之後連接到的點的值還能再更短
			{
				cout << "possible\n"; //則代表有負環
				return;
			}
		}
	}

	cout << "not possible\n"; //能執行到此則代表沒有負環
}

int main()
{
	for (cin >> testCase; testCase--;)
	{
		cin >> nodeNum >> lineNum; //每次輸入點個數和邊個數
		graph.assign(nodeNum, vector<edge>()); //建圖
		for (int y; lineNum--;)
		{
			cin >> y;
			graph[y].push_back(edge());
			cin >> graph[y].back().end >> graph[y].back().weight;
		}

		Bellman_Ford();
	}

	system("pause");
}