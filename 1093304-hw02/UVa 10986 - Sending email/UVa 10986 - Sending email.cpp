#include<iostream>
#include<queue>
using namespace std;
using two = pair<size_t, size_t>; //�Npair�Htwo�N�١A�̧Ǧs�v��(���|��)�Ψ�ؼк��I

int testCase, nodeNum, line, start, target; //����B�I�ӼơB�u���`�ơB�_�I�B���I
vector<vector<two>>graph; //graph�s�Z�_�I���̤p�Z��

void dijkstra(int& t)
{
	vector<size_t>dis(nodeNum, -1); //�Ҧ��I�M�_�I���Z���A�w�]���L���j
	priority_queue<two, vector<two>, greater<two>>temp;
	temp.push({ dis[start] = 0,start }); //��l�_�I�Z����0�A��Jpriority_queue��
	for (int cur_dis, cur_y; temp.size();) //�Ypriority_queue��size����0
	{
		cur_dis = temp.top().first; //���X��e���Z��
		cur_y = temp.top().second; //���X��e�Ҧb����m
		temp.pop(); //���X����N�Ӥ����qpriority_queue���R��
		for (int next_dis, next_pos, x = 0; x < graph[cur_y].size(); x++)
		{
			next_dis = graph[cur_y][x].first; //�P�ؼЪ��Z��
			next_pos = graph[cur_y][x].second; //�ؼ��I��m
			if (dis[next_pos] > cur_dis + next_dis) //�Y�U�Ӯy�Ъ��Z�� > ��e�Z�� + �v��(�D������)
			{
				temp.push({ dis[next_pos] = cur_dis + next_dis,next_pos }); //�h�N�U�Ӯy�Ъ��Z�� = ��e�Z�� + �v��(�D������)�A�é�Jpriority_queue��
			}
		}
	}

	cout << "Case #" << t++ << ": ";
	if (dis[target] == -1)
	{
		cout << "unreachable" << endl;
	}
	else
	{
		cout<< dis[target] << endl;
	}
}


int main()
{
	cin >> testCase;
	for (int t = 1; t <= testCase;)
	{
		cin >> nodeNum >> line >> start >> target;
		graph.assign(nodeNum, vector<two>());
		for (int x, y, latency; line--;) //�عϡA����i�ݦ��O���|��
		{
			cin >> y >> x >> latency;
			graph[y].push_back({ latency ,x });
			graph[x].push_back({ latency ,y });
		}

		dijkstra(t);
	}

	system("pause");
}