#include<iostream>
#include<vector>
using namespace std;

int testCase, Case = 1, width, len, budget, maxArea = 0, minPrice = 0; //����B�e�B���B�w��B�̤j���n�B�̤p��O
vector<vector<int>>landPrice; //�s�C���g�a������
vector<int>rowSum; //��e����[�`

void max1D(const int& left, const int& right)
{
	int curPrice = 0, top = 0; //��e�g�a����B��e�x�Ϊ��W��
	for (int y = 0; y < width; y++) //y�i���U��
	{
		//�C���N��e�l�x�}���ȥ[�`�A�Y�ӭ� > �w��A�h��h��e�W�ɪ��ȨñN�W�ɤU��
		for (curPrice += rowSum[y]; curPrice > budget; curPrice -= rowSum[top++]);
		int curArea = (y - top + 1) * (right - left + 1); //��e���n == (�U�� - �W�� + 1) * (�k�� - ���� + 1)
		if (maxArea < curArea) //�Y����j���g�a
		{
			maxArea = curArea; //�h�N��]���ثe���̤j�g�a
			minPrice = curPrice; //�N��]���ثe���̤p��O
		}
		else if (maxArea == curArea) //�Y�g�a���n�ۦP
		{
			minPrice = min(minPrice, curPrice); //�h���P���n�U��O���p���@��
		}
	}
}

int main()
{
	for (cin >> testCase; testCase--; maxArea = 0, minPrice = 0)
	{
		cin >> width >> len >> budget; //��J�e�B���B�w��
		landPrice.assign(width, vector<int>(len)); //�ع�
		for (int y = 0; y < width; y++) //��J�x�}���C�@�檺��
		{
			for (int x = 0; x < len; cin >> landPrice[y][x++]);
		}

		for (int left = 0; left < len; left++) //�q���䪺��0��}�l
		{
			rowSum.assign(width, 0); //�C�@�����n��l�Ʀ�[�`���j�p
			for (int right = left; right < len; right++) //�C���V�k���L�@�M
			{
				for (int y = 0; y < width; y++) //�N��e�椺���ȥ[�`
				{
					rowSum[y] += landPrice[y][right];
				}

				max1D(left, right); //�C�����e���̤j�g�a���n�P�䤤���̤p��O
			}
		}

		cout << "Case #" << Case++ << ": " << maxArea << " " << minPrice << "\n"; //�L�X�Ҧ��̤j�g�a����O�̤p��
	}

	system("pause");
}