#include<iostream>
#include<vector>
#include<set>
using namespace std;

int nodeNum; //點個數
vector<vector<int>>graph, reGraph; //圖與反向圖
vector<int>power, dis; //權重與距離
set<int>path; //存實際會經過的點

void dfs(int node) //此時實際上是從終點走回起點
{
	path.insert(node); //每次將路徑上會經過的點存入set中(若起點或終點其中一點不在set裡，代表起點走不到終點)
	for (int x = 0; x < reGraph[node].size(); x++)
	{
		if (path.count(reGraph[node][x]) == 0) //若沒經過，則存入set中
		{
			dfs(reGraph[node][x]);
		}
	}
}

void Bellman_Ford() //平時都是用此演算法找距離起點的最短路徑及負環，此題完全相反，需要找最大距離及正環
{
	dis[1] = 100; //初始能量預設為100
	for (int i = 0; i < nodeNum - 1; i++) //Bellman_Ford的重點，總共跑nodeNum - 1次(除了起始點一開始就設為0)，每次都能使其中一點確定為最短路徑
	{
		for (int y = 1; y < graph.size(); y++)
		{
			for (int x = 0; x < graph[y].size(); x++)
			{
				//若當前點的值非0，且之後連接到的點 < 當前的點 + 權重後的值
				if (dis[y] && dis[graph[y][x]] < dis[y] + power[graph[y][x]])
				{
					dis[graph[y][x]] = dis[y] + power[graph[y][x]]; //則將該值給之後連接到的點
				}
			}
		}
	}

	for (int y = 1; y < graph.size(); y++) //此時所有點的值皆為最大路徑(然而若有正環則無法確定最大路徑的值，但可藉此判斷是否有正環)
	{
		for (int x = 0; x < graph[y].size(); x++)
		{
			//若當前點的值非0 && 該點在鎖定的路徑上 && 之後連接到的點的值還能再更大
			if (dis[y] && path.count(graph[y][x]) && dis[graph[y][x]] < dis[y] + power[graph[y][x]])
			{
				cout << "winnable\n"; //代表可以走到終點
				return;
			}
		}
	}

	cout << (dis[nodeNum] ? "winnable\n" : "hopeless\n"); //若執行到此，代表無正環。若終點的值非0則代表可以走到終點
}

int main()
{
	for (; cin >> nodeNum, nodeNum != -1; path.clear()) //每次輸入點個數、若輸入-1則結束；每次清空set
	{
		graph.assign(nodeNum + 1, vector<int>()); //0不用
		reGraph.assign(nodeNum + 1, vector<int>()); //建反向圖，目的是確認起點是否能夠走到終點，並且同時鎖定路徑(將會經過的點存起來)，0不用
		power.assign(nodeNum + 1, int()); //每一點的能量消耗，可看成走到該點的道路(權重)，0不用
		dis.assign(nodeNum + 1, int()); //每一點距離起點的最短路徑，0不用
		for (int linkNum, x, y = 1; y <= nodeNum; y++) //建圖
		{
			for (cin >> power[y] >> linkNum; linkNum--;)
			{
				cin >> x;
				graph[y].push_back(x);
				reGraph[x].push_back(y);
			}
		}

		dfs(nodeNum); //先跑dfs鎖定之後要跑的路徑
		Bellman_Ford();
	}

	system("pause");
}