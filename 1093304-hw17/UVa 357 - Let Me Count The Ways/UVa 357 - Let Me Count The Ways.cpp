#include<iostream>
#include<vector>
using namespace std;

int main()
{
	const int unit[] = { 1,5,10,25,50 }; //有5種硬幣面額
	vector<long long>coin(30001); //題目規定輸入範圍0 <= x <= 30000
	coin[0] = 1; //0元有1種組合，即全部都不拿
	for (auto& u : unit) //對於所有的面額
	{
		for (int i = u; i <= 30000; i++)
		{
			//ex：若u == 5，則初始(coin[5] += coin[0]) == 1，之後(coin[6] += coin[1]) == 1，(coin[10] += coin[5]) == 1種組合，以此類推
			coin[i] += coin[i - u]; //當下錢的組合數 == 拿掉當前指定面額u時的組合數(加上u後coin[i - u]組合數不變，但可增加coin[i]的組合數)
		}
	}

	for (int N; cin >> N; cout << " to produce " << N << " cents change.\n")
	{
		if (coin[N] == 1) //若組合數只有1種
		{
			cout << "There is only 1 way";
			continue;
		}

		cout << "There are " << coin[N] << " ways"; //若組合數大於1種，則輸出N元的組合方法數
	}

	system("pause");
}