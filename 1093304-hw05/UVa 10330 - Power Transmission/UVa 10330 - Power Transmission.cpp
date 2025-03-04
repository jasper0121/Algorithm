#include<iostream>
#include<queue>
#include<climits>
using namespace std;

vector<int>layer; //所有點和0的最短距離，同時代表層數，若該點的層數非0則代表可以從起點走到該點(起點的0除外)
vector<vector<int>>graph; //存2點間的容量

int dinicBFS()
{
	queue<int>temp;
	layer.assign(graph.size(), int()); //初始各點的層數皆設為0
	temp.push(0); //初始將起點設為0(因為起點從0開始走)
	layer[0] = 1;
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

int dinicDFS(int cur, int capacity) //當前的點、容量，初始傳入起點、容量無限
{
	if (cur == graph.size() - 1) //若走到終點
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
	int maxflow = 0; //該網路的最大流量
	while (dinicBFS()) //每次先BFS一次，若回傳值非0，代表還能繼續算最大流量
	{
		for (int min; min = dinicDFS(0, INT_MAX); maxflow += min); //每次找出該路徑上的最小容量，並將其值加入最大流量中，若min == 0則代表結束
	}

	cout << maxflow << endl; //輸出最大流量
}

int main()
{
	for (int nodeNum, edgeNum, start = 0, end = 0; cin >> nodeNum;) //點個數、邊個數、起點、終點；每次先輸入有幾個點
	{
		//建圖，每個點也有自己的容量，故要先做拆點。總點個數為：2倍的點個數 + 整個圖的起點與終點
		graph.assign(2 * nodeNum + 2, vector<int>(2 * nodeNum + 2, int()));
		for (int i = 1; i <= nodeNum; i++) //將輸入的容量轉換成2點間的距離(對每個點做拆點)
		{
			cin >> graph[i][i + nodeNum];
		}

		for (cin >> edgeNum; edgeNum--; ) //先輸入幾個邊，輸入每個邊的起點、終點和容量
		{
			cin >> start >> end;
			cin >> graph[start + nodeNum][end];
		}

		cin >> start >> end; //這裡start和end的意義轉成有幾個點和整個圖的起點和終點連接
		for (int x; start--;) //0號點會和接下來要輸入的前start個點連接
		{
			cin >> x; //輸入會被0接入的點
			graph[0][x] = INT_MAX; //0和x號點之間的容量設為無限大
		}

		for (int x; end--;) //剩下的end個點會和終點連接
		{
			cin >> x; //輸入會接到終點的點
			graph[x + nodeNum][graph.size() - 1] = INT_MAX; //該點和終點間的距離設為無限大
		}

		dinic(); //使用dinic演算法找最大流量(綜合BFS和DFS)
	}

	system("pause");
}