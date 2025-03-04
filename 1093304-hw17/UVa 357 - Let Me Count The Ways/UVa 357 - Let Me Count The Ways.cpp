#include<iostream>
#include<vector>
using namespace std;

int main()
{
	const int unit[] = { 1,5,10,25,50 }; //��5�صw�����B
	vector<long long>coin(30001); //�D�سW�w��J�d��0 <= x <= 30000
	coin[0] = 1; //0����1�زզX�A�Y����������
	for (auto& u : unit) //���Ҧ������B
	{
		for (int i = u; i <= 30000; i++)
		{
			//ex�G�Yu == 5�A�h��l(coin[5] += coin[0]) == 1�A����(coin[6] += coin[1]) == 1�A(coin[10] += coin[5]) == 1�زզX�A�H������
			coin[i] += coin[i - u]; //��U�����զX�� == ������e���w���Bu�ɪ��զX��(�[�Wu��coin[i - u]�զX�Ƥ��ܡA���i�W�[coin[i]���զX��)
		}
	}

	for (int N; cin >> N; cout << " to produce " << N << " cents change.\n")
	{
		if (coin[N] == 1) //�Y�զX�ƥu��1��
		{
			cout << "There is only 1 way";
			continue;
		}

		cout << "There are " << coin[N] << " ways"; //�Y�զX�Ƥj��1�ءA�h��XN�����զX��k��
	}

	system("pause");
}