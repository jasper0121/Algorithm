#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int testCase, cart; //測資、車廂
	vector<int>train, LIS; //列車、最長嚴格遞增子序列
	for (cin >> testCase; testCase--; LIS.clear())
	{
		if (cin >> cart, cart) //輸入車廂數
		{
			train.assign(cart * 2, int()); //因題目說每次車廂可放在車頭或車尾，故將當前的列車順序顛倒一份並加到列車前面，故train的大小 * 2
			for (int i = 0; i < cart; i++)
			{
				cin >> train[cart + i]; //輸入車廂
				train[cart - i - 1] = train[i + cart]; //將當前的列車順序顛倒一份並加到列車前面(ex：若原本是123，則會改成321123)
			}

			LIS.push_back(train[0]); //先將車頭加入LIS
			for (int i = 1; i < train.size(); i++) //LIS演算法，從數列中index == 1的位置開始
			{
				if (train[i] > LIS.back()) //若數列中當前的數字 > LIS中最後面的數字
				{
					LIS.push_back(train[i]); //則直接將當前的數字加入LIS中
					continue;
				}

				*lower_bound(LIS.begin(), LIS.end(), train[i]) = train[i]; //反之，則先找出LIS中，所有大於train[i]之中的最小者，並將其用train[i]取代
			}
		}

		cout << LIS.size() << "\n"; //題目求最長嚴格遞增子序列的長度
	}

	system("pause");
}