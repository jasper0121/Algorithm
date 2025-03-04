#include<iostream>
#include<queue>
using namespace std;
using three = pair<size_t, pair<size_t, size_t>>; //將雙重pair以three代稱，依序存當前該點的最小距離及其點座標

const int dir[5]{ 0,1,0,-1,0 }; //方向(上右下左)
int testCase, row, col; //測資、列、欄
vector<vector<size_t>>weight, graph; //權重(可視為道路長度)、graph存距起點的最小距離

void dijkstra()
{
	priority_queue<three, vector<three>, greater<three>>temp; //min heap，top為最小
	temp.push({ graph[0][0] = weight[0][0],{0,0} }); //先將初始權重放入起點，並加入priority_queue中
	for (int x, y; temp.size();) //若priority_queue的size不為0
	{
		x = temp.top().second.first; //每次先將座標取出
		y = temp.top().second.second;
		temp.pop(); //取出之後將該元素從priority_queue中刪除
		for (int next_x, next_y, i = 0; i < 4; i++) //接下來要走到的座標；上右下左各做一次
		{
			next_x = x + dir[i]; //每次先將下個座標訂好
			next_y = y + dir[i + 1];
			if (next_x < 0 || next_x == col || next_y < 0 || next_y == row) //若下個座標超出範圍外
			{
				continue; //則以下不處理
			}

			if (graph[next_y][next_x] > graph[y][x] + weight[next_y][next_x]) //若下個座標的距離 > 當前距離 + 權重(道路長度)
			{
				//則將下個座標的距離 = 當前距離 + 權重(道路長度)，並放入priority_queue中
				temp.push({ graph[next_y][next_x] = graph[y][x] + weight[next_y][next_x],{ next_x,next_y } });
			}
		}
	}

	cout << graph[row - 1][col - 1] << endl; //輸出最短路徑
}

int main()
{
	for (cin >> testCase; testCase--;)
	{
		cin >> row >> col; //每次輸入列和欄
		graph.assign(row, vector<size_t>(col, -1)); //訂好圖的大小，所有值預設為-1(即最大值)
		weight = graph; //權重初始和圖一樣
		for (int y = 0; y < row; y++) //輸入權重
		{
			for (int x = 0; x < col; cin >> weight[y][x++]);
		}

		dijkstra(); //找最短路徑
	}

	system("pause");
}