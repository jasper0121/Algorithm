#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	vector<int>boy, girl; //�k�B�k
	for (int Case = 1, boyNum, girlNum; cin >> boyNum >> girlNum, boyNum;) //�k�k�Ӽ�
	{
		boy.assign(boyNum, int());
		girl.assign(girlNum, int());
		for (int i = 0; i < boyNum; cin >> boy[i++]); //��J�樭�����~��
		for (int i = 0; i < girlNum; cin >> girl[i++]); //��J�k�ͦ~��
		if (girlNum >= boyNum) //�Y�k�ͼƶq >= �樭��
		{
			cout << "Case " << Case++ << ": " << 0 << endl; //�C���樭�����w�����
			continue;
		}

		sort(boy.begin(), boy.end()); //�Ϥ��h���Ѥp��j�Ƨ�
		sort(girl.begin(), girl.end());
		cout << "Case " << Case++ << ": " << boyNum - girlNum<<" " << boy[0] << endl; //�A��X���X���樭���䤣���A�ÿ�J�䤤�~�ֳ̤p��
	}

	system("pause");
}