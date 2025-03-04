#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#define two pair<int, int> //將pair<int, int>以two代替
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
	int start, end;
	double dis;

	bool operator<(const edge& right) //使用sort時，依邊長由小到大排序
	{
		return dis < right.dis;
	}

	edge(const int& s, const int& e, const double& d) //constructor，在vector的push_back中會使用到，用來設定data member
	{
		start = s;
		end = e;
		dis = d;
	}
};

int testCase, Case = 1, cityNum, limitDis; //測資、當前case、城市總數、極限距離(超過此距離則為鐵路，否則為公路)
vector<two>city; //存所有城市的座標，並且將index作為城市的編號
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

void kruskcal()
{
	int stateNum = 1; //州的數量，初始為1
	double roadLen = 0, railroadLen = 0; //公路總長、鐵路總長
	sort(graph.begin(), graph.end()); //將所有邊長由小到大排序
	for (int i = 0; i < graph.size(); i++) //對於所有可能的邊
	{
		if (union_node(graph[i].start, graph[i].end)) //檢查當前的2點是否能真的連成實線
		{
			//若當前的邊長 <= 極限距離，則該邊長當作公路；否則當作鐵路(2州以鐵路連接，故州數 + 1)
			(graph[i].dis <= limitDis ? roadLen : (stateNum++, railroadLen)) += graph[i].dis;
		}
	}

	//輸出州數、公路長及鐵路長(4捨五入)
	cout << "Case #" << Case++ << ": " << stateNum << " " << int(roadLen + 0.5) << " " << int(railroadLen + 0.5) << endl;
}

int main()
{
	for (cin >> testCase; testCase--; node.clear(), graph.clear()) //每次要將node和graph重置
	{
		cin >> cityNum >> limitDis; //輸入城市總數，極限距離
		city.assign(cityNum, two());
		for (int i = 0; i < cityNum; i++) //輸入座標
		{
			cin >> city[i].first >> city[i].second;
		}

		for (int i = 0; i < cityNum; node.push_back(point(i++, 0))); //設定每個點的parent和rank(每個點的parent都預設為自己，rank初始為0)
		for (int start = 0; start < city.size(); start++) //將所有點互相連接(此時的連接可看成虛線，還未真正連成邊)
		{
			for (int cur = start + 1; cur < city.size(); cur++) //存入所有可能的邊(起點、終點和邊長，2點在座標上的連線長度以畢氏定理算出)
			{
				graph.push_back(edge(start, cur, sqrt(pow(city[cur].first - city[start].first, 2) + pow(city[cur].second - city[start].second, 2))));
			}
		}

		kruskcal();
	}

	system("pause");
}