#include<iostream>
#include<string>
#include<climits>
#include<queue>
using namespace std;

vector<int>layer; //�Ҧ��I�M0���̵u�Z���A�P�ɥN��h�ơA�Y���I���h�ƫD0�h�N��i�H�q�_�I������I(�_�I��0���~)
vector<vector<int>>graph; //�s2�I�����e�q

int dinicBFS()
{
	queue<int>temp;
	layer.assign(38, int()); //��l�U�I���h�Ƭҳ]��0
	temp.push(0); //��l�N�_�I�]��0(�]���_�I�q0�}�l��)
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

int dinicDFS(int cur, int capacity)
{
	if (cur == 37) //�Y������I
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
	while (dinicBFS()) //�C����BFS�@���A�Y�^�ǭȫD0�A�N���ٯ��~���̤j�y�q
	{
		while (dinicDFS(0, INT_MAX)); //�C����X�Ӹ��|�W���̤p�e�q�A�Y == 0�h�N����
	}

	for (int i = 1; i <= 26; i++)
	{
		if (graph[0][i]) //�Y�_�I������r���W������@����capacity > 0
		{
			cout << "!\n"; //�N��L�k���Ƥ��t��
			return;
		}
	}

	vector<char>output(10, '_');
	for (int i = 27; i < 37; i++) //�Ʀr�I
	{
		for (int j = 1; j <= 26; j++) //�r���I
		{
			if (graph[i][j]) //�Y�Ʀr�I �� �^���I > 0(�Y�ϦV��capacity > 0)�N������w���L
			{
				output[i - 27] = j + 64; //�s���I�۹������r��
			}
		}
	}

	for (int i = 0; i < 10; cout << output[i++]); //�̫������X�Y������
	cout << endl;
}

int main()
{
	for (string input; getline(cin, input), input != "";)
	{
		graph.assign(38, vector<int>(38, 0)); //0 == �_�I�B1 ~ 27 == A ~ Z�B28 ~ 37 == 0 ~ 9�B38 == ���I

		do //�ع�
		{
			graph[0][input[0] - 64] = input[1] - '0'; //����capacity
			for (int i = 3; i < input.size() - 1; i++) //��󤧫�|�s���쪺�I(�^��r�����Ʀr)������capacity���]��1
			{
				graph[input[0] - 64][input[i] - 21] = 1;
			}
		} while (getline(cin, input), input != "");

		for (int i = 27; i < 38; graph[i++][37] = 1); //�Ҧ��Ʀr�I���s������I�A��e�q���]��1
		dinic();
	}

	system("pause");
}