#include<iostream>
#include<vector>
#define INF 100000000
using namespace std;

int main()
{
	vector<vector<int>>graph[2]; //graph[0] == �~���H���a�ϡBgraph[1] == �ѤH���a��
	for (int street, weight; cin >> street, street; cout << "\n") //�D���ơA�v��(�D������)
	{
		int maxPos = 0; //������e�̤j���D���s��
		graph[0].assign(26, vector<int>(26, INF)); //�D���s���d��u��A ~ Z�A��l�v���]���L���j
		graph[1] = graph[0]; //��l�ѤH���a�ϩM�~���H�ۦP
		for (char age, connect, u, v; street--;)
		{
			cin >> age >> connect >> u >> v >> weight; //��J�~��(Y == �~���H�BM == �ѤH)�B�O�_���V�s�q(B == ���V)�B�_�I�P���I�B�D����(�v��)
			maxPos = max(maxPos, max(u, v) - 'A'); //��̤j���D���s��
			graph[age == 'M'][u - 'A'][v - 'A'] = weight; //�ئ~���H�P�ѤH����
			if (connect == 'B') //�Yconnect == 'B'�h�ӱ��D���ئ����V
			{
				graph[age == 'M'][v - 'A'][u - 'A'] = weight;
			}
		}

		for (int i = 0; i <= maxPos; i++) //�ۤv����ۤv�����|�����w��0
		{
			graph[0][i][i] = graph[1][i][i] = 0;
		}

		for (int mid = 0; mid <= maxPos; mid++) //�򬥨̼w�t��k�A�Ҧ�u��v���i����|���A�����u�̵u��
		{
			for (int u = 0; u <= maxPos; u++)
			{
				for (int v = 0; v <= maxPos; v++)
				{
					graph[0][u][v] = min(graph[0][u][v], graph[0][u][mid] + graph[0][mid][v]);
					graph[1][u][v] = min(graph[1][u][v], graph[1][u][mid] + graph[1][mid][v]);
				}
			}
		}

		char start[2]; //�~���H�P�ѤH���_�I
		cin >> start[0] >> start[1];
		int minDis = INF; //����X2�H�|�X���̵u�Z��
		for (int end = 0; end <= maxPos; end++)
		{
			minDis = min(minDis, graph[0][start[0] - 'A'][end] + graph[1][start[1] - 'A'][end]);
		}

		if (minDis == INF) //�Y�̵u�Z�������L���j�A�h�N��2�H�L�k�|�X
		{
			cout << "You will never meet.";
			continue;
		}

		cout << minDis; //�Ϥ��h�L�X2�H�|�X���̵u�Z��
		for (int end = 0; end <= maxPos; end++) //�L�X�̵u�Z�����|�X�a�I�A�Y���h�Ӧa�I���̵u�Z���ۦP�h���L�X
		{
			if (minDis == graph[0][start[0] - 'A'][end] + graph[1][start[1] - 'A'][end])
			{
				cout << " " << char(end + 'A');
			}
		}
	}

	system("pause");
}