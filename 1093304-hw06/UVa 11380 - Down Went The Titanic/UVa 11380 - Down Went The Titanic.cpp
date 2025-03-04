#include<iostream>
#include<queue>
#include<climits>
using namespace std;

int row, col, capacity; //�C�B��B�e�q
const int dir[5]{ 0,1,0,-1,0 }; //��V�A�W�k�U��
vector<int>layer; //�Ҧ��I�M0���̵u�Z���A�P�ɥN��h�ơA�Y���I���h�ƫD0�h�N��i�H�q�_�I������I(�_�I��0���~)
vector<vector<int>>graph;

int dinicBFS()
{
	queue<int>temp;
	layer.assign(graph.size(), int()); //��l�U�I���h�Ƭҳ]��0
	temp.push(0); //��l�N�_�I�]��0
	layer[0] = 1; //�_�I��layer�]��1
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
		for (int min; min = dinicDFS(0, INT_MAX); maxflow += min); //�C����X�Ӹ��|�W���̤p�e�q�A�ñN��ȥ[�J�̤j�y�q���A�Ymin == 0�h�N����
	}

	cout << maxflow << endl; //��X�̤j�y�q
}

int main()
{
	for (char input; cin >> row >> col >> capacity;)
	{
		graph.assign(2 * row * col + 2, vector<int>(2 * row * col + 2)); //�n�����I�A�[�W�_�I�M���I
		for (int y = 1; y <= row; y++)
		{
			for (int x = 1, cur = col * (y - 1) + x; x <= col; x++, cur++) //�ع�
			{
				cin >> input;
				switch (input)
				{
				case '*': //���B�W���H�Acapacity == 1
					graph[cur][cur + row * col] = graph[0][cur] = 1;
					break;
				case '.': //���B�Acapacity == 1
					graph[cur][cur + row * col] = 1;
					break;
				case '@': //�p�B�Acapacity == �L��
					graph[cur][cur + row * col] = INT_MAX;
					break;
				case '#': //���Y�A���I
					graph[cur][cur + row * col] = INT_MAX;
					graph[cur + row * col][graph.size() - 1] = capacity; //�̫�N�Ҧ�����s����@�Ӳ��I
					break;
				}

				for (int next_x, next_y, nextPos, i = 0; i < 4; i++)
				{
					next_x = x + dir[i]; //�U�@��x�y��
					next_y = y + dir[i + 1]; //�U�@��y�y��
					if (next_x == 0 || next_x > col || next_y == 0 || next_y > row) //�Y�U�Ӯy�жW�X�d��~
					{
						continue; //�h�H�U���B�z
					}

					graph[cur + row * col][col * (next_y - 1) + next_x] = INT_MAX; //���I�᪺�I �� �U���I��capacity == �L��
				}
			}
		}

		dinic(); //�ϥ�dinic�t��k��̤j�y�q(��XBFS�MDFS)
	}

	system("pause");
}