#include<iostream>
#include <iomanip>
#include<vector>
#include<unordered_set>
#define INF 100000000
using namespace std;

int main()
{
	vector<vector<int>>graph;
	unordered_set<int>num; //存那些數會與其他數連接，如此就不需要遍歷整個graph，只需要遍歷真正有與其他點連接的點
	for (int start, end, Case = 1; cin >> start >> end, start; num.clear()) //起點、終點，每次num要重置
	{
		graph.assign(101, vector<int>(101, INF)); //數字範圍1 ~ 100，0不用，初始權重設為無限大
		do
		{
			num.insert(start);
			num.insert(end);
			graph[start][end] = 1; //2點間的權重(可看成道路長)均設為1
		} while (cin >> start >> end, start);

		for (auto& mid : num) //遍歷num內的所有值
		{
			for (auto& u : num)
			{
				for (auto& v : num) //佛洛依德演算法，所有u到v的可能路徑中，取路線最短者
				{
					graph[u][v] = min(graph[u][v], graph[u][mid] + graph[mid][v]);
				}
			}
		}

		double sum = 0, way = num.size() * (num.size() - 1); //所有點都會和其他點找最短路徑，所以方法數 == 點個數 * (點個數 - 1)
		for (auto& u : num)
		{
			for (auto& v : num)
			{
				if (u != v) //若起點 != 終點
				{
					sum += graph[u][v]; //則將最短路徑加總
				}
			}
		}

		//所求 == 最短路徑的總和 / 方法數
		cout << "Case " << Case++ << ": average length between pages = " << fixed << setprecision(3) << sum / way << " clicks\n";
	}

	system("pause");
}