#include<iostream>
#include<iomanip>
#include<queue>
#include<climits>
using namespace std;

struct edge //�e�q�M��O
{
	double capacity, cost;
};

int car, bank; //���ơB�Ȧ��
vector<bool>inQueue; //��e�������O�_�bQueue��
vector<int>parent;
vector<double>dis;  //�Z�����I���e�I�һݪ��`cost
vector<vector<edge>>graph; //�C����s���e�q�P��O

bool SPFA(const int& start, const int& end)
{
	parent.assign(graph.size(), 0); //parent��l��
	dis.assign(graph.size(), INT_MAX); //�Z����l���̤j
	inQueue.assign(graph.size(), false); //�Ҧ��bqueue�������A���w�]��false
	queue<int>q;
	dis[start] = 0.0; //�_�I���Z����0
	q.push(start);
	for (int u; q.size();)
	{
		u = q.front();
		q.pop();
		inQueue[u] = false;
		for (int v = start; v <= end; v++) //���Ҧ����I
		{
			//�Yu �� v ���e�q(�N��2�I���إ���)�A�B���U�ӭn���쪺�I�A��cost > ��e2�I����cost
			if (graph[u][v].capacity && dis[v] > dis[u] + graph[u][v].cost)
			{
				dis[v] = dis[u] + graph[u][v].cost; //�h��sdis[v]����I�Ҫ᪺cost
				parent[v] = u; //v��parent�]��u
				if (inQueue[v] == false) //�Y��Hv���bQueue
				{
					q.push(v); //�h�N��[�Jqueue��
					inQueue[v] = true; //�bqueue�������A�]��true
				}
			}
		}
	}

	return dis[end] != INT_MAX; //�Y���I��dis == �̤j�ȡA�N��w�g�L���i������I�A�^��false
}

void MCMF(const int& start, const int& end)
{
	double minCost = 0.0; //�̤p��O
	while (SPFA(start, end))
	{
		double minCapacity = INT_MAX; //��l�N�̤p�e�q�]���̤j��
		for (int v = end; v != start; v = parent[v]) //v�q���I�}�l�F�Yv�٨S����_�I�F�C�����e����v��parent
		{
			minCapacity = min(minCapacity, graph[parent[v]][v].capacity); //2�e�q���̤p
		}

		minCost += minCapacity * dis[end]; //dis[nodeNum] == 1���capacity�q�_�I����I�һݪ��̤p��O
		for (int v = end; v != start; v = parent[v]) //v�q���I�}�l�F�Yv�٨S����_�I�F�C�����e����v��parent
		{
			graph[parent[v]][v].capacity -= minCapacity; //�ӱ����|�W�Ҧ���capacity - �̤p��capacity
			graph[v][parent[v]].capacity += minCapacity; //�ӱ����u�W���ϦVcapacity + �̤p��capacity
		}
	}

	cout << fixed << setprecision(2) << minCost / bank + 0.001 << endl; //�̫��X�����ɶ�
}

int main()
{
	while (cin >> bank >> car, bank) //��l����J�Ȧ�M�����ƶq
	{
		graph.assign(car + bank + 2, vector<edge>(car + bank + 2));
		for (int b = 1; b <= bank; b++) //�عϡA���D�����V��
		{
			for (int c = 1; c <= car; c++)
			{
				cin >> graph[c][car + b].cost;
				graph[car + b][c].cost = -graph[c][car + b].cost; //�ϦV��cost���t
				graph[c][car + b].capacity = 1; //�Ҧ�capacity���w�]��1
			}
		}

		for (int i = 1; i <= car; i++) //�q�̪���I���C�x����capacity�]���]��1
		{
			graph[0][i].capacity = 1;
		}

		for (int i = car + 1; i < graph.size() - 1; i++) //�s���qcar + 1�_�N�O�Ȧ��m�s��
		{
			graph[i][graph.size() - 1].capacity = 1; //���Ҧ����Ȧ泣�s�u�ܤ@�Ӳ��I
		}

		MCMF(0, graph.size() - 1); //�_�I��0
	}

	system("pause");
}