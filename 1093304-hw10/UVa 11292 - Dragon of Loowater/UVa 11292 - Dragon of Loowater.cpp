#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	vector<int>dragon, knight; //龍頭、騎士身高
	for (int dragonNum, knightNum; cin >> dragonNum >> knightNum, dragonNum; )//龍數量、騎士數
	{
		int total = 0; //總花費
		dragon.assign(dragonNum, int());
		knight.assign(knightNum, int());
		for (int i = 0; i < dragonNum; cin >> dragon[i++]); //輸入龍頭直徑
		for (int i = 0; i < knightNum; cin >> knight[i++]); //輸入騎士身高
		sort(dragon.begin(), dragon.end()); //龍頭直徑由小到大排序
		sort(knight.begin(), knight.end()); //騎士身高由小到大排序

		int d = 0, k = 0; //dragon的index、knight的index
		for (; k < knightNum && d < dragonNum; k++) //對於每個騎士
		{
			if (knight[k] >= dragon[d]) //若騎士身高 >= 龍頭直徑，才能順利砍下
			{
				total += knight[k]; //此時需要花費與騎士身高等值的金幣
				d++; //砍下的龍頭數
			}
		}

		if (d == dragonNum) //若所有龍頭都被砍下
		{
			cout << total << endl; //輸出總花費
			continue;
		}

		cout << "Loowater is doomed!\n"; //無法砍下所有龍頭
	}

	system("pause");
}