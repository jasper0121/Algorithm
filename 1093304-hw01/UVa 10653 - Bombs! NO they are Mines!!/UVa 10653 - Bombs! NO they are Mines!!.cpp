#include<iostream>
#include<queue>
using namespace std;

const int dir[5]{ 0,1,0,-1,0 }; //��V(�W�k�U��)
int row, col, rowBomb, start_row, start_col, end_row, end_col; //�C�B��B�X�C�����u�B�_�I�M���I�y��
vector<vector<int>>graph; //�C��N��q�_�I��Ӯy�Ъ��Z��

void BFS()
{
	queue<pair<int, int>>temp;
	temp.push({ start_row,start_col }); //��l���N�_�I�y�Х[�Jqueue��
	for (int cur_row, cur_col; temp.size();) //��e�y�СFqueue�����Ť~���X
	{
		cur_row = temp.front().first; //�C���Nqueue���̫e�����y�Ш��X�ӧ@����e�y��
		cur_col = temp.front().second;
		temp.pop(); //���X����N�Ӥ����qqueue���R��
		for (int next_row, next_col, i = 0; i < 4; i++) //���U�ӭn���쪺�y�СF�W�k�U���U���@��
		{
			next_row = cur_row + dir[i + 1]; //�C�����N�U�Ӯy�Эq�n
			next_col = cur_col + dir[i];
			if (next_row < 0 || next_row == row || next_col < 0 || next_col == col) //�Y�U�Ӯy�жW�X�d��~
			{
				continue; //�h�H�U���B�z
			}

			if (graph[next_row][next_col] == 0 && !(next_row == start_row && next_col == start_col)) //�Y�U�Ӯy�Ъ��� == 0(�����L)�A�B�Ӯy�ЫD�_�l�I
			{
				graph[next_row][next_col] = graph[cur_row][cur_col] + 1; //�h�Ӯy�Ъ��Z�� == ��e�Ҧb�y�� + 1
				temp.push({ next_row,next_col }); //�A�N�U�Ӯy�Х[�Jqueue��
			}
		}
	}

	cout << graph[end_row][end_col] << endl; //��X�q�_�I��Ӯy�Ъ��Z��
}

int main()
{
	while (cin >> row >> col, row)
	{
		graph.assign(row, vector<int>(col)); //�ھ�row�Mcolumn�ع�
		cin >> rowBomb;
		for (int x, y, bombNum; rowBomb--;)
		{
			for (cin >> y >> bombNum; bombNum--;)//�C������J�ĴX�C�θӦC�����u��
			{
				cin >> x;
				graph[y][x] = -1; //�N���u�s�b����m�]��-1
			}
		}

		cin >> start_row >> start_col >> end_row >> end_col; //��J�_�l�M���I�y��
		BFS(); //��BFS�䵪��
	}

	system("pause");
}