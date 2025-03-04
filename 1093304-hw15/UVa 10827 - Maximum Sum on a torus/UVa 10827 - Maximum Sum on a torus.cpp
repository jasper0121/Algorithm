#include<iostream>
#include<vector>
#define INF 100000000
using namespace std;

vector<vector<int>>graph; //�x�}
vector<int>rowSum; //��e����[�`

int max1D()
{
	int localMax, globalMax, localMin, globalMin, total; //�ϰ�M���쪺�̤j�γ̤p�ȡA��e�l�x�}�����`�M
	globalMax = localMax = globalMin = localMin = total = rowSum[0]; //��l���]����[�`�����Ĥ@�Ӽ�
	for (int i = 1; i < rowSum.size(); i++)
	{
		total += rowSum[i]; //�N��e�l�x�}���ȥ[�`
		//��X��e�̤j���l�x�}�M
		localMax = max(localMax + rowSum[i], rowSum[i]);
		globalMax = max(globalMax, localMax);
		//�ѩ��D�ت��x�}�W�U���q�A�G�A��X��e�̤p���l�x�}�M�A�ҨD�Y�i�����u��ӯx�} - �̤p���l�x�}�v
		localMin = min(localMin + rowSum[i], rowSum[i]);
		globalMin = min(globalMin, localMin);
	}

	return max(globalMax, total - globalMin); //�S�W�U�۳q���x�}�M���W�U�۳q���x�}�������j���@��^��
}

int main()
{
	int testCase;
	cin >> testCase;
	for (int N; testCase--;)
	{
		cin >> N; //�x�}���
		graph.assign(N, vector<int>(N)); //�إ�N * N���x�}
		for (int y = 0; y < graph.size(); y++) //��J�x�}���C�@�檺��
		{
			for (int x = 0; x < graph[y].size(); cin >> graph[y][x++]);
		}

		int globalMax = -INF; //�̤j���l�x�}�M�A��l�]���L���p(�]���x�}�����t��)
		for (int left = 0, right = 0; left < graph.size(); right = ++left) //�q���䪺��0��}�l�A�C���V�k���L�@�M
		{
			rowSum.assign(N, 0); //�C�@�����n��l�Ʀ�[�`���j�p
			//�ѩ󥪥k���q�A�ҥH�Y����̥k����٥���N���A�h�q�̥��~��p��
			for (int times = N; times--; (++right) %= N) //ex: �YN == 5�A�h�]��(0 �� 4)��B(1 �� 4, 0)�B(2 �� 4, 0 �� 1)�B(3 �� 4, 0 �� 2)�B(4, 0 �� 3)�A�H������
			{
				for (int y = 0; y < graph.size(); y++) //�N��e�椺���ȥ[�`
				{
					rowSum[y] += graph[y][right];
				}

				globalMax = max(globalMax, max1D()); //�C������e���̤j���l�x�}�M
			}
		}

		cout << globalMax << "\n"; //�L�X�̤j���l�x�}�M
	}

	system("pause");
}