#include<iostream>
#include<vector>
using namespace std;

int dp[27][27][352]; //dp[i][j][k]��u�ϥΫe i �Ӧr���A�զ����r���ӼƬ� j�A�`�M�� k ���r�ꪺ�Ҧ����p��(1�[��26���`�M��351)

int main()
{
	for (int i = 1; i <= 26; i++) //�u�ϥΫei�Ӧr���A�B�u�Τ@�Ӧr�����ܡA�����`�M��i�����p�ƥu��1��
	{
		dp[i][1][i] = 1;
	}

	for (int i = 1; i <= 26; i++) //�u�ϥΫei�Ӧr��
	{
		for (int j = 1; j <= i; j++) //�b�u�ϥΫei�Ӧr�������p�U�A�զ����r���ӼƳ̦h�N�Oi��
		{
			for (int k = 1; k <= (1 + i) * i / 2; k++) //�b�u�ϥΫei�Ӧr�������p�U�A�r���`�M�̦h��k = 1 + 2+ ... + i = (1 + i) * i / 2
			{
				dp[i][j][k] += dp[i - 1][j][k]; //��l���N�u�ϥΫei - 1�Ӧr���A���ϥΦP��j�Ӧr���ӼơA�B�[�`�]�ۦP�����p�[�W�h(�Y��i�Ӧr�����ϥ�)
				if (k >= i) //�Y�`�M >= ��i�Ӧr��
				{
					dp[i][j][k] += dp[i - 1][j - 1][k - i]; //�h�[�W�u�u�ϥΫei - 1�Ӧr���A�u��j - 1�Ӧr���զ��A���`�M�[�Wi�|����k�v����k��(�Y�ϥβ�i�Ӧr��)
				}
			}
		}
	}

	//�Y��J���b�d�򤺫h��X��0
	for (int n = 1, len, sum; cin >> len >> sum, len; cout << "Case " << n++ << ": " << (len <= 26 && sum <= 351 ? dp[26][len][sum] : 0) << "\n");
	system("pause");
}