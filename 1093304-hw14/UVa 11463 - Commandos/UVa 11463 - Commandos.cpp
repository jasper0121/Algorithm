#include<iostream>
#include<vector>
#define INF 10000000
using namespace std;

int main()
{
	vector<vector<int>>graph;
	int testCase;
	cin >> testCase;
	for (int node, line, Case = 1; testCase--;)
	{
		cin >> node >> line; //輸入建築物個數(點個數)、道路數
		graph.assign(node, vector<int>(node, INF)); //初始權重設為無限大
		for (int i = 0; i < graph.size(); i++) //自己走到自己的路徑長必定為0
		{
			graph[i][i] = 0;
		}

		for (int u, v; line--;) //建雙向圖
		{
			cin >> u >> v;
			graph[u][v] = graph[v][u] = 1; //2點間的距離(權重)固定為1
		}

		for (int mid = 0; mid < graph.size(); mid++) //佛洛依德演算法，所有u到v的可能路徑中，取路線最短者
		{
			for (int u = 0; u < graph.size(); u++)
			{
				for (int v = 0; v < graph.size(); v++)
				{
					graph[u][v] = min(graph[u][v], graph[u][mid] + graph[mid][v]);
				}
			}
		}

		int start, end, maxDis = 0; //起點、終點、最大距離
		cin >> start >> end;
		//題目求所有點都走完並走到終點所花的最短時間，且由於有多個人同時從起點出發
		for (int mid = 0; mid < graph.size(); mid++) //因此此題等同於「起點 → 最遠的點 → 終點」所走的最大距離
		{
			maxDis = max(maxDis, graph[start][mid] + graph[mid][end]);
		}

		cout << "Case " << Case++ << ": " << maxDis << "\n"; //最後印出最大距離
	}

	system("pause");
}