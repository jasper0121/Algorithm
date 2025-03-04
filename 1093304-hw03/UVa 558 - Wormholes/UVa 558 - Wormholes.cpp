#include<iostream>
#include<vector>
#include<climits>
using namespace std;

struct edge //�䪺����(�v��)�β��I
{
	int weight = 0, end = 0;
};

int testCase, nodeNum, lineNum; //����B�I�ӼơB��Ӽ�
vector<vector<edge>>graph; //�C�@�椺������β��I

void Bellman_Ford()
{
	vector<int>dis(nodeNum, INT_MAX); //��l�U���I���ȳ��]���̤j��
	dis[0] = 0; //��l�N�_�I�]��0
	for (nodeNum--; nodeNum--; ) //Bellman_Ford�����I�A�`�@�]nodeNum - 1��(���F�_�l�I�@�}�l�N�]��0)�A�C������Ϩ䤤�@�I�T�w���̵u���|
	{
		for (int y = 0; y < graph.size(); y++)
		{
			for (int x = 0; x < graph[y].size(); x++)
			{
				if (dis[y] != INT_MAX && dis[graph[y][x].end] > dis[y] + graph[y][x].weight) //�Y��e�I���Ȥ��O�̤j��
				{
					//�Y����s���쪺�I > ��e���I + �v���᪺�ȡA�h�N�ӭȵ�����s���쪺�I
					dis[graph[y][x].end] = dis[y] + graph[y][x].weight;
				}
			}
		}
	}

	for (int y = 0; y < graph.size(); y++) //���ɩҦ��I���ȬҬ��̵u���|(�M�ӭY���t���h�L�k�T�w�̵u���|���ȡA���i�Ǧ��P�_�O�_���t��)
	{
		for (int x = 0; x < graph[y].size(); x++)
		{
			if (dis[graph[y][x].end] > dis[y] + graph[y][x].weight) //�Y����s���쪺�I�����ٯ�A��u
			{
				cout << "possible\n"; //�h�N���t��
				return;
			}
		}
	}

	cout << "not possible\n"; //�����즹�h�N��S���t��
}

int main()
{
	for (cin >> testCase; testCase--;)
	{
		cin >> nodeNum >> lineNum; //�C����J�I�ӼƩM��Ӽ�
		graph.assign(nodeNum, vector<edge>()); //�ع�
		for (int y; lineNum--;)
		{
			cin >> y;
			graph[y].push_back(edge());
			cin >> graph[y].back().end >> graph[y].back().weight;
		}

		Bellman_Ford();
	}

	system("pause");
}