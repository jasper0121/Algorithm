#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	vector<int>dragon, knight; //�s�Y�B�M�h����
	for (int dragonNum, knightNum; cin >> dragonNum >> knightNum, dragonNum; )//�s�ƶq�B�M�h��
	{
		int total = 0; //�`��O
		dragon.assign(dragonNum, int());
		knight.assign(knightNum, int());
		for (int i = 0; i < dragonNum; cin >> dragon[i++]); //��J�s�Y���|
		for (int i = 0; i < knightNum; cin >> knight[i++]); //��J�M�h����
		sort(dragon.begin(), dragon.end()); //�s�Y���|�Ѥp��j�Ƨ�
		sort(knight.begin(), knight.end()); //�M�h�����Ѥp��j�Ƨ�

		int d = 0, k = 0; //dragon��index�Bknight��index
		for (; k < knightNum && d < dragonNum; k++) //���C���M�h
		{
			if (knight[k] >= dragon[d]) //�Y�M�h���� >= �s�Y���|�A�~�බ�Q��U
			{
				total += knight[k]; //���ɻݭn��O�P�M�h�������Ȫ�����
				d++; //��U���s�Y��
			}
		}

		if (d == dragonNum) //�Y�Ҧ��s�Y���Q��U
		{
			cout << total << endl; //��X�`��O
			continue;
		}

		cout << "Loowater is doomed!\n"; //�L�k��U�Ҧ��s�Y
	}

	system("pause");
}