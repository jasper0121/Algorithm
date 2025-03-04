#include<iostream>
#include<vector>
#define two pair<int,int>
#define INF 100000000
using namespace std;

int main()
{
	vector<vector<int>>dp; //dp[i][j] == 璶舱Θ肚参基iのInfoTechnologicalj┮惠程ぶe_coin计
	vector<two>e_coin; //e_coin砆だ肚参基籔InfoTechnological基
	int testCase;
	cin >> testCase;
	for (int e_coinNum, e_modulus; testCase--;) //e_coin贺摸计秖e-modulus ^ 2 == 肚参 ^ 2 + InfoTechnological ^ 2
	{
		dp.assign(301, vector<int>(301, INF)); //e-modulus300伐猵肚参 == 300InfoTechnological == 0┪2は
		dp[0][0] = 0; //肚参 == 0InfoTechnological == 0程ぶe_coin计 == 0
		cin >> e_coinNum >> e_modulus; //块e_coine-modulus
		e_coin.assign(e_coinNum, two()); //沮e_coin贺摸计ミ皚
		for (int i = 0; i < e_coinNum; cin >> e_coin[i].first >> e_coin[i].second, i++); //块–贺e_coin肚参籔InfoTechnological
		for (auto& coin : e_coin) //癸┮Τe_coin
		{
			for (int i = coin.first; i <= 300; i++)
			{
				for (int j = coin.second; j <= 300; j++)
				{
					//猅羭程e_coin薄猵ㄏ "笷肚参iInfoTechnologicalj" 计秖讽玡程
					dp[i][j] = min(dp[i][j], dp[i - coin.first][j - coin.second] + 1);
				}
			}
		}

		int minCoinNum = INF; //┮―ノ程ぶe-coinㄓ笷莱e-modulus珿程┮惠e-coin﹍砞礚
		for (int i = 0; i <= 300; i++) //癸┮Τ肚参基籔InfoTechnological
		{
			for (int j = 0; j <= 300; j++)
			{
				if (i * i + j * j == e_modulus * e_modulus) //璝肚参基籔InfoTechnological沮そΑ才e_modulus
				{
					minCoinNum = min(minCoinNum, dp[i][j]); //玥┮Τ才そΑ舱讽いт┮惠程ぶe-coin计秖
				}
			}
		}

		if (minCoinNum == INF) //璝minCoinNumご礚┮―e_modulus礚猭搓眔
		{
			cout << "not possible\n";
			continue;
		}

		cout << minCoinNum << "\n"; //はぇ玥程ぶ┮惠e_coin计秖
	}

	system("pause");
}