#include<iostream>
using namespace std;

long long dp[66][67][2]; //dp[i][j][k]�A�`�@i���d�l�Bj�ӳB��w�����A�B�̤W�h���S����(0 == �S��A1 == ����)

int main()
{
	dp[1][0][0] = dp[1][1][1] = 1; //�b�u���@���d�l�����p�U�A0�Ӧw�����w�S��A1�Ӧw���h���w����
	for (int i = 2; i <= 65; i++)
	{
		//�Y�n�b�W�h�[1�h�S�ꪺ�d�l�A�B0���d�l�w������k�� == i - 1���d�l���A�S���@�Ӧw���B�̤W���S�� + 1�Ӧw���B�̤W�����d�l����
		dp[i][0][0] = dp[i - 1][0][0] + dp[i - 1][1][1];
		for (int j = 1; j <= i; j++)
		{
			//�Y�n�b�W�h�[1�h�S�ꪺ�d�l�A�B�ϱo��j���d�l�w���A�h��k�� == �@i - 1�h���d�l���Aj�Ӧw���B�̤W�h�S��A�[�Wj + 1�Ӧw�����̤W�h����
			dp[i][j][0] = dp[i - 1][j][0] + dp[i - 1][j + 1][1]; //�������p�Gdp[65 - 1][65 + 1][1]�A�ҥHdp����2��}�C�n�}67��
			//�Y�n�b�W�h�[1�h���ꪺ�d�l�A�B�ϱo��j���d�l�w���A�h��k�� == �@i - 1�h���d�l�B��j - 1���d�l�w��
			dp[i][j][1] = dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1];
		}
	}

	for (int num, safe; cin >> num >> safe, num >= 0; cout << dp[num][safe][0] + dp[num][safe][1] << "\n");
	system("pause");
}