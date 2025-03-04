#include<iostream>
#include<vector>
#define INF 100000000
using namespace std;

int main()
{
	vector<int>cut; //切割點
	vector<vector<int>>dp; //dp[i][j]，木頭從切割點i ~ j中的最小花費
	for (int cutNum, length; cin >> length, length;) //輸入木頭總長度
	{
		cin >> cutNum; //切割點的數量
		cut.assign(cutNum + 2, int()); //頭尾也當成切割點
		for (int i = 1; i <= cutNum; cin >> cut[i++]); //輸入切割點(最前端的切割點必定為0)
		cut.back() = length; //最尾端的切割點必為整根木頭的長度
		dp.assign(cut.size(), vector<int>(cut.size()));
		//若part == 1，代表只有一段中間沒有切割點的木頭，這時的花費是0，故從2開始起算。cut.size() - 1 == 木頭段數
		for (int part = 2; part <= cut.size() - 1; part++)
		{
			for (int begin = 0, end = part; end < cut.size(); begin++, end++) //每次起點和終點都固定向後走一段
			{
				dp[begin][end] = INF; //初始將從起點到終點所花費的時間設為無限
				for (int cutPos = begin + 1; cutPos < end; cutPos++) //初始切割點的位置 == 起點的下一個切割點
				{
					//若起點 ~ 當前切割點 + 當前切割點 ~ 終點 + 起點到終點的木頭長度 < 當前木頭的總花費，則更新該段木頭的最小花費
					dp[begin][end] = min(dp[begin][end], dp[begin][cutPos] + dp[cutPos][end] + (cut[end] - cut[begin]));
				}
			}
		}

		cout << "The minimum cutting is " << dp[0].back() << ".\n"; //題目求整段木頭的最小花費
	}

	system("pause");
}