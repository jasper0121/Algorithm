#include<iostream>
#include<vector>
#define INF 100000000
using namespace std;

int main()
{
	vector<int>cut; //�����I
	vector<vector<int>>dp; //dp[i][j]�A���Y�q�����Ii ~ j�����̤p��O
	for (int cutNum, length; cin >> length, length;) //��J���Y�`����
	{
		cin >> cutNum; //�����I���ƶq
		cut.assign(cutNum + 2, int()); //�Y���]�������I
		for (int i = 1; i <= cutNum; cin >> cut[i++]); //��J�����I(�̫e�ݪ������I���w��0)
		cut.back() = length; //�̧��ݪ������I������ڤ��Y������
		dp.assign(cut.size(), vector<int>(cut.size()));
		//�Ypart == 1�A�N��u���@�q�����S�������I�����Y�A�o�ɪ���O�O0�A�G�q2�}�l�_��Ccut.size() - 1 == ���Y�q��
		for (int part = 2; part <= cut.size() - 1; part++)
		{
			for (int begin = 0, end = part; end < cut.size(); begin++, end++) //�C���_�I�M���I���T�w�V�ᨫ�@�q
			{
				dp[begin][end] = INF; //��l�N�q�_�I����I�Ҫ�O���ɶ��]���L��
				for (int cutPos = begin + 1; cutPos < end; cutPos++) //��l�����I����m == �_�I���U�@�Ӥ����I
				{
					//�Y�_�I ~ ��e�����I + ��e�����I ~ ���I + �_�I����I�����Y���� < ��e���Y���`��O�A�h��s�Ӭq���Y���̤p��O
					dp[begin][end] = min(dp[begin][end], dp[begin][cutPos] + dp[cutPos][end] + (cut[end] - cut[begin]));
				}
			}
		}

		cout << "The minimum cutting is " << dp[0].back() << ".\n"; //�D�بD��q���Y���̤p��O
	}

	system("pause");
}