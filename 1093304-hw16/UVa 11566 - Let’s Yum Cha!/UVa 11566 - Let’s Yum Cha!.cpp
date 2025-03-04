#include<iostream>
#include<iomanip>
#include<vector>
#define two pair<int,int>
using namespace std;

int main()
{
	vector<two>showcase; //展示櫃，first == 該點心的價格、second == 所有人的滿意度之和
	vector<vector<int>>dp; //dp[i][j] == 選了i個點心，總價為j元下的最大喜好度
	//總人數(自己 + 朋友)、每人付錢的上限、茶費、點心種類數、總預算
	for (int people, maxCost, tea, dessert, budget; cin >> people >> maxCost >> tea >> dessert, people;)
	{
		//每人最多只能花費maxCost的量，但由於還要付服務費以及每人茶費，故實際花在點心上的總預算 == 人數 * 上限花費 / 服務費 - 人數 * 茶費
		budget = (++people * maxCost) / float(1.1) - people * tea; //此時的people只是朋友數，故要先加上自己
		showcase.assign(dessert * 2, two()); //每種點心最多只能選2次，故當成點心展示櫃中每種點心只有2個
		for (int i = 0; i < showcase.size(); i += 2) //建立展示櫃
		{
			cin >> showcase[i].first; //輸入該點心的價格
			showcase[i + 1].first = showcase[i].first; //每種點心一次放2個
			for (int favor, j = 0; j < people; j++) //輸入每人對該種點心的喜好度，並且將其加總
			{
				cin >> favor;
				showcase[i + 1].second = showcase[i].second += favor;
			}
		}

		dp.assign(people * 2 + 1, vector<int>(budget + 1)); //dp[i][j] == 選了i個點心，總價為j元
		for (int i = 0; i < showcase.size(); i++)
		{
			int price = showcase[i].first, favour = showcase[i].second; //當前點心的價格與喜好度
			for (int p = people * 2; p; p--) //每人最多點2個點心，故people * 2 == 最大點心數；背包問題一律由後往前算
			{
				for (int b = budget; b >= price; b--) //若當前的預算 >= 該點心的價格，代表還付得起
				{
					dp[p][b] = max(dp[p][b], dp[p - 1][b - price] + favour); //盡可能地找出選了p個點心且預算為b的最大喜好度
				}
			}
		}

		int maxFavour = 0; //最大喜好度
		for (int i = 0; i < dp.size(); maxFavour = max(maxFavour, dp[i++][budget])); //找出在預算內的最大喜好度
		cout << setprecision(2) << fixed << double(maxFavour) / people << "\n"; //根據公式計算並輸出平均喜好度
	}

	system("pause");
}