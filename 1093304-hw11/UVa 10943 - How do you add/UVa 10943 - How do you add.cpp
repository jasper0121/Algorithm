#include<iostream>
using namespace std;

int way[101][101]; //方法數。第一格代表一個數字n，第二格代表n拆成m個數

int main()
{
	for (int num = 0; num <= 100; way[num++][1] = 1); //任何數拆成1個部份的組合數就只會是該數本身，只會有1種組合
	for (int num = 0; num <= 100; num++) //拆成的組合中可以有0，故要從0開始起算
	{
		for (int part = 1; part <= 100; part++) //至少一定會拆成1個部分，故從1開始起算
		{
			for (int add = 0; add <= num; add++) //若add為0，代表在part - 1的組合中直接再多加一個0來成為part的方法數，故要從0開始起算
			{
			 	 //減去的add當作是最後加上去，故part要 - 1，最後add加在該組合尾端，才會是所要求的part數
				(way[num][part] += way[num - add][part - 1]) %= 1000000; //餘1000000為題目要求，add的上限為num數
			}
		}
	}

	for (int num, part; cin >> num >> part, num; cout << way[num][part] << "\n"); //根據輸入的值印出對應的方法數，若輸入0則跳出
	system("pause");
}