#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<vector>
#define two pair<double,double>
using namespace std;

vector<two>point; //�s�Ҧ��I�y��

double divide_and_conquer(int left, int right)
{
	if (left == right) //�Y�����k�b��ɨ���F�̥��γ̥k
	{
		return 10000; //�h�^���D�ةҭq���̤j��
	}

	int midnode = (left + right) / 2; //��e�������I(���I�|�b���u������)
	double midline = (point[midnode].first + point[midnode + 1].first) / 2; //�w�q���u���G��e�����I�P�U�ӥk�I���������u(��Ȭ��Ӥ����u��x�y��)
	//���ɥi��q���u�����k�b��̤px�}�l��A���k�b��U�ۧ�X�ӥb�䤺2�I�����̤p�Z���A����q�N��e2�b����o���̤p�Z�������̤p��
	double range = min(divide_and_conquer(midnode + 1, right), divide_and_conquer(left, midnode)); //�åB�N�ӳ̤p�ȧ@����e���u�V���k�������d��
	double minDis = range; //�̤p�Z���s�b��d�򤺡A�G���N�̤p�Z�� == �d��

	for (int L = midnode; L >= left && midline - range < point[L].first; L--) //�Y���b�䪺��e�Ix�y�Цb�d��
	{
		for (int R = midnode + 1; R < point.size() && point[R].first < midline + range; R++) //�Y�k�b�䪺��ex�y�Цb�d��
		{
			//��X2�I���Z����A�Y���e�̵u�Z���٤p�A�h�̤p�Z����]���ӭ�
			minDis = min(minDis, sqrt(pow(point[R].first - point[L].first, 2) + pow(point[R].second - point[L].second, 2)));
		}
	}

	return minDis; //�^�ǳ̵u�Z��
}

int main()
{
	for (int nodeNum; cin >> nodeNum, nodeNum;) //�I�Ӽ�
	{
		point.assign(nodeNum, two()); //�ھ��I�Ӽưt�m�Ŷ�
		for (int i = 0; i < nodeNum; i++) //��J�U���I�y��(x�y�� == first�By�y�� == second)
		{
			cin >> point[i].first >> point[i].second;
		}

		sort(point.begin(), point.end()); //��x�y�ХѤp��j�Ƨ�
		double minDis = divide_and_conquer(0, nodeNum - 1); //��̵u�Z���A��l�a�J�Ȭ��̥��M�̥k����

		if (minDis < 10000) //�Y�̵u�Z�� < 10000
		{
			cout << setprecision(4) << fixed << minDis << "\n"; //�h�|�ˤ��J���X��p���I��4��
		}
		else
		{
			cout << "INFINITY\n";
		}
	}

	system("pause");
}