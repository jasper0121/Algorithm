#include<iostream>
#include<vector>
#define INF 100000000
using namespace std;

int main()
{
	int testCase, dis; //測資、起點和終點的距離
	vector<vector<int>>wind, minCost; //風向表(可看成2點間的邊)、點座標(存距原點的最小花費)
	for (cin >> testCase; testCase--;)
	{
		cin >> dis; //輸入和終點的距離
		wind.assign(10, vector<int>(dis /= 100)); //dis / 100 == 實際邊個數
		minCost.assign(10, vector<int>(dis + 1, INF)); //點個數 == 邊個數 + 1，初始值設為無限
		for (int y = 9; y >= 0; y--) //如同座標，設左下為(0,0)
		{
			for (int x = 0; x < wind[y].size(); cin >> wind[y][x++]); //輸入風向(權重)
		}

		minCost[0][0] = 0; //原點的最小花費為0
		for (int x = 1; x < minCost[0].size(); x++) //x從1開始，因為會用到x - 1
		{
			for (int y = 0; y <= 9; y++) //對於當前的點(飛行方式：上升花費60，平飛花費30，下降花費20)
			{
				if (y) //若當前點的y座標非0，代表該點可從左下和左邊的點走到，選擇2條路線中花費較小者(花費 == 累積花費 + 飛行方式 - 是否順風)
				{
					minCost[y][x] = min(minCost[y - 1][x - 1] + 60 - wind[y - 1][x - 1], minCost[y][x - 1] + 30 - wind[y][x - 1]);
				}

				if (y != 9) //若當前的點不是最上面的點，代表該點可從左上的點走到，判斷從左上的路線是否較小
				{
					minCost[y][x] = min(minCost[y][x], minCost[y + 1][x - 1] + 20 - wind[y + 1][x - 1]);
				}
			}
		}

		cout << minCost[0].back() << "\n\n"; //輸出到終點時的最小花費
	}

	system("pause");
}