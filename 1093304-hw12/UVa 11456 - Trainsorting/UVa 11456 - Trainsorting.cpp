#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int testCase, cart; //����B���[
	vector<int>train, LIS; //�C���B�̪��Y�滼�W�l�ǦC
	for (cin >> testCase; testCase--; LIS.clear())
	{
		if (cin >> cart, cart) //��J���[��
		{
			train.assign(cart * 2, int()); //�]�D�ػ��C�����[�i��b���Y�Ψ����A�G�N��e���C�������A�ˤ@���å[��C���e���A�Gtrain���j�p * 2
			for (int i = 0; i < cart; i++)
			{
				cin >> train[cart + i]; //��J���[
				train[cart - i - 1] = train[i + cart]; //�N��e���C�������A�ˤ@���å[��C���e��(ex�G�Y�쥻�O123�A�h�|�令321123)
			}

			LIS.push_back(train[0]); //���N���Y�[�JLIS
			for (int i = 1; i < train.size(); i++) //LIS�t��k�A�q�ƦC��index == 1����m�}�l
			{
				if (train[i] > LIS.back()) //�Y�ƦC����e���Ʀr > LIS���̫᭱���Ʀr
				{
					LIS.push_back(train[i]); //�h�����N��e���Ʀr�[�JLIS��
					continue;
				}

				*lower_bound(LIS.begin(), LIS.end(), train[i]) = train[i]; //�Ϥ��A�h����XLIS���A�Ҧ��j��train[i]�������̤p�̡A�ñN���train[i]���N
			}
		}

		cout << LIS.size() << "\n"; //�D�بD�̪��Y�滼�W�l�ǦC������
	}

	system("pause");
}