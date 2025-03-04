#include<iostream>
using namespace std;

long long bar[51][51][51]; //0不用，barNum(總條數)、zone(黑白合計有幾個區域)、width(同顏色的極限寬度)

int main()
{
	for (int barNum = 1; barNum <= 50; barNum++) //題目規定第1條必為黑
	{
		for (int width = barNum; width <= 50; bar[barNum][1][width++] = 1); //若區域為1，則該區域必只有黑色，故只有1種組合
	}

	for (int barNum = 1; barNum <= 50; barNum++)
	{
		for (int zone = 1; zone <= 50; zone++)
		{
			for (int width = 1; width <= 50; width++)
			{
				if (width > barNum) //若極限寬度 > 總條數，則該方法數等同於極限寬度 == 總條數
				{
					bar[barNum][zone][width] = bar[barNum][zone][barNum];
					continue;
				}

				for (int add = 1; add <= width; add++) //減掉的add數等同於在最尾端加上同種顏色的條數，因此zone要 - 1。add的上限等同width
				{
					bar[barNum][zone][width] += bar[barNum - add][zone - 1][width];
				}
			}
		}
	}

	for (int barNum, zone, width; cin >> barNum >> zone >> width; cout << bar[barNum][zone][width] << "\n"); //根據輸入條件印出對應的值
	system("pause");
}