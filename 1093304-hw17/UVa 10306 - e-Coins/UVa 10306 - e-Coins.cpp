#include<iostream>
#include<vector>
#define two pair<int,int>
#define INF 100000000
using namespace std;

int main()
{
	vector<vector<int>>dp; //dp[i][j] == �n�զ��ǲλ��Ȭ�i�H��InfoTechnological�Ȭ�j�һݪ��̤�e_coin��
	vector<two>e_coin; //�@��e_coin�Q�����ǲλ��ȻPInfoTechnological����
	int testCase;
	cin >> testCase;
	for (int e_coinNum, e_modulus; testCase--;) //e_coin�������ƶq�Be-modulus�� ^ 2 == �ǲ� ^ 2 + InfoTechnological ^ 2
	{
		dp.assign(301, vector<int>(301, INF)); //e-modulus�W��300�A�N�������p�U�i��ǲ� == 300�BInfoTechnological == 0�A��2�̬ۤ�
		dp[0][0] = 0; //�ǲ� == 0�BInfoTechnological == 0���̤�e_coin�� == 0
		cin >> e_coinNum >> e_modulus; //��Je_coin�Be-modulus��
		e_coin.assign(e_coinNum, two()); //�ھ�e_coin�������ƫإ߰}�C�j�p
		for (int i = 0; i < e_coinNum; cin >> e_coin[i].first >> e_coin[i].second, i++); //��J�C��e_coin���ǲλPInfoTechnological
		for (auto& coin : e_coin) //���Ҧ���e_coin
		{
			for (int i = coin.first; i <= 300; i++)
			{
				for (int j = coin.second; j <= 300; j++)
				{
					//�T�|�̫�@��e_coin�[�J�����p�A�ìݬݥ[�J���_�� "�F��ǲά�i�BInfoTechnological��j" ���ƶq����e�̤p
					dp[i][j] = min(dp[i][j], dp[i - coin.first][j - coin.second] + 1);
				}
			}
		}

		int minCoinNum = INF; //�ҨD���γ̤֪�e-coin�ӹF�������e-modulus�ȡA�G�̤p�һ�e-coin��l�]���L��
		for (int i = 0; i <= 300; i++) //���Ҧ��i�઺�ǲλ��ȻPInfoTechnological
		{
			for (int j = 0; j <= 300; j++)
			{
				if (i * i + j * j == e_modulus * e_modulus) //�Y�ǲλ��ȻPInfoTechnological�ھڤ����ŦXe_modulus
				{
					minCoinNum = min(minCoinNum, dp[i][j]); //�h�b�Ҧ��ŦX���������զX���A��X�һݪ��̤�e-coin�ƶq
				}
			}
		}

		if (minCoinNum == INF) //�YminCoinNum�����L���A�N��ҨD��e_modulus�L�k��o
		{
			cout << "not possible\n";
			continue;
		}

		cout << minCoinNum << "\n"; //�Ϥ��h�L�X�̤֩һݪ�e_coin���ƶq
	}

	system("pause");
}