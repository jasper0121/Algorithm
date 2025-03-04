#include<iostream>
#include<queue>
#include<climits>
using namespace std;

vector<int>layer; //�Ҧ��I�M0���̵u�Z���A�P�ɥN��h�ơA�Y���I���h�ƫD0�h�N��i�H�q�_�I������I(�_�I��0���~)
vector<vector<int>>graph;

int dinicBFS()
{
	queue<int>temp;
	layer.assign(graph.size(), int()); //��l�U�I���h�Ƭҳ]��0
	temp.push(1); //��l�N�_�I�]��0
	layer[1] = 1; //�_�I��layer�]��1
	for (int y; temp.size();) //y == ��e���I�B�Yqueue��size()����0
	{
		y = temp.front(); //�C���Nqueue�̫e�����������X��
		temp.pop(); //����Nqueue�����Ӥ����R��
		for (int x = 1; x < graph[y].size(); x++) //�C���qx = 1�}�l(�Y�q0�}�l�h�a�J�H�U����|���ҥ~)
		{
			if (graph[y][x] && layer[x] == 0) //�Yy��x���٦��e�q�A�B�٥��]�wx���ĴX�h
			{
				layer[x] = layer[y] + 1; //�h�Nx�]��y���h�� + 1
				temp.push(x); //�ñN���I�[�Jqueue��
			}
		}
	}

	return layer.back(); //�̫�^�ǲ��I���h�ơA�Y���I���h�Ƭ�0�A�h�N��q�_�I�w�g�L�k������I
}

int dinicDFS(int cur, int capacity) //��e���I�B�e�q�A��l�ǤJ�_�I�B�e�q�L��
{
	if (cur == graph.size() - 1) //�Y������I
	{
		return capacity; //�h�^�Ƿ�e���e�q(���ɷ|�O�̤p�e�q)
	}

	for (int minCapacity, x = 0; x < graph[cur].size(); x++) //�q�_�I���e�I�����Ҹg�L���̤p�e�q�F�ؼбq1�}�l
	{
		//�Y��e���e�q�D0�A���u�u�۶��h�����Ǩ��A�b�ӱ����u�W��X�̤p���e�q�A�B�Ӯe�q�D0��
		if (graph[cur][x] && layer[x] == layer[cur] + 1 && (minCapacity = dinicDFS(x, min(graph[cur][x], capacity))))
		{
			graph[cur][x] -= minCapacity; //��e���u�W���C�Ӯe�q - ���u�W�ҧ�쪺�̤p�e�q
			graph[x][cur] += minCapacity; //��e���u�W���C�ӳѾl�e�q + ���u�W�ҧ�쪺�̤p�e�q
			return minCapacity; //�^�Ǹӱ����|�W�ҧ�쪺�̤p�e�q
		}
	}

	return 0; //�Y��e�w�S��������|�i�H������I�A�h�^��0
}

void dinic()
{
	int maxflow = 0; //�Ӻ������̤j�y�q
	while (dinicBFS()) //�C����BFS�@���A�Y�^�ǭȫD0�A�N���ٯ��~���̤j�y�q
	{
		for (int min; min = dinicDFS(1, INT_MAX); maxflow += min); //�C����X�Ӹ��|�W���̤p�e�q�A�ñN��ȥ[�J�̤j�y�q���A�Ymin == 0�h�N����
	}

	cout << maxflow << endl; //��X�̤j�y�q
}

int main()
{
	for (int nodeNum, edgeNum, node, capacity; cin >> nodeNum >> edgeNum, nodeNum;)
	{
		graph.assign(2 * nodeNum + 1, vector<int>(2 * nodeNum + 1));
		for (int i = nodeNum - 2; i--;) //�������I
		{
			cin >> node >> capacity;
			graph[node][node + nodeNum] = graph[node + nodeNum][node] = capacity;
		}

		for (int start, end; edgeNum--;) //�L�V�ϫع�
		{
			cin >> start >> end >> capacity;
			graph[start][end + nodeNum] = graph[end][start + nodeNum] = capacity;
		}

		dinic(); //�ϥ�dinic�t��k��̤j�y�q(��XBFS�MDFS)
	}

	system("pause");
}