#include<iostream>
#include<queue>
using namespace std;
using two = pair<size_t, size_t>; //將pair以two代稱，依序存權重(路徑長)及其目標端點

int testCase, nodeNum, line, start, target; //測資、點個數、線的總數、起點、終點
vector<vector<two>>graph; //graph存距起點的最小距離

void dijkstra(int& t)
{
	vector<size_t>dis(nodeNum, -1); //所有點和起點的距離，預設為無限大
	priority_queue<two, vector<two>, greater<two>>temp;
	temp.push({ dis[start] = 0,start }); //初始起點距離為0，放入priority_queue中
	for (int cur_dis, cur_y; temp.size();) //若priority_queue的size不為0
	{
		cur_dis = temp.top().first; //取出當前的距離
		cur_y = temp.top().second; //取出當前所在的位置
		temp.pop(); //取出之後將該元素從priority_queue中刪除
		for (int next_dis, next_pos, x = 0; x < graph[cur_y].size(); x++)
		{
			next_dis = graph[cur_y][x].first; //與目標的距離
			next_pos = graph[cur_y][x].second; //目標點位置
			if (dis[next_pos] > cur_dis + next_dis) //若下個座標的距離 > 當前距離 + 權重(道路長度)
			{
				temp.push({ dis[next_pos] = cur_dis + next_dis,next_pos }); //則將下個座標的距離 = 當前距離 + 權重(道路長度)，並放入priority_queue中
			}
		}
	}

	cout << "Case #" << t++ << ": ";
	if (dis[target] == -1)
	{
		cout << "unreachable" << endl;
	}
	else
	{
		cout<< dis[target] << endl;
	}
}


int main()
{
	cin >> testCase;
	for (int t = 1; t <= testCase;)
	{
		cin >> nodeNum >> line >> start >> target;
		graph.assign(nodeNum, vector<two>());
		for (int x, y, latency; line--;) //建圖，延遲可看成是路徑長
		{
			cin >> y >> x >> latency;
			graph[y].push_back({ latency ,x });
			graph[x].push_back({ latency ,y });
		}

		dijkstra(t);
	}

	system("pause");
}