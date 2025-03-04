#include <iostream>
#include <sstream>
#include<iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include<cmath>
using namespace std;

struct node //一個點有：x和y座標、和最左下點的距離、sort用的operator(將所有點以y排序)
{
	double x, y, dis;
	bool operator<(const node& right)
	{
		return y == right.y ? x < right.x : y < right.y; //盡可能地先取y較小者，若y相同再取x較小的
	}
};

vector<node>point, stack; //存所有點座標、存凸包點

double distance(const node& left, const node& right) //算2點間的距離
{
	return sqrt(pow(right.x - left.x, 2) + pow(right.y - left.y, 2));
}

double cross_product(const node& p0, const node& p1, const node& p2) //外積公式，(p1 - p0) × (p2 - p0)
{
	return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

bool polar_angle(const node& left, const node& right) //極角排序
{
	double cp = cross_product(point[0], left, right); //以point[0]為原點做一次外積
	return cp == 0 ? left.dis < right.dis : cp > 0; //若外積 == 0，則比較右邊的距離是否比較大；反之若外積為正，代表逆時針旋轉，則回傳true
}

void GrahamScan()
{
	sort(point.begin(), point.end()); //先將所有點以y由小到大排序
	for (int i = 1; i < point.size(); i++) //從排序後的第1個點開始，每個點都算出與原點(point[0])的距離
	{
		point[i].dis = distance(point[0], point[i]);
	}

	sort(point.begin() + 1, point.end(), polar_angle); //從第1個點開始做一次極角排序
	for (int i = 0; i < point.size(); i++) //對於所有的點
	{
		//若stack內存的點 >= 2(因為加上當前的點才能去判斷旋轉趨勢是順或逆時針)，且外積的結果 <=0(非逆時針)
		while (stack.size() >= 2 && cross_product(stack[stack.size() - 2], stack[stack.size() - 1], point[i]) <= 0)
		{
			stack.pop_back(); //則當前stack內的top刪除
		}

		stack.push_back(point[i]); //每次將當前的點加入stack
	}

	stack.push_back(point[0]); //最後會繞回原點
}

int main()
{
	int testCase, nodeNum; //測資、點個數
	double initialLen; //初始的橡皮筋長度
	cin >> testCase;
	for (; testCase--; stack.clear()) //每次清空stack內的資料
	{
		cin >> initialLen >> nodeNum;
		point.assign(nodeNum, node());
		for (int i = 0; i < point.size(); i++) //輸入點座標
		{
			cin >> point[i].x >> point[i].y;
		}

		GrahamScan();
		double perimeter = 0; //找出凸包後，所有點圍起來的多邊形周長
		for (int i = 1; i < stack.size(); i++) //前後2點間的距離加總的結果就是周長
		{
			perimeter += distance(stack[i - 1], stack[i]);
		}

		cout << setprecision(5) << fixed << max(initialLen, perimeter) << endl; //控制輸出在小數點後5位，若周長比橡皮筋初始長還小，則輸出橡皮筋長度
	}

	system("pause");
}