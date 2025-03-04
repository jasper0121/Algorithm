#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

vector<vector<int>>graph;
int employee, friendNum, id, testCase; //員工總數、每個員工的朋友數、員工編號、測資數

void BFS()
{
	cin >> id; //輸入員工編號
	if (graph[id].empty()) //若該編號的陣列內size為0
	{
		cout << 0 << endl; //代表該員工沒朋友
		return;
	}

	queue<int>temp;
	vector<int>dis(graph.size()), max(graph.size() + 1); //distance存每個點對於起始點的距離、max為第幾天(index)有最多原本不知道的人得知消息(0不使用)
	temp.push(id); //初始先將start加入queue中
	for (int cur; temp.size();) //cur == 當前的點、若queue的size()不為0
	{
		cur = temp.front(); //每次將queue最前面的元素拿出來
		temp.pop(); //之後將queue中的該元素刪掉
		for (int x = 0; x < graph[cur].size(); x++) //對於cur所連接的所有的點
		{
			if (graph[cur][x] != id && dis[graph[cur][x]] == 0) //若接下來要走訪的該點 != 起點，且該點 == 0 (還未走過)
			{
				dis[graph[cur][x]] = dis[cur] + 1; //則接下來該點的距離為當前的距離 + 1
				max[dis[graph[cur][x]]]++; //最大距離 + 1
				temp.push(graph[cur][x]); //並將該點加入queue
			}
		}
	}

	auto it = max_element(max.begin() + 1, max.end()); //找出哪一天(index)的值最大，從第1天開始找
	cout << *it << " " << it - max.begin() << endl; //輸出該值及其index
}

int main()
{
	cin >> employee; //輸入人數
	graph.assign(employee, vector<int>()); //建圖
	for (int y = 0; y < employee; y++) //對於每個員工、輸入朋友數並建關係圖
	{
		cin >> friendNum;
		graph[y].assign(friendNum, int());
		for (int x = 0; x < friendNum; cin >> graph[y][x++]);
	}

	for (cin >> testCase; testCase--; BFS()); //輸入幾筆測資，每次以BFS找答案
	system("pause");
}