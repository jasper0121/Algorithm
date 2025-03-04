#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int testCase, width, length, height; //����B���B�e�B��
vector<vector<vector<long long>>>cube; //�ߤ���
vector<vector<long long>>sum_yz; //��e���G�������[�`
vector<long long>sum_y; //��e����[�`

long long max1D()
{
	long long localMax = sum_y[0], globalMax = sum_y[0]; //�ϰ�M���쪺�̤j��
	for (int i = 1; i < sum_y.size(); i++)
	{
		localMax = max(localMax + sum_y[i], sum_y[i]); //��X��e�̤j���l�x�}�M
		globalMax = max(globalMax, localMax);
	}

	return globalMax; //�^�ǳ̤j���@���x�}�M
}

long long max2D()
{
	long long globalMax = LLONG_MIN; //�̤j���l�ߤ�x�}�M�A��l�]���L���p
	for (int z_left = 0; z_left < height; z_left++) //�q���䪺��0��}�l�A�C���V�k���L�@�M(�byz�������Az�����`��x)
	{
		sum_y.assign(width, 0); //�C�@�����n��l�Ʀ�[�`���j�p
		for (int z_right = z_left; z_right < height; z_right++) //�C���V�k���L�@�M
		{
			for (int y = 0; y < width; y++) //�N��e�椺���ȥ[�`
			{
				sum_y[y] += sum_yz[y][z_right];
			}

			globalMax = max(globalMax, max1D()); //�C������e���̤j���l�x�}�M
		}
	}

	return globalMax; //�^�ǳ̤j���G���x�}�M
}

int main()
{
	for (cin >> testCase; testCase--;)
	{
		cin >> length >> width >> height; //��J���e��
		cube.assign(height, vector<vector<long long>>(width, vector<long long>(length))); //�ع�
		for (int z = 0; z < cube.size(); z++) //��J�x�}���C�@�檺��
		{
			for (int y = 0; y < cube[z].size(); y++)
			{
				for (int x = 0; x < cube[z][y].size(); cin >> cube[z][y][x++]);
			}
		}

		long long globalMax = LLONG_MIN; //�̤j���l�ߤ�x�}�M�A��l�]���L���p
		for (int x_left = 0; x_left < length; x_left++) //�q���䪺��0��}�l�A�C���V�k���L�@�M
		{
			sum_yz.assign(width, vector<long long>(height)); //�C�@�����n��l�ƤG�������[�`���j�p
			for (int x_right = x_left; x_right < length; x_right++)
			{
				for (int y = 0; y < width; y++) //�N��e�G�����������ȥ[�`�A�Hy���e�B�Hz����
				{
					for (int z = 0; z < height; z++)
					{
						sum_yz[y][z] += cube[z][y][x_right];
					}
				}

				globalMax = max(globalMax, max2D()); //�C������e���̤j���l�G���x�}�M
			}
		}

		cout << globalMax << (testCase ? "\n\n" : "\n"); //�L�X�̤j���l�ߤ�x�}�M
	}

	system("pause");
}