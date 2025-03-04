#include<iostream>
#include<vector>
#define INF 100000000
using namespace std;

int main()
{
	vector<int>coin, dp; //���B�B�զ��ӭ��B���ּ̤ƶq(�P���B������)
	int testCase, price, coinNum; //����B����B���B�ƶq
	for (cin >> testCase; testCase--;)
	{
		int total = 0;
		cin >> price >> coinNum; //��J����P���B�ƶq
		coin.assign(coinNum, int()); //�ھڭ��B���ƶq�ӨM�wcoin���}�C�j�p
		for (int i = 0; i < coin.size(); i++) //��J�Ҧ����B
		{
			cin >> coin[i];
			total += (total < price ? coin[i] : 0); //�L�{���N���B�[�`����W�L���w����
		}

		dp.assign(total + 1, INF); //�]���D�حn�D�W�L(�]�t)price���̧C���B�զX�A�]���Ndp�j�p�]��total + 1�A�W�L�������N���p��
		dp[0] = 0; //�զ�0������k�Ƭ��������A�G��k�Ƭ�0
		for (auto& c : coin) //���Ҧ����B���w��
		{
			for (int i = total; i >= c; i--) //�]�����B���୫�ơA�G�ѫ᩹�e��
			{
				dp[i] = min(dp[i], dp[i - c] + 1); //�T�|��e�����B�[�J�����p�A�è��զ����Bi���ֵ̤w����
			}
		}

		//�D�بD���B�[�`��̱���(�j�󵥩�)price���ȻP���B�ƶq
		for (; dp[price] == INF; price++); //�G�qprice�}�l�A�@���զ��ӭȪ��w���Ƥ����L���A�N��Y���ҨD
		cout << price << " " << dp[price] << "\n"; //�L�X�̱���(�j�󵥩�)price���ȻP���B�ƶq
	}

	system("pause");
}