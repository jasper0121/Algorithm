#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	vector<int>boy, girl; //男、女
	for (int Case = 1, boyNum, girlNum; cin >> boyNum >> girlNum, boyNum;) //男女個數
	{
		boy.assign(boyNum, int());
		girl.assign(girlNum, int());
		for (int i = 0; i < boyNum; cin >> boy[i++]); //輸入單身狗的年齡
		for (int i = 0; i < girlNum; cin >> girl[i++]); //輸入女生年齡
		if (girlNum >= boyNum) //若女生數量 >= 單身狗
		{
			cout << "Case " << Case++ << ": " << 0 << endl; //每隻單身狗必定能找到伴
			continue;
		}

		sort(boy.begin(), boy.end()); //反之則先由小到大排序
		sort(girl.begin(), girl.end());
		cout << "Case " << Case++ << ": " << boyNum - girlNum<<" " << boy[0] << endl; //再輸出有幾隻單身狗找不到伴，並輸入其中年齡最小者
	}

	system("pause");
}