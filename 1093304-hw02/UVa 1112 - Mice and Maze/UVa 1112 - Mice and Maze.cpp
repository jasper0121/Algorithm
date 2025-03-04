#include<iostream>
#include<queue>
using namespace std;
using two = pair<size_t, size_t>; //將pair以two代稱，依序存權重(道路長度)及道路的另一端點

vector<vector<two>>graph; //graph存距起點的最小距離

int dijkstra(const int& start, const int& limitTime)
{
	int total = 0; //符合題目所求的點個數
	vector<size_t>dis(graph.size(), -1); //所有點和起點的距離，預設為無限大
	priority_queue<two, vector<two>, greater<two>>temp;
	temp.push({ dis[start] = 0,start }); //起點距離為0(起點必定為所求的點之一)
	for (int cur_dis, cur_y; temp.size();) //若priority_queue的size不為0
	{
		cur_dis = temp.top().first; //取出當前的距離
		cur_y = temp.top().second; //取出當前所在的位置
		temp.pop(); //取出之後將該元素從priority_queue中刪除
		for (int next_dis, next_pos, x = 0; x < graph[cur_y].size(); x++) //走訪所有和當前連接的點
		{
			next_dis = graph[cur_y][x].first; //與目標的距離
			next_pos = graph[cur_y][x].second; //目標點位置
			if (dis[next_pos] > cur_dis + next_dis) //若下個座標的距離 > 當前距離 + 權重(道路長度)
			{
				temp.push({ dis[next_pos] = cur_dis + next_dis,next_pos }); //則將下個座標的距離 = 當前距離 + 權重(道路長度)，並放入priority_queue中
			}
		}
	}

	for (int i = 1; i < dis.size(); total += dis[i++] <= limitTime); //最後數有幾個點和起點的距離 <= 時限
	return total;
}

int main()
{
	int testCase, nodeNum, end, limitTime, edgeNum; //測資、點個數、終點、時間限制、道路總數
	for (cin >> testCase; testCase--;)
	{
		cin >> nodeNum >> end >> limitTime >> edgeNum;
		graph.assign(nodeNum + 1, vector<two>()); //題目從1開始，所以0不用

		for (int x, y, time; edgeNum--;) //由於題目要求所有點距終點的最小路徑是否在時限內，可將終點視為起點反向建圖，使得同一條路不會走到2次以上
		{
			cin >> y >> x >> time;
			graph[x].push_back({ time ,y });
		}

		cout << dijkstra(end, limitTime) << endl;
		if (testCase)
		{
			cout << endl;
		}
	}

	system("pause");
}