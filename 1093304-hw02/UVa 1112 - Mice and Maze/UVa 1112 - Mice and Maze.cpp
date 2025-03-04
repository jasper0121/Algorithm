#include<iostream>
#include<queue>
using namespace std;
using two = pair<size_t, size_t>; //�Npair�Htwo�N�١A�̧Ǧs�v��(�D������)�ιD�����t�@���I

vector<vector<two>>graph; //graph�s�Z�_�I���̤p�Z��

int dijkstra(const int& start, const int& limitTime)
{
	int total = 0; //�ŦX�D�ةҨD���I�Ӽ�
	vector<size_t>dis(graph.size(), -1); //�Ҧ��I�M�_�I���Z���A�w�]���L���j
	priority_queue<two, vector<two>, greater<two>>temp;
	temp.push({ dis[start] = 0,start }); //�_�I�Z����0(�_�I���w���ҨD���I���@)
	for (int cur_dis, cur_y; temp.size();) //�Ypriority_queue��size����0
	{
		cur_dis = temp.top().first; //���X��e���Z��
		cur_y = temp.top().second; //���X��e�Ҧb����m
		temp.pop(); //���X����N�Ӥ����qpriority_queue���R��
		for (int next_dis, next_pos, x = 0; x < graph[cur_y].size(); x++) //���X�Ҧ��M��e�s�����I
		{
			next_dis = graph[cur_y][x].first; //�P�ؼЪ��Z��
			next_pos = graph[cur_y][x].second; //�ؼ��I��m
			if (dis[next_pos] > cur_dis + next_dis) //�Y�U�Ӯy�Ъ��Z�� > ��e�Z�� + �v��(�D������)
			{
				temp.push({ dis[next_pos] = cur_dis + next_dis,next_pos }); //�h�N�U�Ӯy�Ъ��Z�� = ��e�Z�� + �v��(�D������)�A�é�Jpriority_queue��
			}
		}
	}

	for (int i = 1; i < dis.size(); total += dis[i++] <= limitTime); //�̫�Ʀ��X���I�M�_�I���Z�� <= �ɭ�
	return total;
}

int main()
{
	int testCase, nodeNum, end, limitTime, edgeNum; //����B�I�ӼơB���I�B�ɶ�����B�D���`��
	for (cin >> testCase; testCase--;)
	{
		cin >> nodeNum >> end >> limitTime >> edgeNum;
		graph.assign(nodeNum + 1, vector<two>()); //�D�رq1�}�l�A�ҥH0����

		for (int x, y, time; edgeNum--;) //�ѩ��D�حn�D�Ҧ��I�Z���I���̤p���|�O�_�b�ɭ����A�i�N���I�����_�I�ϦV�عϡA�ϱo�P�@�������|����2���H�W
		{
			cin >> y >> x >> time;
			graph[x].push_back({ time ,y });
		}

		cout << dijkstra(end, limitTime) << endl;
		if (testCase)
		{
			cout << endl;
		}
	}

	system("pause");
}