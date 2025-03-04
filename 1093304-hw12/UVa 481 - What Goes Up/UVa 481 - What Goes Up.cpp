#include<iostream>
#include<vector>
using namespace std;

struct two //癸–计埃セ计ぇ临穦Τ赣计﹃い
{
	int num, len;
};

int main()
{
	vector<two>seq; //计
	vector<int>LIS; //程腨患糤
	for (int num; cin >> num; seq.push_back({ num,1 })); //块计﹍┮Τ计常箇砞1(┮Τ计秨﹍常Θ﹃秨繷)
	LIS.push_back(seq[0].num); //秨﹍盢计い程秨繷计程腨患糤
	for (int i = 1; i < seq.size(); i++) //LIS簍衡猭眖计いindex == 1竚秨﹍
	{
		if (seq[i].num > LIS.back()) //璝计い讽玡计 > LISい程计
		{
			LIS.push_back(seq[i].num); //玥钡盢讽玡计LISい
			seq[i].len = LIS.size(); //赣计LISい == LIS
			continue;
		}

		auto it = lower_bound(LIS.begin(), LIS.end(), seq[i].num); //はぇ玥тLISい┮Τseq[i].numぇい程
		*it = seq[i].num; //ぇ盢﹚竚计ノseq[i].numㄏ眔seq[i].numぇ钡计
		seq[i].len = (it - LIS.begin() + 1); //讽玡计 == ┮index + 1
	}

	//程LISsize()┮―妓计穦Τlen计パ玡ゲ﹚琌パ珿眖seq程秨﹍┕玡т
	for (int i = seq.size() - 1, maxLen = LIS.size(); i >= 0; i--) //﹍maxLen == LIS眖seqいт妮程腨患糤计秈LIS
	{
		if (seq[i].len == maxLen) //璝讽玡计len == maxLen
		{
			LIS[maxLen - 1] = seq[i].num; //玥盢赣计癸莱竚
			maxLen--;
		}
	}

	cout << LIS.size() << "\n-\n";
	for (int i = 0; i < LIS.size(); cout << LIS[i++] << "\n"); //LIS
	system("pause");
}