#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	vector<int>bag, bagNum; //�]�]�����B�C�������ƶq(�q1�}�l)
	for (int total; cin >> total, total; cout << endl) //�`�]�]��
	{
		int bagMax = 0; //�s���������ƶq�̦h�A�]�N��۳̤p���
		bag.assign(total, int());
		bagNum.assign(total + 1, int()); //0����
		for (int i = 0; i < total; i++)
		{
			cin >> bag[i]; //��J����
			bagNum[bag[i]]++; //�Ӻ������ƶq + 1
			bagMax = max(bagMax, bagNum[bag[i]]); //����������ƶq�̦h
		}

		sort(bag.begin(), bag.end()); //�����ƥѤp��j�Ƨ�
		cout << bagMax << endl;
		for (int cur = 0; cur < bagMax; cout << endl, cur++) //�bbagMax���d�򤺪��C�ӭȳ��@���_�I
		{
			for (int next = cur; next < bag.size(); next += bagMax) //�C���HbagMax���Z�����ۿ�X
			{
				cout << (cur == next ? "" : " ") << bag[next];
			}
		}
	}

	system("pause");
}