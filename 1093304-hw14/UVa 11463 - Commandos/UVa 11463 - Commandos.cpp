#include<iostream>
#include<vector>
#define INF 10000000
using namespace std;

int main()
{
	vector<vector<int>>graph;
	int testCase;
	cin >> testCase;
	for (int node, line, Case = 1; testCase--;)
	{
		cin >> node >> line; //��J�ؿv���Ӽ�(�I�Ӽ�)�B�D����
		graph.assign(node, vector<int>(node, INF)); //��l�v���]���L���j
		for (int i = 0; i < graph.size(); i++) //�ۤv����ۤv�����|�����w��0
		{
			graph[i][i] = 0;
		}

		for (int u, v; line--;) //�����V��
		{
			cin >> u >> v;
			graph[u][v] = graph[v][u] = 1; //2�I�����Z��(�v��)�T�w��1
		}

		for (int mid = 0; mid < graph.size(); mid++) //�򬥨̼w�t��k�A�Ҧ�u��v���i����|���A�����u�̵u��
		{
			for (int u = 0; u < graph.size(); u++)
			{
				for (int v = 0; v < graph.size(); v++)
				{
					graph[u][v] = min(graph[u][v], graph[u][mid] + graph[mid][v]);
				}
			}
		}

		int start, end, maxDis = 0; //�_�I�B���I�B�̤j�Z��
		cin >> start >> end;
		//�D�بD�Ҧ��I�������è�����I�Ҫ᪺�̵u�ɶ��A�B�ѩ󦳦h�ӤH�P�ɱq�_�I�X�o
		for (int mid = 0; mid < graph.size(); mid++) //�]�����D���P��u�_�I �� �̻����I �� ���I�v�Ҩ����̤j�Z��
		{
			maxDis = max(maxDis, graph[start][mid] + graph[mid][end]);
		}

		cout << "Case " << Case++ << ": " << maxDis << "\n"; //�̫�L�X�̤j�Z��
	}

	system("pause");
}