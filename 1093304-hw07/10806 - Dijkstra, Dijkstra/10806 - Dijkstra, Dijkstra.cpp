#include<iostream>
#include<queue>
#include<climits>
using namespace std;

struct Edge //�C�@��edge�s���_�I�B���I�B�e�q�B����
{
	int start, end, capacity, cost;
	Edge(const int& s, const int& e, const int& ca, const int& co)
	{
		start = s;
		end = e;
		capacity = ca;
		cost = co;
	}
};

int  nodeNum, edgeNum; //�I�ӼơB���`�ơB�n�ǰe����Ƥj�p�B�C���䪺�e�q
vector<Edge>edge; //���L�V�ϡA�C2�I���n�s4����
vector<vector<int>>graph; //outgoingEdges�A�s�C���I�s��U���I�bedge������m(index)
vector<int>dis, parent; //dis�۷��A�Z�����I���e�I�һݪ��`cost
vector<bool>inQueue; //��e�������O�_�bQueue��

void addEdge(const int& start, const int& end, const int& capacity, const int& cost, int& edgeNo) //�إ���
{
	edge.push_back({ end,start, 0,-cost }); //���إߤϦV����
	graph[start].push_back(edgeNo++); //�o�ˤ~��bgraph��start�s��end(�o��push_back���O���ت�edge index)
	edge.push_back({ start, end,capacity,cost }); //�A�ӫإ��V��
	graph[end].push_back(edgeNo++); //�bgraph��end�s��start
}

bool SPFA(const int& start, const int& end)
{
	parent.assign(graph.size(), -1); //parent��l��
	dis.assign(graph.size(), INT_MAX); //�Z����l���̤j
	inQueue.assign(graph.size(), false); //�Ҧ��bqueue�������A���w�]��false
	queue<int>q;
	dis[start] = 0; //�_�I���Z����0
	q.push(start);
	for (int u, v; q.size();)
	{
		u = q.front();
		q.pop();
		inQueue[u] = false;
		for (int e : graph[u]) //���u�I�s���쪺�Ҧ���(e == �䪺�s��)
		{
			v = edge[e].start; //�C���Nqueue�̫e�����������X�ӡA�C���䪺start�N�Ou�ҳs���쪺�I
			if (edge[e].capacity && dis[v] > dis[u] + edge[e].cost) //�Y����W�٦��e�q�A�B���U�ӭn���쪺�I�A��cost > ��e�I�ֿn��cost + 2�I����cost
			{
				dis[v] = dis[u] + edge[e].cost; //�h��sdis[v]����I�Ҫ᪺cost
				parent[v] = e; //�N��eedge��start��parent�]���Ҧb��index
				if (inQueue[v] == false) //�Y��Hv���bQueue
				{
					q.push(v); //�h�N��[�Jqueue��
					inQueue[v] = true; //�bqueue�������A�]��true
				}
			}
		}
	}

	return dis[graph.size() - 1] != INT_MAX; //�Y���I��dis == �̤j�ȡA�N��w�g�L���i������I�A�^��false
}

void MCMF(const int& start, const int& end)
{
	int maxflow = 0, minCost = 0, counter = 0; //�̤j�y�q�B�̤p��O�B�p�⨫�F�X���A�D�حn�D�̦h��2���N�n��
	for (; counter != 2 && SPFA(start, end); counter++) //�Y���F2���h���X�j��
	{
		int minCapacity = INT_MAX; //��l�N�̤p�e�q�]���̤j��
		//v�q���I�}�l�F�Yv�٨S����_�I�Fparent[v] == ����Ҧbindex�A�ҥHedge[parent[v]].end == ���䪺start
		for (int v = end; v != start; v = edge[parent[v]].end)
		{
			minCapacity = min(minCapacity, edge[parent[v]].capacity); //2�e�q���̤p
		}

		maxflow += minCapacity; //�����|�W�̤p��capacity == �����|�W�үಣ�ͪ��̤j�y�q
		minCost += minCapacity * dis[nodeNum]; //dis[nodeNum] == 1���capacity�q�_�I����I�һݪ��̤p��O
		//v�q���I�}�l�F�Yv�٨S����_�I�Fparent[v] == ����Ҧbindex�A�ҥHedge[parent[v]].end == ���䪺start
		for (int v = end; v != start; v = edge[parent[v]].end)
		{
			edge[parent[v]].capacity -= minCapacity; //�ӱ����|�W�Ҧ���capacity - �̤p��capacity
			edge[parent[v] ^ 1].capacity += minCapacity; //�ӱ����u�W���ϦVcapacity + �̤p��capacity
		}
	}

	if (counter == 2) //�Ymaxflow�̫� >= ��Ƥj�p�A�N���Ӹ�Ƴ�����ǥѦ������ǿ�
	{
		cout << minCost << "\n"; //�G��X�̤p����O
		return;
	}

	cout << "Back to jail\n";
}

int main()
{
	for (int start, end, cost, edgeNo; cin >> nodeNum, nodeNum; edge.clear()) //��󤧫�n�s���Ҧ��䵹���@�ӽs���B�C����J�I�Ӽ�
	{
		cin >> edgeNum; //��J��Ӽ�
		graph.assign(nodeNum + 2, vector<int>()); //�I�Ӽ� + �_�I + ���I
		for (addEdge(0, 1, 2, 0, edgeNo = 0); edgeNum--;) //�ع�(�s�䪺�覡)�A��l�إ߭��I�A��capacity == ����n��J��dataSize
		{
			cin >> start >> end >> cost;
			addEdge(start, end, 1, cost, edgeNo); //���V����
			addEdge(end, start, 1, cost, edgeNo); //�ϦV����
		}

		addEdge(nodeNum, nodeNum + 1, 2, 0, edgeNo); //�إ߲��I
		edge[edge.size() - 2].capacity = edge[0].capacity = 2; //�q�_�I�}�l�M�s�V���I��capacity���]��2
		MCMF(0, graph.size() - 1); //�q0���I�]��nodeNum���I
	}

	system("pause");
}