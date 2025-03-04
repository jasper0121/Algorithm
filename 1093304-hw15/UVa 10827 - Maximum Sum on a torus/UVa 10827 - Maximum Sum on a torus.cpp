#include<iostream>
#include<vector>
#define INF 100000000
using namespace std;

vector<vector<int>>graph; //矩陣
vector<int>rowSum; //當前的行加總

int max1D()
{
	int localMax, globalMax, localMin, globalMin, total; //區域和全域的最大及最小值，當前子矩陣內的總和
	globalMax = localMax = globalMin = localMin = total = rowSum[0]; //初始都設為行加總中的第一個數
	for (int i = 1; i < rowSum.size(); i++)
	{
		total += rowSum[i]; //將當前子矩陣的值加總
		//算出當前最大的子矩陣和
		localMax = max(localMax + rowSum[i], rowSum[i]);
		globalMax = max(globalMax, localMax);
		//由於題目的矩陣上下互通，故再算出當前最小的子矩陣和，所求即可視為「整個矩陣 - 最小的子矩陣」
		localMin = min(localMin + rowSum[i], rowSum[i]);
		globalMin = min(globalMin, localMin);
	}

	return max(globalMax, total - globalMin); //沒上下相通的矩陣和有上下相通的矩陣中取較大的一方回傳
}

int main()
{
	int testCase;
	cin >> testCase;
	for (int N; testCase--;)
	{
		cin >> N; //矩陣邊長
		graph.assign(N, vector<int>(N)); //建立N * N的矩陣
		for (int y = 0; y < graph.size(); y++) //輸入矩陣中每一格的值
		{
			for (int x = 0; x < graph[y].size(); cin >> graph[y][x++]);
		}

		int globalMax = -INF; //最大的子矩陣和，初始設為無限小(因為矩陣內有負數)
		for (int left = 0, right = 0; left < graph.size(); right = ++left) //從左邊的第0行開始，每次向右掃過一遍
		{
			rowSum.assign(N, 0); //每一輪都要初始化行加總的大小
			//由於左右互通，所以若掃到最右行但還未滿N次，則從最左繼續計算
			for (int times = N; times--; (++right) %= N) //ex: 若N == 5，則跑第(0 → 4)行、(1 → 4, 0)、(2 → 4, 0 → 1)、(3 → 4, 0 → 2)、(4, 0 → 3)，以此類推
			{
				for (int y = 0; y < graph.size(); y++) //將當前行內的值加總
				{
					rowSum[y] += graph[y][right];
				}

				globalMax = max(globalMax, max1D()); //每次取當前的最大的子矩陣和
			}
		}

		cout << globalMax << "\n"; //印出最大的子矩陣和
	}

	system("pause");
}