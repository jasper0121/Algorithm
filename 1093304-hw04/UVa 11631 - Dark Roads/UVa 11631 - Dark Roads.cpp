#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct point //用於併查集，每個點的初始parent為自己，rank最高者將成為root
{
	int parent, rank;

	point(const int& p, const int& r) //constructor，在vector的push_back中會使用到，用來設定data member
	{
		parent = p;
		rank = r;
	}
};

struct edge //每一條邊有起點、終點和邊長
{
	int start, end, dis;

	bool operator<(const edge& right) //使用sort時，依邊長由小到大排序
	{
		return dis < right.dis;
	}
};

vector<point>node; //存所有城市，每個城市視為一個點
vector<edge>graph; //存所有可能的邊

int find_root(int start) //若當前該點的parent != 自己，則從parent繼續往前找，若找到則回傳該點
{
	return node[start].parent != start ? find_root(node[start].parent) : start;
}

bool union_node(const int& s, const int& e)
{
	int startRoot = find_root(s), endRoot = find_root(e); //2點各自找root
	if (startRoot != endRoot) //若2點的root不相同，則代表若連接此2點不會形成環，可將2個root連接起來形成一個集合
	{
		if (node[startRoot].rank == node[endRoot].rank) //若2個root的rank相同
		{
			node[endRoot].parent = startRoot; //則設定endRoot的parent為startRoot
			node[startRoot].rank++; //因為endRoot的parent是startRoot，所以startRoot的階級 + 1
		}
		else //若startRoot的階級較大，則設定endRoot的parent為startRoot；反之則將startRoot的parent設為endRoot
		{
			(node[startRoot].rank > node[endRoot].rank) ? (node[endRoot].parent = startRoot) : (node[startRoot].parent = endRoot);
		}

		return true; //2點已連成實線，回傳true
	}

	return false; //2點不能連成實線，回傳false
}

void kruskcal(const int& totalDis)
{
	int minDis = 0; //所有城市都連起來所需的最小邊長
	sort(graph.begin(), graph.end()); //將所有邊長由小到大排序
	for (int i = 0; i < graph.size(); i++)
	{
		if (union_node(graph[i].start, graph[i].end)) //檢查當前的2點是否能真的連成實線
		{
			minDis += graph[i].dis; //將已連成實線的線段長加總
		}
	}

	cout << totalDis - minDis << endl; //題目求最多能省多少邊長，即總線段 - 最小所需邊長
}

int main()
{
	for (int cityNum, roadNum; cin >> cityNum >> roadNum, cityNum; node.clear()) //點個數、邊總數；每次輸入直到其中一個輸入0；每次將node重置
	{
		int totalDis = 0; //總邊長，即所有路燈都開(也可看成所有權重的總和)
		for (int i = 0; i < cityNum; node.push_back(point(i++, 0))); //設定每個點的parent和rank(每個點的parent都預設為自己，rank初始為0)
		graph.assign(roadNum, edge()); //建圖
		for (int i = 0; i < roadNum; i++) //輸入題目給的所有可能的邊(此時的連接可看成虛線，還未真正連成邊)
		{
			cin >> graph[i].start >> graph[i].end >> graph[i].dis; //起點、終點、邊長
			totalDis += graph[i].dis; //邊長加總
		}

		kruskcal(totalDis);
	}

	system("pause");
}