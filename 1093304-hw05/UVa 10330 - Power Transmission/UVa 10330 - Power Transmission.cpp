#include<iostream>
#include<queue>
#include<climits>
using namespace std;

vector<int>layer; //�Ҧ��I�M0���̵u�Z���A�P�ɥN��h�ơA�Y���I���h�ƫD0�h�N��i�H�q�_�I������I(�_�I��0���~)
vector<vector<int>>graph; //�s2�I�����e�q

int dinicBFS()
{
	queue<int>temp;
	layer.assign(graph.size(), int()); //��l�U�I���h�Ƭҳ]��0
	temp.push(0); //��l�N�_�I�]��0(�]���_�I�q0�}�l��)
	layer[0] = 1;
	for (int y; temp.size();) //y == ��e���I�B�Yqueue��size()����0
	{
		y = temp.front(); //�C���Nqueue�̫e�����������X��
		temp.pop(); //����Nqueue�����Ӥ����R��
		for (int x = 1; x < graph[y].size(); x++) //�C���qx = 1�}�l(�b��BFS�ɤ��|���^���I)
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
		for (int min; min = dinicDFS(0, INT_MAX); maxflow += min); //�C����X�Ӹ��|�W���̤p�e�q�A�ñN��ȥ[�J�̤j�y�q���A�Ymin == 0�h�N����
	}

	cout << maxflow << endl; //��X�̤j�y�q
}

int main()
{
	for (int nodeNum, edgeNum, start = 0, end = 0; cin >> nodeNum;) //�I�ӼơB��ӼơB�_�I�B���I�F�C������J���X���I
	{
		//�عϡA�C���I�]���ۤv���e�q�A�G�n�������I�C�`�I�ӼƬ��G2�����I�Ӽ� + ��ӹϪ��_�I�P���I
		graph.assign(2 * nodeNum + 2, vector<int>(2 * nodeNum + 2, int()));
		for (int i = 1; i <= nodeNum; i++) //�N��J���e�q�ഫ��2�I�����Z��(��C���I�����I)
		{
			cin >> graph[i][i + nodeNum];
		}

		for (cin >> edgeNum; edgeNum--; ) //����J�X����A��J�C���䪺�_�I�B���I�M�e�q
		{
			cin >> start >> end;
			cin >> graph[start + nodeNum][end];
		}

		cin >> start >> end; //�o��start�Mend���N�q�ন���X���I�M��ӹϪ��_�I�M���I�s��
		for (int x; start--;) //0���I�|�M���U�ӭn��J���estart���I�s��
		{
			cin >> x; //��J�|�Q0���J���I
			graph[0][x] = INT_MAX; //0�Mx���I�������e�q�]���L���j
		}

		for (int x; end--;) //�ѤU��end���I�|�M���I�s��
		{
			cin >> x; //��J�|������I���I
			graph[x + nodeNum][graph.size() - 1] = INT_MAX; //���I�M���I�����Z���]���L���j
		}

		dinic(); //�ϥ�dinic�t��k��̤j�y�q(��XBFS�MDFS)
	}

	system("pause");
}