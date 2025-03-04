#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

vector<vector<int>>graph;
int employee, friendNum, id, testCase; //���u�`�ơB�C�ӭ��u���B�ͼơB���u�s���B�����

void BFS()
{
	cin >> id; //��J���u�s��
	if (graph[id].empty()) //�Y�ӽs�����}�C��size��0
	{
		cout << 0 << endl; //�N��ӭ��u�S�B��
		return;
	}

	queue<int>temp;
	vector<int>dis(graph.size()), max(graph.size() + 1); //distance�s�C���I���_�l�I���Z���Bmax���ĴX��(index)���̦h�쥻�����D���H�o������(0���ϥ�)
	temp.push(id); //��l���Nstart�[�Jqueue��
	for (int cur; temp.size();) //cur == ��e���I�B�Yqueue��size()����0
	{
		cur = temp.front(); //�C���Nqueue�̫e�����������X��
		temp.pop(); //����Nqueue�����Ӥ����R��
		for (int x = 0; x < graph[cur].size(); x++) //���cur�ҳs�����Ҧ����I
		{
			if (graph[cur][x] != id && dis[graph[cur][x]] == 0) //�Y���U�ӭn���X�����I != �_�I�A�B���I == 0 (�٥����L)
			{
				dis[graph[cur][x]] = dis[cur] + 1; //�h���U�Ӹ��I���Z������e���Z�� + 1
				max[dis[graph[cur][x]]]++; //�̤j�Z�� + 1
				temp.push(graph[cur][x]); //�ñN���I�[�Jqueue
			}
		}
	}

	auto it = max_element(max.begin() + 1, max.end()); //��X���@��(index)���ȳ̤j�A�q��1�Ѷ}�l��
	cout << *it << " " << it - max.begin() << endl; //��X�ӭȤΨ�index
}

int main()
{
	cin >> employee; //��J�H��
	graph.assign(employee, vector<int>()); //�ع�
	for (int y = 0; y < employee; y++) //���C�ӭ��u�B��J�B�ͼƨë����Y��
	{
		cin >> friendNum;
		graph[y].assign(friendNum, int());
		for (int x = 0; x < friendNum; cin >> graph[y][x++]);
	}

	for (cin >> testCase; testCase--; BFS()); //��J�X������A�C���HBFS�䵪��
	system("pause");
}