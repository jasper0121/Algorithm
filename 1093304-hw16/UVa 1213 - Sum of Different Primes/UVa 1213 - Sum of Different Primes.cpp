#include<iostream>
#include<vector>
using namespace std;

int main()
{
	vector<vector<int>>dp(1121, vector<int>(15)); //dp[i][j] == ��e���Ʀri��j�ӽ�ƲզX�Ӧ�����k��
	vector<int>prime; //�s1120�����Ҧ����
	vector<bool>visit(1121);
	prime.push_back(2); //2�O���
	for (int i = 3; i <= 1120; i += 2) //�q3�}�l�A�]���F0�M2�H�~�����Ƴ����O��ơA�G�C���[2
	{
		if (visit[i] == false) //�p�G��ei�N���Ʀr�٥��Q���X
		{
			prime.push_back(i); //�N��O���
			for (int k = i; (k += i) <= 1120; visit[k] = true); //�N����i�����ƥ��]��true�N���X�A�]���L�̥��w���O���
		}
	}

	dp[0][0] = 1; //0��0�ӽ�ƲզX�Ӧ�����k�Ƭ�1
	for (auto& p : prime) //��Ҧ������
	{
		for (int i = 1120; i >= p; i--) //i�i���O�I�]�e�q�A�Y�ѫe�����A�h�i��|���ƨ���P�˪����
		{
			for (int j = 14; j; j--) //�D�ؤW������14�ؽ�ƲզX
			{
				dp[i][j] += dp[i - p][j - 1]; //�۷��i�ȨC����h�@�ӽ�ơA�@��dp[i - p][j - 1] == dp[0][0]�A�N��i��j�ӽ�ƲզX�Ӧ�����k�� + 1
			}
		}
	}

	for (int n, k; cin >> n >> k, n; cout << dp[n][k] << "\n"); //��J�ؼмƦrn�Mk�A�Dn�Hk�ӽ�ƲզX�Ӧ�����k��
	system("pause");
}