#include<iostream>
#include<vector>
using namespace std;

int testCase, Case = 1, width, len, budget, maxArea = 0, minPrice = 0; //測資、寬、長、預算、最大面積、最小花費
vector<vector<int>>landPrice; //存每塊土地的價格
vector<int>rowSum; //當前的行加總

void max1D(const int& left, const int& right)
{
	int curPrice = 0, top = 0; //當前土地價格、當前矩形的上界
	for (int y = 0; y < width; y++) //y可當成下界
	{
		//每次將當前子矩陣的值加總，若該值 > 預算，則減去當前上界的值並將上界下移
		for (curPrice += rowSum[y]; curPrice > budget; curPrice -= rowSum[top++]);
		int curArea = (y - top + 1) * (right - left + 1); //當前面積 == (下界 - 上界 + 1) * (右界 - 左界 + 1)
		if (maxArea < curArea) //若找到更大的土地
		{
			maxArea = curArea; //則將其設為目前的最大土地
			minPrice = curPrice; //將其設為目前的最小花費
		}
		else if (maxArea == curArea) //若土地面積相同
		{
			minPrice = min(minPrice, curPrice); //則取同面積下花費較小的一方
		}
	}
}

int main()
{
	for (cin >> testCase; testCase--; maxArea = 0, minPrice = 0)
	{
		cin >> width >> len >> budget; //輸入寬、長、預算
		landPrice.assign(width, vector<int>(len)); //建圖
		for (int y = 0; y < width; y++) //輸入矩陣中每一格的值
		{
			for (int x = 0; x < len; cin >> landPrice[y][x++]);
		}

		for (int left = 0; left < len; left++) //從左邊的第0行開始
		{
			rowSum.assign(width, 0); //每一輪都要初始化行加總的大小
			for (int right = left; right < len; right++) //每次向右掃過一遍
			{
				for (int y = 0; y < width; y++) //將當前行內的值加總
				{
					rowSum[y] += landPrice[y][right];
				}

				max1D(left, right); //每次找當前的最大土地面積與其中的最小花費
			}
		}

		cout << "Case #" << Case++ << ": " << maxArea << " " << minPrice << "\n"; //印出所有最大土地中花費最小者
	}

	system("pause");
}