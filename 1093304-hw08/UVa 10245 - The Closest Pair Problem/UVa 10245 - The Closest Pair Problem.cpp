#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<vector>
#define two pair<double,double>
using namespace std;

vector<two>point; //存所有點座標

double divide_and_conquer(int left, int right)
{
	if (left == right) //若取左右半邊時走到了最左或最右
	{
		return 10000; //則回傳題目所訂的最大值
	}

	int midnode = (left + right) / 2; //當前中間的點(中點會在中線的左邊)
	double midline = (point[midnode].first + point[midnode + 1].first) / 2; //定義中線為：當前中間點與下個右點間的中垂線(其值為該中垂線的x座標)
	//先盡可能從中線的左右半邊最小x開始後，左右半邊各自找出該半邊內2點間的最小距離，之後從將當前2半邊取得的最小距離中取最小值
	double range = min(divide_and_conquer(midnode + 1, right), divide_and_conquer(left, midnode)); //並且將該最小值作為當前中線向左右延伸的範圍
	double minDis = range; //最小距離存在於範圍內，故先將最小距離 == 範圍

	for (int L = midnode; L >= left && midline - range < point[L].first; L--) //若左半邊的當前點x座標在範圍內
	{
		for (int R = midnode + 1; R < point.size() && point[R].first < midline + range; R++) //若右半邊的當前x座標在範圍內
		{
			//算出2點間距離後，若比當前最短距離還小，則最小距離改設為該值
			minDis = min(minDis, sqrt(pow(point[R].first - point[L].first, 2) + pow(point[R].second - point[L].second, 2)));
		}
	}

	return minDis; //回傳最短距離
}

int main()
{
	for (int nodeNum; cin >> nodeNum, nodeNum;) //點個數
	{
		point.assign(nodeNum, two()); //根據點個數配置空間
		for (int i = 0; i < nodeNum; i++) //輸入各個點座標(x座標 == first、y座標 == second)
		{
			cin >> point[i].first >> point[i].second;
		}

		sort(point.begin(), point.end()); //對x座標由小到大排序
		double minDis = divide_and_conquer(0, nodeNum - 1); //找最短距離，初始帶入值為最左和最右的值

		if (minDis < 10000) //若最短距離 < 10000
		{
			cout << setprecision(4) << fixed << minDis << "\n"; //則四捨五入後輸出到小數點後4位
		}
		else
		{
			cout << "INFINITY\n";
		}
	}

	system("pause");
}