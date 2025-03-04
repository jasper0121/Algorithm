#include<iostream>
#include<vector>
using namespace std;

int main()
{
	vector<vector<int>>dp(1121, vector<int>(15)); //dp[i][j] == 當前的數字i用j個質數組合而成的方法數
	vector<int>prime; //存1120內的所有質數
	vector<bool>visit(1121);
	prime.push_back(2); //2是質數
	for (int i = 3; i <= 1120; i += 2) //從3開始，因除了0和2以外的偶數都不是質數，故每次加2
	{
		if (visit[i] == false) //如果當前i代表的數字還未被走訪
		{
			prime.push_back(i); //代表是質數
			for (int k = i; (k += i) <= 1120; visit[k] = true); //將之後i的倍數全設為true代表走訪，因為他們必定不是質數
		}
	}

	dp[0][0] = 1; //0由0個質數組合而成的方法數為1
	for (auto& p : prime) //對所有的質數
	{
		for (int i = 1120; i >= p; i--) //i可當成是背包容量，若由前往後算，則可能會重複取到同樣的質數
		{
			for (int j = 14; j; j--) //題目上限為用14種質數組合
			{
				dp[i][j] += dp[i - p][j - 1]; //相當於i值每次減去一個質數，一旦dp[i - p][j - 1] == dp[0][0]，代表i由j個質數組合而成的方法數 + 1
			}
		}
	}

	for (int n, k; cin >> n >> k, n; cout << dp[n][k] << "\n"); //輸入目標數字n和k，求n以k個質數組合而成的方法數
	system("pause");
}