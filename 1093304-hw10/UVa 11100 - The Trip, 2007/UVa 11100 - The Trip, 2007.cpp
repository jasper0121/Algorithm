#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	vector<int>bag, bagNum; //包包種類、每種類的數量(從1開始)
	for (int total; cin >> total, total; cout << endl) //總包包數
	{
		int bagMax = 0; //存哪種類的數量最多，也代表著最小件數
		bag.assign(total, int());
		bagNum.assign(total + 1, int()); //0不用
		for (int i = 0; i < total; i++)
		{
			cin >> bag[i]; //輸入種類
			bagNum[bag[i]]++; //該種類的數量 + 1
			bagMax = max(bagMax, bagNum[bag[i]]); //找哪種類的數量最多
		}

		sort(bag.begin(), bag.end()); //種類數由小到大排序
		cout << bagMax << endl;
		for (int cur = 0; cur < bagMax; cout << endl, cur++) //在bagMax為範圍內的每個值都作為起點
		{
			for (int next = cur; next < bag.size(); next += bagMax) //每次以bagMax為距離跳著輸出
			{
				cout << (cur == next ? "" : " ") << bag[next];
			}
		}
	}

	system("pause");
}