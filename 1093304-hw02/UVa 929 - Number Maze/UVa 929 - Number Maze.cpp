#include<iostream>
#include<queue>
using namespace std;
using three = pair<size_t, pair<size_t, size_t>>; //�N����pair�Hthree�N�١A�̧Ǧs��e���I���̤p�Z���Ψ��I�y��

const int dir[5]{ 0,1,0,-1,0 }; //��V(�W�k�U��)
int testCase, row, col; //����B�C�B��
vector<vector<size_t>>weight, graph; //�v��(�i�����D������)�Bgraph�s�Z�_�I���̤p�Z��

void dijkstra()
{
	priority_queue<three, vector<three>, greater<three>>temp; //min heap�Atop���̤p
	temp.push({ graph[0][0] = weight[0][0],{0,0} }); //���N��l�v����J�_�I�A�å[�Jpriority_queue��
	for (int x, y; temp.size();) //�Ypriority_queue��size����0
	{
		x = temp.top().second.first; //�C�����N�y�Ш��X
		y = temp.top().second.second;
		temp.pop(); //���X����N�Ӥ����qpriority_queue���R��
		for (int next_x, next_y, i = 0; i < 4; i++) //���U�ӭn���쪺�y�СF�W�k�U���U���@��
		{
			next_x = x + dir[i]; //�C�����N�U�Ӯy�Эq�n
			next_y = y + dir[i + 1];
			if (next_x < 0 || next_x == col || next_y < 0 || next_y == row) //�Y�U�Ӯy�жW�X�d��~
			{
				continue; //�h�H�U���B�z
			}

			if (graph[next_y][next_x] > graph[y][x] + weight[next_y][next_x]) //�Y�U�Ӯy�Ъ��Z�� > ��e�Z�� + �v��(�D������)
			{
				//�h�N�U�Ӯy�Ъ��Z�� = ��e�Z�� + �v��(�D������)�A�é�Jpriority_queue��
				temp.push({ graph[next_y][next_x] = graph[y][x] + weight[next_y][next_x],{ next_x,next_y } });
			}
		}
	}

	cout << graph[row - 1][col - 1] << endl; //��X�̵u���|
}

int main()
{
	for (cin >> testCase; testCase--;)
	{
		cin >> row >> col; //�C����J�C�M��
		graph.assign(row, vector<size_t>(col, -1)); //�q�n�Ϫ��j�p�A�Ҧ��ȹw�]��-1(�Y�̤j��)
		weight = graph; //�v����l�M�Ϥ@��
		for (int y = 0; y < row; y++) //��J�v��
		{
			for (int x = 0; x < col; cin >> weight[y][x++]);
		}

		dijkstra(); //��̵u���|
	}

	system("pause");
}