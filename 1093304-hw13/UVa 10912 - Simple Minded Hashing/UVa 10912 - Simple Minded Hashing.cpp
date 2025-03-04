#include<iostream>
#include<vector>
using namespace std;

int dp[27][27][352]; //dp[i][j][k]表只使用前 i 個字母，組成的字母個數為 j，總和為 k 的字串的所有情況數(1加到26的總和為351)

int main()
{
	for (int i = 1; i <= 26; i++) //只使用前i個字母，且只用一個字母的話，那麼總和為i的情況數只有1種
	{
		dp[i][1][i] = 1;
	}

	for (int i = 1; i <= 26; i++) //只使用前i個字母
	{
		for (int j = 1; j <= i; j++) //在只使用前i個字母的情況下，組成的字母個數最多就是i個
		{
			for (int k = 1; k <= (1 + i) * i / 2; k++) //在只使用前i個字母的情況下，字母總和最多為k = 1 + 2+ ... + i = (1 + i) * i / 2
			{
				dp[i][j][k] += dp[i - 1][j][k]; //初始先將只使用前i - 1個字母，但使用同樣j個字母個數，且加總也相同的情況加上去(即第i個字母不使用)
				if (k >= i) //若總和 >= 第i個字母
				{
					dp[i][j][k] += dp[i - 1][j - 1][k - i]; //則加上「只使用前i - 1個字母，只用j - 1個字母組成，其總和加上i會等於k」的方法數(即使用第i個字母)
				}
			}
		}
	}

	//若輸入不在範圍內則輸出為0
	for (int n = 1, len, sum; cin >> len >> sum, len; cout << "Case " << n++ << ": " << (len <= 26 && sum <= 351 ? dp[26][len][sum] : 0) << "\n");
	system("pause");
}