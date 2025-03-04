#include<iostream>
#include<vector>
#include<set>
using namespace std;

int nodeNum; //�I�Ӽ�
vector<vector<int>>graph, reGraph; //�ϻP�ϦV��
vector<int>power, dis; //�v���P�Z��
set<int>path; //�s��ڷ|�g�L���I

void dfs(int node) //���ɹ�ڤW�O�q���I���^�_�I
{
	path.insert(node); //�C���N���|�W�|�g�L���I�s�Jset��(�Y�_�I�β��I�䤤�@�I���bset�̡A�N��_�I��������I)
	for (int x = 0; x < reGraph[node].size(); x++)
	{
		if (path.count(reGraph[node][x]) == 0) //�Y�S�g�L�A�h�s�Jset��
		{
			dfs(reGraph[node][x]);
		}
	}
}

void Bellman_Ford() //���ɳ��O�Φ��t��k��Z���_�I���̵u���|�έt���A���D�����ۤϡA�ݭn��̤j�Z���Υ���
{
	dis[1] = 100; //��l��q�w�]��100
	for (int i = 0; i < nodeNum - 1; i++) //Bellman_Ford�����I�A�`�@�]nodeNum - 1��(���F�_�l�I�@�}�l�N�]��0)�A�C������Ϩ䤤�@�I�T�w���̵u���|
	{
		for (int y = 1; y < graph.size(); y++)
		{
			for (int x = 0; x < graph[y].size(); x++)
			{
				//�Y��e�I���ȫD0�A�B����s���쪺�I < ��e���I + �v���᪺��
				if (dis[y] && dis[graph[y][x]] < dis[y] + power[graph[y][x]])
				{
					dis[graph[y][x]] = dis[y] + power[graph[y][x]]; //�h�N�ӭȵ�����s���쪺�I
				}
			}
		}
	}

	for (int y = 1; y < graph.size(); y++) //���ɩҦ��I���ȬҬ��̤j���|(�M�ӭY�������h�L�k�T�w�̤j���|���ȡA���i�Ǧ��P�_�O�_������)
	{
		for (int x = 0; x < graph[y].size(); x++)
		{
			//�Y��e�I���ȫD0 && ���I�b��w�����|�W && ����s���쪺�I�����ٯ�A��j
			if (dis[y] && path.count(graph[y][x]) && dis[graph[y][x]] < dis[y] + power[graph[y][x]])
			{
				cout << "winnable\n"; //�N��i�H������I
				return;
			}
		}
	}

	cout << (dis[nodeNum] ? "winnable\n" : "hopeless\n"); //�Y����즹�A�N��L�����C�Y���I���ȫD0�h�N��i�H������I
}

int main()
{
	for (; cin >> nodeNum, nodeNum != -1; path.clear()) //�C����J�I�ӼơB�Y��J-1�h�����F�C���M��set
	{
		graph.assign(nodeNum + 1, vector<int>()); //0����
		reGraph.assign(nodeNum + 1, vector<int>()); //�ؤϦV�ϡA�ت��O�T�{�_�I�O�_���������I�A�åB�P����w���|(�N�|�g�L���I�s�_��)�A0����
		power.assign(nodeNum + 1, int()); //�C�@�I����q���ӡA�i�ݦ�������I���D��(�v��)�A0����
		dis.assign(nodeNum + 1, int()); //�C�@�I�Z���_�I���̵u���|�A0����
		for (int linkNum, x, y = 1; y <= nodeNum; y++) //�ع�
		{
			for (cin >> power[y] >> linkNum; linkNum--;)
			{
				cin >> x;
				graph[y].push_back(x);
				reGraph[x].push_back(y);
			}
		}

		dfs(nodeNum); //���]dfs��w����n�]�����|
		Bellman_Ford();
	}

	system("pause");
}