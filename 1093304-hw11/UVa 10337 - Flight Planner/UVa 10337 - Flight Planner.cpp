#include<iostream>
#include<vector>
#define INF 100000000
using namespace std;

int main()
{
	int testCase, dis; //����B�_�I�M���I���Z��
	vector<vector<int>>wind, minCost; //���V��(�i�ݦ�2�I������)�B�I�y��(�s�Z���I���̤p��O)
	for (cin >> testCase; testCase--;)
	{
		cin >> dis; //��J�M���I���Z��
		wind.assign(10, vector<int>(dis /= 100)); //dis / 100 == �����Ӽ�
		minCost.assign(10, vector<int>(dis + 1, INF)); //�I�Ӽ� == ��Ӽ� + 1�A��l�ȳ]���L��
		for (int y = 9; y >= 0; y--) //�p�P�y�СA�]���U��(0,0)
		{
			for (int x = 0; x < wind[y].size(); cin >> wind[y][x++]); //��J���V(�v��)
		}

		minCost[0][0] = 0; //���I���̤p��O��0
		for (int x = 1; x < minCost[0].size(); x++) //x�q1�}�l�A�]���|�Ψ�x - 1
		{
			for (int y = 0; y <= 9; y++) //����e���I(����覡�G�W�ɪ�O60�A������O30�A�U����O20)
			{
				if (y) //�Y��e�I��y�y�ЫD0�A�N����I�i�q���U�M���䪺�I����A���2�����u����O���p��(��O == �ֿn��O + ����覡 - �O�_����)
				{
					minCost[y][x] = min(minCost[y - 1][x - 1] + 60 - wind[y - 1][x - 1], minCost[y][x - 1] + 30 - wind[y][x - 1]);
				}

				if (y != 9) //�Y��e���I���O�̤W�����I�A�N����I�i�q���W���I����A�P�_�q���W�����u�O�_���p
				{
					minCost[y][x] = min(minCost[y][x], minCost[y + 1][x - 1] + 20 - wind[y + 1][x - 1]);
				}
			}
		}

		cout << minCost[0].back() << "\n\n"; //��X����I�ɪ��̤p��O
	}

	system("pause");
}