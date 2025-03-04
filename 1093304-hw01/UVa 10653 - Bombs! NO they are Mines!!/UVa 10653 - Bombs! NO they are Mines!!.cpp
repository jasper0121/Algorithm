#include<iostream>
#include<queue>
using namespace std;

const int dir[5]{ 0,1,0,-1,0 }; //方向(上右下左)
int row, col, rowBomb, start_row, start_col, end_row, end_col; //列、欄、幾列有炸彈、起點和終點座標
vector<vector<int>>graph; //每格代表從起點到該座標的距離

void BFS()
{
	queue<pair<int, int>>temp;
	temp.push({ start_row,start_col }); //初始先將起點座標加入queue中
	for (int cur_row, cur_col; temp.size();) //當前座標；queue內全空才跳出
	{
		cur_row = temp.front().first; //每次將queue中最前面的座標取出來作為當前座標
		cur_col = temp.front().second;
		temp.pop(); //取出之後將該元素從queue中刪除
		for (int next_row, next_col, i = 0; i < 4; i++) //接下來要走到的座標；上右下左各做一次
		{
			next_row = cur_row + dir[i + 1]; //每次先將下個座標訂好
			next_col = cur_col + dir[i];
			if (next_row < 0 || next_row == row || next_col < 0 || next_col == col) //若下個座標超出範圍外
			{
				continue; //則以下不處理
			}

			if (graph[next_row][next_col] == 0 && !(next_row == start_row && next_col == start_col)) //若下個座標的值 == 0(未走過)，且該座標非起始點
			{
				graph[next_row][next_col] = graph[cur_row][cur_col] + 1; //則該座標的距離 == 當前所在座標 + 1
				temp.push({ next_row,next_col }); //再將下個座標加入queue中
			}
		}
	}

	cout << graph[end_row][end_col] << endl; //輸出從起點到該座標的距離
}

int main()
{
	while (cin >> row >> col, row)
	{
		graph.assign(row, vector<int>(col)); //根據row和column建圖
		cin >> rowBomb;
		for (int x, y, bombNum; rowBomb--;)
		{
			for (cin >> y >> bombNum; bombNum--;)//每次先輸入第幾列及該列的炸彈數
			{
				cin >> x;
				graph[y][x] = -1; //將炸彈存在的位置設為-1
			}
		}

		cin >> start_row >> start_col >> end_row >> end_col; //輸入起始和終點座標
		BFS(); //用BFS找答案
	}

	system("pause");
}