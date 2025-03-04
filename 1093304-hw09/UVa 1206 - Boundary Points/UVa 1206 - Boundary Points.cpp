#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include<cmath>
using namespace std;

struct node //�@���I���Gx�My�y�СB�M�̥��U�I���Z���Bsort�Ϊ�operator(�N�Ҧ��I�Hy�Ƨ�)
{
	double x, y, dis;
	bool operator<(const node& right)
	{
		return y == right.y ? x < right.x : y < right.y; //�ɥi��a����y���p�̡A�Yy�ۦP�A��x���p��
	}
};

vector<node>point, stack; //�s�Ҧ��I�y�СB�s�Y�]�I

double cross_product(const node& p0, const node& p1, const node& p2) //�~�n�����A(p1 - p0) �� (p2 - p0)
{
	return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

bool polar_angle(const node& left, const node& right) //�����Ƨ�
{
	double cp = cross_product(point[0], left, right); //�Hpoint[0]�����I���@���~�n
	return cp == 0 ? left.dis < right.dis : cp > 0; //�Y�~�n == 0�A�h����k�䪺�Z���O�_����j�F�Ϥ��Y�~�n�����A�N��f�ɰw����A�h�^��true
}

void GrahamScan()
{
	sort(point.begin(), point.end()); //���N�Ҧ��I�Hy�Ѥp��j�Ƨ�
	for (int i = 1; i < point.size(); i++) //�q�Ƨǫ᪺��1���I�}�l�A�C���I����X�P���I(point[0])���Z��
	{
		point[i].dis = sqrt(pow(point[i].x - point[0].x, 2) + pow(point[i].y - point[0].y, 2));
	}

	sort(point.begin() + 1, point.end(), polar_angle); //�q��1���I�}�l���@�������Ƨ�
	for (int i = 0; i < point.size(); i++) //���Ҧ����I
	{
		//�Ystack���s���I >= 2(�]���[�W��e���I�~��h�P�_�����ͶլO���ΰf�ɰw)�A�B�~�n�����G <=0(�D�f�ɰw)
		while (stack.size() >= 2 && cross_product(stack[stack.size() - 2], stack[stack.size() - 1], point[i]) <= 0)
		{
			stack.pop_back(); //�h��estack����top�R��
		}

		stack.push_back(point[i]); //�C���N��e���I�[�Jstack
	}

	stack.push_back(point[0]); //�̫�|¶�^���I
}

int main()
{
	char c; //�Ψӿ�J�h��r��
	double x, y; //��Jx�My�y��
	for (string input; getline(cin, input); cout << endl, point.clear(), stack.clear()) //��J����B�C�������Npoint�Mstack������ƲM��
	{
		for (stringstream ss(input); ss >> c >> x >> c >> y >> c; point.push_back({ x,y })); //�C�����X�@�Ӯy�Ъ�x�My�æs�Jpoint(c�Ψӿ�J�p�A���M�r��)
		GrahamScan();
		for (int i = 0; i < stack.size(); i++) //stack�����Ҧ��I�Y���Y�]�A�L�X�Ҧ�stack�����I
		{
			cout << (i ? " " : "") << "(" << stack[i].x << "," << stack[i].y << ")";
		}
	}

	system("pause");
}