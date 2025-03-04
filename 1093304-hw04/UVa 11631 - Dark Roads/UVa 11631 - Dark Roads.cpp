#include<iostream>
#include<algorithm>
#include<vector>
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
	int start, end, dis;

	bool operator<(const edge& right) //�ϥ�sort�ɡA������Ѥp��j�Ƨ�
	{
		return dis < right.dis;
	}
};

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

void kruskcal(const int& totalDis)
{
	int minDis = 0; //�Ҧ��������s�_�өһݪ��̤p���
	sort(graph.begin(), graph.end()); //�N�Ҧ�����Ѥp��j�Ƨ�
	for (int i = 0; i < graph.size(); i++)
	{
		if (union_node(graph[i].start, graph[i].end)) //�ˬd��e��2�I�O�_��u���s����u
		{
			minDis += graph[i].dis; //�N�w�s����u���u�q���[�`
		}
	}

	cout << totalDis - minDis << endl; //�D�بD�̦h��٦h������A�Y�`�u�q - �̤p�һ����
}

int main()
{
	for (int cityNum, roadNum; cin >> cityNum >> roadNum, cityNum; node.clear()) //�I�ӼơB���`�ơF�C����J����䤤�@�ӿ�J0�F�C���Nnode���m
	{
		int totalDis = 0; //�`����A�Y�Ҧ����O���}(�]�i�ݦ��Ҧ��v�����`�M)
		for (int i = 0; i < cityNum; node.push_back(point(i++, 0))); //�]�w�C���I��parent�Mrank(�C���I��parent���w�]���ۤv�Arank��l��0)
		graph.assign(roadNum, edge()); //�ع�
		for (int i = 0; i < roadNum; i++) //��J�D�ص����Ҧ��i�઺��(���ɪ��s���i�ݦ���u�A�٥��u���s����)
		{
			cin >> graph[i].start >> graph[i].end >> graph[i].dis; //�_�I�B���I�B���
			totalDis += graph[i].dis; //����[�`
		}

		kruskcal(totalDis);
	}

	system("pause");
}