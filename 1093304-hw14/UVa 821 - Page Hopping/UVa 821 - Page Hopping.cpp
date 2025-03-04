#include<iostream>
#include <iomanip>
#include<vector>
#include<unordered_set>
#define INF 100000000
using namespace std;

int main()
{
	vector<vector<int>>graph;
	unordered_set<int>num; //�s���ǼƷ|�P��L�Ƴs���A�p���N���ݭn�M�����graph�A�u�ݭn�M���u�����P��L�I�s�����I
	for (int start, end, Case = 1; cin >> start >> end, start; num.clear()) //�_�I�B���I�A�C��num�n���m
	{
		graph.assign(101, vector<int>(101, INF)); //�Ʀr�d��1 ~ 100�A0���ΡA��l�v���]���L���j
		do
		{
			num.insert(start);
			num.insert(end);
			graph[start][end] = 1; //2�I�����v��(�i�ݦ��D����)���]��1
		} while (cin >> start >> end, start);

		for (auto& mid : num) //�M��num�����Ҧ���
		{
			for (auto& u : num)
			{
				for (auto& v : num) //�򬥨̼w�t��k�A�Ҧ�u��v���i����|���A�����u�̵u��
				{
					graph[u][v] = min(graph[u][v], graph[u][mid] + graph[mid][v]);
				}
			}
		}

		double sum = 0, way = num.size() * (num.size() - 1); //�Ҧ��I���|�M��L�I��̵u���|�A�ҥH��k�� == �I�Ӽ� * (�I�Ӽ� - 1)
		for (auto& u : num)
		{
			for (auto& v : num)
			{
				if (u != v) //�Y�_�I != ���I
				{
					sum += graph[u][v]; //�h�N�̵u���|�[�`
				}
			}
		}

		//�ҨD == �̵u���|���`�M / ��k��
		cout << "Case " << Case++ << ": average length between pages = " << fixed << setprecision(3) << sum / way << " clicks\n";
	}

	system("pause");
}