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
		return 1000000; //�h�^���D�ةҭq���̤j��
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
			minDis = min(minDis, max(abs(point[R].first - point[L].first), abs(point[R].second - point[L].second)));
		}
	}

	return minDis; //�^�ǳ̵u�Z��
}

int main()
{
	for (int nodeNum; cin >> nodeNum;)
	{
		point.assign(nodeNum, two());
		for (int i = 0; i < nodeNum; i++) //��J�U���I�y��(x�y�� == first�By�y�� == second)
		{
			cin >> point[i].first >> point[i].second;
		}

		sort(point.begin(), point.end()); //��x�y�ХѤp��j�Ƨ�
		cout << divide_and_conquer(0, nodeNum - 1) << endl; //��̵u�Z���A��l�a�J�Ȭ��̥��M�̥k����

	}

	system("pause");
}

/*
double ds(two& a, two& b)
{
	return max(abs(a.first - b.first), abs(a.second - b.second));
}
double Combine(int& a, int& b, int& mid, double& l, double& r)
{
	double d = min(l, r);
	double line = (V[mid].first + V[mid + 1].first) / 2;
	double Min = d;
	for (int i = mid + 1; i <= b && V[i].first < line + d; ++i)
		for (int j = mid; j >= a && V[j].first > line - d; --j)
			Min = min(Min, ds(V[i], V[j]));
	return Min;
}
double Divide(int a, int b)
{
	if (a >= b) return 1000000;
	int mid = (a + b) / 2;
	double l = Divide(a, mid);
	double r = Divide(mid + 1, b);
	return Combine(a, b, mid, l, r);
}
*/