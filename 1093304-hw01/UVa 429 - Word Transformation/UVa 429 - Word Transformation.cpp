#include<iostream>
#include<string>
#include<queue>
#include<map>
using namespace std;

map<string, int>dic; //字典
vector<vector<int>>graph; //圖

int BFS(const int& start, const int& end)
{
	if (start == end) //若起點和終點一開始就相同
	{
		return 0; //則路徑為0
	}

	queue<int>temp;
	vector<int>dis(graph.size()); //存每個單字和start的距離
	temp.push(start); //初始先將start加入queue中
	for (int cur; temp.size();) //cur == 當前的點、若queue的size()不為0
	{
		cur = temp.front(); //每次將queue最前面的元素拿出來
		temp.pop(); //之後將queue中的該元素刪掉
		for (int x = 0; x < graph[cur].size(); x++) //對於cur所連接的所有的點
		{
			if (graph[cur][x] != start && dis[graph[cur][x]] == 0) //若接下來要走訪的該點 != 起點，且該點 == 0 (還未走過)
			{
				dis[graph[cur][x]] = dis[cur] + 1; //則接下來該點的距離為當前的距離 + 1
				temp.push(graph[cur][x]); //並將該點加入queue
			}

			if (graph[cur][x] == end) //若當前該點 == 終點
			{
				return dis[graph[cur][x]]; //則回傳終點的距離
			}
		}
	}
}

int main()
{
	int testCase; //測資
	cin >> testCase;
	cin.ignore(); //接下來會用到getline，故先ignore清除緩衝區
	string word; //輸入字典單字
	for (getline(cin, word); testCase--; dic.clear()) //先輸入換行、每次字典重置
	{
		for (int i = 0; getline(cin, word), word != "*"; dic.insert({ word,i++ })); //每次將單字給一個唯一編號並放入字典中(first == 單字、second == 編號)
		graph.assign(dic.size(), vector<int>()); //建圖，其中index == 單字編號
		for (auto curIt = dic.begin(); curIt != dic.end(); curIt++)
		{
			for (auto target = curIt; ++target != dic.end(); )
			{
				if (curIt->first.size() == target->first.size()) //對於每個單字，若找到有其他單字的長度與當前相同
				{
					int diff = 0; //字母差異數
					for (int i = 0; i < curIt->first.size(); i++)
					{
						diff += curIt->first[i] != target->first[i]; //若當前2單字的字母不同則diff會 + 1 (true)，反之則會 + 0 (false)
					}

					if (diff == 1) //若只差1個字母，則將2編號互相加入對方index的陣列中
					{
						graph[curIt->second].push_back(target->second);
						graph[target->second].push_back(curIt->second);
					}
				}
			}
		}

		for (string input; getline(cin, input), input != "";) //輸入起點和終點
		{
			string start = input.substr(0, input.find(' ')); //在input中提取起點和終點(2字串)
			string end = input.substr(start.size() + 1);
			cout << start << " " << end << " " << BFS(dic[start], dic[end]) << endl; //將對應的編號作為BFS參數
		}

		if (testCase) //若testCase == 0則不換行
		{
			cout << endl;
		}
	}

	system("pause");
}