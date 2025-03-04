#include<iostream>
#include<string>
#include<climits>
#include<queue>
using namespace std;

vector<int>layer; //所有點和0的最短距離，同時代表層數，若該點的層數非0則代表可以從起點走到該點(起點的0除外)
vector<vector<int>>graph; //存2點間的容量

int dinicBFS()
{
	queue<int>temp;
	layer.assign(38, int()); //初始各點的層數皆設為0
	temp.push(0); //初始將起點設為0(因為起點從0開始走)
	for (int y; temp.size();) //y == 當前的點、若queue的size()不為0
	{
		y = temp.front(); //每次將queue最前面的元素拿出來
		temp.pop(); //之後將queue中的該元素刪掉
		for (int x = 1; x < graph[y].size(); x++) //每次從x = 1開始(在做BFS時不會走回原點)
		{
			if (graph[y][x] && layer[x] == 0) //若y→x間還有容量，且還未設定x位於第幾層
			{
				layer[x] = layer[y] + 1; //則將x設為y的層數 + 1
				temp.push(x); //並將該點加入queue中
			}
		}
	}

	return layer.back(); //最後回傳終點的層數，若終點的層數為0，則代表從起點已經無法走到終點
}

int dinicDFS(int cur, int capacity)
{
	if (cur == 37) //若走到終點
	{
		return capacity; //則回傳當前的容量(此時會是最小容量)
	}

	for (int minCapacity, x = 0; x < graph[cur].size(); x++) //從起點到當前點之間所經過的最小容量；目標從1開始
	{
		//若當前的容量非0，路線沿著階層的順序走，在該條路線上找出最小的容量，且該容量非0時
		if (graph[cur][x] && layer[x] == layer[cur] + 1 && (minCapacity = dinicDFS(x, min(graph[cur][x], capacity))))
		{
			graph[cur][x] -= minCapacity; //當前路線上的每個容量 - 路線上所找到的最小容量
			graph[x][cur] += minCapacity; //當前路線上的每個剩餘容量 + 路線上所找到的最小容量
			return minCapacity; //回傳該條路徑上所找到的最小容量
		}
	}

	return 0; //若當前已沒有任何路徑可以走到終點，則回傳0
}

void dinic()
{
	while (dinicBFS()) //每次先BFS一次，若回傳值非0，代表還能繼續算最大流量
	{
		while (dinicDFS(0, INT_MAX)); //每次找出該路徑上的最小容量，若 == 0則代表結束
	}

	for (int i = 1; i <= 26; i++)
	{
		if (graph[0][i]) //若起點→任何字母上有任何一條的capacity > 0
		{
			cout << "!\n"; //代表無法全數分配完
			return;
		}
	}

	vector<char>output(10, '_');
	for (int i = 27; i < 37; i++) //數字點
	{
		for (int j = 1; j <= 26; j++) //字母點
		{
			if (graph[i][j]) //若數字點 → 英文點 > 0(即反向的capacity > 0)代表此條邊已走過
			{
				output[i - 27] = j + 64; //存該點相對應的字母
			}
		}
	}

	for (int i = 0; i < 10; cout << output[i++]); //最後全部輸出即為答案
	cout << endl;
}

int main()
{
	for (string input; getline(cin, input), input != "";)
	{
		graph.assign(38, vector<int>(38, 0)); //0 == 起點、1 ~ 27 == A ~ Z、28 ~ 37 == 0 ~ 9、38 == 終點

		do //建圖
		{
			graph[0][input[0] - 64] = input[1] - '0'; //紀錄capacity
			for (int i = 3; i < input.size() - 1; i++) //對於之後會連接到的點(英文字母→數字)之間的capacity都設為1
			{
				graph[input[0] - 64][input[i] - 21] = 1;
			}
		} while (getline(cin, input), input != "");

		for (int i = 27; i < 38; graph[i++][37] = 1); //所有數字點都連接到終點，其容量都設為1
		dinic();
	}

	system("pause");
}