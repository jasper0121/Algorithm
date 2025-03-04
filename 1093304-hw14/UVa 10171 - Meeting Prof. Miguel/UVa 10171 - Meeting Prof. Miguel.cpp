#include<iostream>
#include<vector>
#define INF 100000000
using namespace std;

int main()
{
	vector<vector<int>>graph[2]; //graph[0] == 年輕人的地圖、graph[1] == 老人的地圖
	for (int street, weight; cin >> street, street; cout << "\n") //道路數，權重(道路長度)
	{
		int maxPos = 0; //紀錄當前最大的道路編號
		graph[0].assign(26, vector<int>(26, INF)); //道路編號範圍只有A ~ Z，初始權重設為無限大
		graph[1] = graph[0]; //初始老人的地圖和年輕人相同
		for (char age, connect, u, v; street--;)
		{
			cin >> age >> connect >> u >> v >> weight; //輸入年齡(Y == 年輕人、M == 老人)、是否雙向連通(B == 雙向)、起點與終點、道路長(權重)
			maxPos = max(maxPos, max(u, v) - 'A'); //找最大的道路編號
			graph[age == 'M'][u - 'A'][v - 'A'] = weight; //建年輕人與老人的圖
			if (connect == 'B') //若connect == 'B'則該條道路建成雙向
			{
				graph[age == 'M'][v - 'A'][u - 'A'] = weight;
			}
		}

		for (int i = 0; i <= maxPos; i++) //自己走到自己的路徑長必定為0
		{
			graph[0][i][i] = graph[1][i][i] = 0;
		}

		for (int mid = 0; mid <= maxPos; mid++) //佛洛依德演算法，所有u到v的可能路徑中，取路線最短者
		{
			for (int u = 0; u <= maxPos; u++)
			{
				for (int v = 0; v <= maxPos; v++)
				{
					graph[0][u][v] = min(graph[0][u][v], graph[0][u][mid] + graph[0][mid][v]);
					graph[1][u][v] = min(graph[1][u][v], graph[1][u][mid] + graph[1][mid][v]);
				}
			}
		}

		char start[2]; //年輕人與老人的起點
		cin >> start[0] >> start[1];
		int minDis = INF; //先找出2人會合的最短距離
		for (int end = 0; end <= maxPos; end++)
		{
			minDis = min(minDis, graph[0][start[0] - 'A'][end] + graph[1][start[1] - 'A'][end]);
		}

		if (minDis == INF) //若最短距離仍為無限大，則代表2人無法會合
		{
			cout << "You will never meet.";
			continue;
		}

		cout << minDis; //反之則印出2人會合的最短距離
		for (int end = 0; end <= maxPos; end++) //印出最短距離的會合地點，若有多個地點的最短距離相同則都印出
		{
			if (minDis == graph[0][start[0] - 'A'][end] + graph[1][start[1] - 'A'][end])
			{
				cout << " " << char(end + 'A');
			}
		}
	}

	system("pause");
}