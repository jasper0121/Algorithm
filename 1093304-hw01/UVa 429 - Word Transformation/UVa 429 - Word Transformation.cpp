#include<iostream>
#include<string>
#include<queue>
#include<map>
using namespace std;

map<string, int>dic; //�r��
vector<vector<int>>graph; //��

int BFS(const int& start, const int& end)
{
	if (start == end) //�Y�_�I�M���I�@�}�l�N�ۦP
	{
		return 0; //�h���|��0
	}

	queue<int>temp;
	vector<int>dis(graph.size()); //�s�C�ӳ�r�Mstart���Z��
	temp.push(start); //��l���Nstart�[�Jqueue��
	for (int cur; temp.size();) //cur == ��e���I�B�Yqueue��size()����0
	{
		cur = temp.front(); //�C���Nqueue�̫e�����������X��
		temp.pop(); //����Nqueue�����Ӥ����R��
		for (int x = 0; x < graph[cur].size(); x++) //���cur�ҳs�����Ҧ����I
		{
			if (graph[cur][x] != start && dis[graph[cur][x]] == 0) //�Y���U�ӭn���X�����I != �_�I�A�B���I == 0 (�٥����L)
			{
				dis[graph[cur][x]] = dis[cur] + 1; //�h���U�Ӹ��I���Z������e���Z�� + 1
				temp.push(graph[cur][x]); //�ñN���I�[�Jqueue
			}

			if (graph[cur][x] == end) //�Y��e���I == ���I
			{
				return dis[graph[cur][x]]; //�h�^�ǲ��I���Z��
			}
		}
	}
}

int main()
{
	int testCase; //����
	cin >> testCase;
	cin.ignore(); //���U�ӷ|�Ψ�getline�A�G��ignore�M���w�İ�
	string word; //��J�r���r
	for (getline(cin, word); testCase--; dic.clear()) //����J����B�C���r�孫�m
	{
		for (int i = 0; getline(cin, word), word != "*"; dic.insert({ word,i++ })); //�C���N��r���@�Ӱߤ@�s���é�J�r�夤(first == ��r�Bsecond == �s��)
		graph.assign(dic.size(), vector<int>()); //�عϡA�䤤index == ��r�s��
		for (auto curIt = dic.begin(); curIt != dic.end(); curIt++)
		{
			for (auto target = curIt; ++target != dic.end(); )
			{
				if (curIt->first.size() == target->first.size()) //���C�ӳ�r�A�Y��즳��L��r�����׻P��e�ۦP
				{
					int diff = 0; //�r���t����
					for (int i = 0; i < curIt->first.size(); i++)
					{
						diff += curIt->first[i] != target->first[i]; //�Y��e2��r���r�����P�hdiff�| + 1 (true)�A�Ϥ��h�| + 0 (false)
					}

					if (diff == 1) //�Y�u�t1�Ӧr���A�h�N2�s�����ۥ[�J���index���}�C��
					{
						graph[curIt->second].push_back(target->second);
						graph[target->second].push_back(curIt->second);
					}
				}
			}
		}

		for (string input; getline(cin, input), input != "";) //��J�_�I�M���I
		{
			string start = input.substr(0, input.find(' ')); //�binput�������_�I�M���I(2�r��)
			string end = input.substr(start.size() + 1);
			cout << start << " " << end << " " << BFS(dic[start], dic[end]) << endl; //�N�������s���@��BFS�Ѽ�
		}

		if (testCase) //�YtestCase == 0�h������
		{
			cout << endl;
		}
	}

	system("pause");
}