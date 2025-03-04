#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#define two pair<int, int> //�Npair<int, int>�Htwo�N��
using namespace std;

struct point //�Ω�֬d���A�C���I����lparent���ۤv�Arank�̰��̱N����root
{
	int parent, rank;

	point(const int& p, const int& r) //constructor�A�bvector��push_back���|�ϥΨ�A�Ψӳ]�wdata member
	{
		parent = p;
		rank = r;
	}
};

struct edge //�C�@���䦳�_�I�B���I�M���
{
	int start, end;
	double dis;

	bool operator<(const edge& right) //�ϥ�sort�ɡA������Ѥp��j�Ƨ�
	{
		return dis < right.dis;
	}

	edge(const int& s, const int& e, const double& d) //constructor�A�bvector��push_back���|�ϥΨ�A�Ψӳ]�wdata member
	{
		start = s;
		end = e;
		dis = d;
	}
};

int testCase, Case = 1, cityNum, limitDis; //����B��ecase�B�����`�ơB�����Z��(�W�L���Z���h���K���A�_�h������)
vector<two>city; //�s�Ҧ��������y�СA�åB�Nindex�@���������s��
vector<point>node; //�s�Ҧ������A�C�ӫ��������@���I
vector<edge>graph; //�s�Ҧ��i�઺��

int find_root(int start) //�Y��e���I��parent != �ۤv�A�h�qparent�~�򩹫e��A�Y���h�^�Ǹ��I
{
	return node[start].parent != start ? find_root(node[start].parent) : start;
}

bool union_node(const int& s, const int& e)
{
	int startRoot = find_root(s), endRoot = find_root(e); //2�I�U�ۧ�root
	if (startRoot != endRoot) //�Y2�I��root���ۦP�A�h�N��Y�s����2�I���|�Φ����A�i�N2��root�s���_�ӧΦ��@�Ӷ��X
	{
		if (node[startRoot].rank == node[endRoot].rank) //�Y2��root��rank�ۦP
		{
			node[endRoot].parent = startRoot; //�h�]�wendRoot��parent��startRoot
			node[startRoot].rank++; //�]��endRoot��parent�OstartRoot�A�ҥHstartRoot������ + 1
		}
		else //�YstartRoot�����Ÿ��j�A�h�]�wendRoot��parent��startRoot�F�Ϥ��h�NstartRoot��parent�]��endRoot
		{
			(node[startRoot].rank > node[endRoot].rank) ? (node[endRoot].parent = startRoot) : (node[startRoot].parent = endRoot);
		}

		return true; //2�I�w�s����u�A�^��true
	}

	return false; //2�I����s����u�A�^��false
}

void kruskcal()
{
	int stateNum = 1; //�{���ƶq�A��l��1
	double roadLen = 0, railroadLen = 0; //�����`���B�K���`��
	sort(graph.begin(), graph.end()); //�N�Ҧ�����Ѥp��j�Ƨ�
	for (int i = 0; i < graph.size(); i++) //���Ҧ��i�઺��
	{
		if (union_node(graph[i].start, graph[i].end)) //�ˬd��e��2�I�O�_��u���s����u
		{
			//�Y��e����� <= �����Z���A�h�������@�����F�_�h��@�K��(2�{�H�K���s���A�G�{�� + 1)
			(graph[i].dis <= limitDis ? roadLen : (stateNum++, railroadLen)) += graph[i].dis;
		}
	}

	//��X�{�ơB���������K����(4�ˤ��J)
	cout << "Case #" << Case++ << ": " << stateNum << " " << int(roadLen + 0.5) << " " << int(railroadLen + 0.5) << endl;
}

int main()
{
	for (cin >> testCase; testCase--; node.clear(), graph.clear()) //�C���n�Nnode�Mgraph���m
	{
		cin >> cityNum >> limitDis; //��J�����`�ơA�����Z��
		city.assign(cityNum, two());
		for (int i = 0; i < cityNum; i++) //��J�y��
		{
			cin >> city[i].first >> city[i].second;
		}

		for (int i = 0; i < cityNum; node.push_back(point(i++, 0))); //�]�w�C���I��parent�Mrank(�C���I��parent���w�]���ۤv�Arank��l��0)
		for (int start = 0; start < city.size(); start++) //�N�Ҧ��I���۳s��(���ɪ��s���i�ݦ���u�A�٥��u���s����)
		{
			for (int cur = start + 1; cur < city.size(); cur++) //�s�J�Ҧ��i�઺��(�_�I�B���I�M����A2�I�b�y�ФW���s�u���ץH����w�z��X)
			{
				graph.push_back(edge(start, cur, sqrt(pow(city[cur].first - city[start].first, 2) + pow(city[cur].second - city[start].second, 2))));
			}
		}

		kruskcal();
	}

	system("pause");
}