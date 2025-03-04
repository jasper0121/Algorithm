#include<iostream>
#include<vector>
#define INF 100000000
using namespace std;

int main()
{
	vector<int>coin, dp; //肂舱Θ赣肂程ぶ计秖(肂ぃ狡)
	int testCase, price, coinNum; //代戈基肂计秖
	for (cin >> testCase; testCase--;)
	{
		int total = 0;
		cin >> price >> coinNum; //块基籔肂计秖
		coin.assign(coinNum, int()); //沮肂计秖ㄓ∕﹚coin皚
		for (int i = 0; i < coin.size(); i++) //块┮Τ肂
		{
			cin >> coin[i];
			total += (total < price ? coin[i] : 0); //筁祘い盢肂羆禬筁﹚基
		}

		dp.assign(total + 1, INF); //肈ヘ璶―禬筁()price程肂舱盢dp砞total + 1禬筁场だ碞ぃ璸衡
		dp[0] = 0; //舱Θ0じよ猭计常ぃ珿よ猭计0
		for (auto& c : coin) //癸┮Τ肂祑刽
		{
			for (int i = total; i >= c; i--) //肂ぃ狡珿パ┕玡
			{
				dp[i] = min(dp[i], dp[i - c] + 1); //猅羭讽玡肂薄猵舱Θ肂i程ぶ祑刽计
			}
		}

		//肈ヘ―肂羆程钡(单)price籔肂计秖
		for (; dp[price] == INF; price++); //珿眖price秨﹍ス舱Θ赣祑刽计ぃ礚┮―
		cout << price << " " << dp[price] << "\n"; //程钡(单)price籔肂计秖
	}

	system("pause");
}