#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int testCase, num, Case = 1; //測資、建築物數、當前測資
	vector<int>hight, width, LIS, LDS; //建築物的高與寬、最長嚴格遞增與遞減，每格存到此建築物的過程中的最大寬度總和
	for (cin >> testCase; testCase--;)
	{
		cin >> num; //輸入建築物數
		int LIS_max = 0, LDS_max = 0; //題目求高度嚴格遞增和遞減(不用求最長)，且所有遞增的組合中寬度總和最寬的
		hight.assign(num, int()); //建築物高度
		width.assign(num, int()); //建築物寬度
		for (int i = 0; i < hight.size(); cin >> hight[i++]); //輸入所有高度
		for (int i = 0; i < width.size(); cin >> width[i++]); //輸入所有寬度
		LIS = LDS = width; //初始LIS和LDS中的值和width一樣(這裡存的是遞增/減到每個建築物時的累積寬度)
		for (int cur = 0; cur < hight.size(); cur++) //current將所有的高度走過一遍
		{
			for (int tar = 0; tar <= cur; tar++) //每次current和current前面所有的數字比較
			{
				if (hight[cur] > hight[tar]) //若current比目標數字大，代表遞增
				{
					LIS[cur] = max(LIS[cur], LIS[tar] + width[cur]); //若target的累積寬度 + current的寬度 > current的累積寬度，則更新LIS[cur]的值
				}
				else if (hight[cur] < hight[tar]) //若current比目標數字小，代表遞減
				{
					LDS[cur] = max(LDS[cur], LDS[tar] + width[cur]); //若target的累積寬度 + current的寬度 > current的累積寬度，則更新LDS[cur]的值
				}

				LIS_max = max(LIS_max, LIS[cur]); //最後比較，當前的LIS[cur]是否比目前的最大值還大
				LDS_max = max(LDS_max, LDS[cur]); //最後比較，當前的LDS[cur]是否比目前的最大值還大
			}
		}

		cout << "Case " << Case++ << ". ";
		if (LIS_max >= LDS_max) //題目要求哪個最大值較大就先輸出
		{
			cout << "Increasing (" << LIS_max << "). Decreasing (" << LDS_max << ").\n";
			continue;
		}

		cout << "Decreasing (" << LDS_max << "). Increasing (" << LIS_max << ").\n";
	}

	system("pause");
}