#include<iostream>
#include<iomanip>
#include<vector>
#define two pair<int,int>
using namespace std;

int main()
{
	vector<two>showcase; //�i���d�Afirst == ���I�ߪ�����Bsecond == �Ҧ��H�����N�פ��M
	vector<vector<int>>dp; //dp[i][j] == ��Fi���I�ߡA�`����j���U���̤j�ߦn��
	//�`�H��(�ۤv + �B��)�B�C�H�I�����W���B���O�B�I�ߺ����ơB�`�w��
	for (int people, maxCost, tea, dessert, budget; cin >> people >> maxCost >> tea >> dessert, people;)
	{
		//�C�H�̦h�u���OmaxCost���q�A���ѩ��٭n�I�A�ȶO�H�ΨC�H���O�A�G��ڪ�b�I�ߤW���`�w�� == �H�� * �W����O / �A�ȶO - �H�� * ���O
		budget = (++people * maxCost) / float(1.1) - people * tea; //���ɪ�people�u�O�B�ͼơA�G�n���[�W�ۤv
		showcase.assign(dessert * 2, two()); //�C���I�̦߳h�u���2���A�G���I�߮i���d���C���I�ߥu��2��
		for (int i = 0; i < showcase.size(); i += 2) //�إ߮i���d
		{
			cin >> showcase[i].first; //��J���I�ߪ�����
			showcase[i + 1].first = showcase[i].first; //�C���I�ߤ@����2��
			for (int favor, j = 0; j < people; j++) //��J�C�H��Ӻ��I�ߪ��ߦn�סA�åB�N��[�`
			{
				cin >> favor;
				showcase[i + 1].second = showcase[i].second += favor;
			}
		}

		dp.assign(people * 2 + 1, vector<int>(budget + 1)); //dp[i][j] == ��Fi���I�ߡA�`����j��
		for (int i = 0; i < showcase.size(); i++)
		{
			int price = showcase[i].first, favour = showcase[i].second; //��e�I�ߪ�����P�ߦn��
			for (int p = people * 2; p; p--) //�C�H�̦h�I2���I�ߡA�Gpeople * 2 == �̤j�I�߼ơF�I�]���D�@�ߥѫ᩹�e��
			{
				for (int b = budget; b >= price; b--) //�Y��e���w�� >= ���I�ߪ�����A�N���٥I�o�_
				{
					dp[p][b] = max(dp[p][b], dp[p - 1][b - price] + favour); //�ɥi��a��X��Fp���I�ߥB�w�⬰b���̤j�ߦn��
				}
			}
		}

		int maxFavour = 0; //�̤j�ߦn��
		for (int i = 0; i < dp.size(); maxFavour = max(maxFavour, dp[i++][budget])); //��X�b�w�⤺���̤j�ߦn��
		cout << setprecision(2) << fixed << double(maxFavour) / people << "\n"; //�ھڤ����p��ÿ�X�����ߦn��
	}

	system("pause");
}