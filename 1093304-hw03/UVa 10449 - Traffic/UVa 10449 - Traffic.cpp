#include<iostream>
#include<vector>
#include<climits>
#include<cmath>
#include<set>
using namespace std;

struct edge //���(�v��)�B���I
{
	int weight = 0, end = 0;
};

int testNum = 1, nodeNum, lineNum, endNum; //����B�I�ӼơB��ӼơB���I�Ӽ�
vector<int>nodeVal, dis; //�C���I����l�w�]�ȡB�Z��(��(�_�I - ���I)^3)
vector<vector<edge>>graph;
set<int> negative_ring; //�N�t���W���I�s�_��

void Bellman_Ford()
{
	dis[1] = 0; //��l�N�_�I�]��0
	for (nodeNum--; nodeNum--;) //Bellman_Ford�����I�A�`�@�]nodeNum - 1��(���F�_�l�I�@�}�l�N�]��0)�A�C������Ϩ䤤�@�I�T�w���̵u���|
	{
		for (int y = 1; y < graph.size(); y++)
		{
			for (int x = 0; x < graph[y].size(); x++)
			{
				//�Y��e�I���Ȥ��O�̤j�ȡA�B����s���쪺�I > ��e���I + �v���᪺��
				if (dis[y] != INT_MAX && dis[graph[y][x].end] > dis[y] + graph[y][x].weight)
				{
					dis[graph[y][x].end] = dis[y] + graph[y][x].weight; //�h�N�ӭȵ�����s���쪺�I
				}
			}
		}
	}

	for (int y = 1; y < graph.size(); y++) //���ɩҦ��I���ȬҬ��̵u���|(�M�ӭY���t���h�L�k�T�w�̵u���|���ȡA���i�Ǧ��P�_�O�_���t��)
	{
		for (int x = 0; x < graph[y].size(); x++)
		{
			if (dis[graph[y][x].end] > dis[y] + graph[y][x].weight) //�Y����s���쪺�I�����ٯ�A��u
			{
				dis[graph[y][x].end] = dis[y] + graph[y][x].weight; //�h�~��N�ȧ��p
				negative_ring.insert(graph[y][x].end); //�å[�Jset��(�b�t�������h�`���@�ѭȤ@�w�|�p��3)
			}
		}
	}
}

int main()
{
	for (; cin >> nodeNum; negative_ring.clear())
	{
		graph.assign(nodeNum + 1, vector<edge>()); //����0
		nodeVal.assign(nodeNum + 1, int()); //����0
		dis.assign(nodeNum + 1, INT_MAX); //����0
		for (int i = 1; i <= nodeNum; cin >> nodeVal[i++]); //�s�J�C���I����
		cin >> lineNum;	
		for (int y; lineNum--;) //�ع�
		{
			cin >> y;
			graph[y].push_back(edge());
			cin >> graph[y].back().end;
			graph[y].back().weight = pow(nodeVal[graph[y].back().end] - nodeVal[y], 3); //�D�حn�D�v����(�_�I - ���I)^3
		}

		if (nodeNum) //�Y�I�ӼƫD0�N�]�t��k
		{
			Bellman_Ford();
		}

		cin >> endNum; //��J�n���쪺���I�Ӽ�
		cout << "Set #" << testNum++ << endl;
		for (int end; endNum--;)
		{
			cin >> end;
			if (negative_ring.count(end) || dis[end] < 3 || dis[end] == INT_MAX) //�Y�ҨD�����I�s�b��t�� || �� < 3 || �L�k����
			{
				cout << "?" << endl; //�h��X�ݸ�
				continue;
			}

			cout << dis[end] << endl; //�_�h��X�̵u���|
		}
	}

	system("pause");
}