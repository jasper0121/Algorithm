#include<iostream>
using namespace std;

int way[101][101]; //��k�ơC�Ĥ@��N��@�ӼƦrn�A�ĤG��N��n�m�Ӽ�

int main()
{
	for (int num = 0; num <= 100; way[num++][1] = 1); //����Ʃ1�ӳ������զX�ƴN�u�|�O�Ӽƥ����A�u�|��1�زզX
	for (int num = 0; num <= 100; num++) //����զX���i�H��0�A�G�n�q0�}�l�_��
	{
		for (int part = 1; part <= 100; part++) //�ܤ֤@�w�|�1�ӳ����A�G�q1�}�l�_��
		{
			for (int add = 0; add <= num; add++) //�Yadd��0�A�N��bpart - 1���զX�������A�h�[�@��0�Ӧ���part����k�ơA�G�n�q0�}�l�_��
			{
			 	 //��h��add��@�O�̫�[�W�h�A�Gpart�n - 1�A�̫�add�[�b�ӲզX���ݡA�~�|�O�ҭn�D��part��
				(way[num][part] += way[num - add][part - 1]) %= 1000000; //�l1000000���D�حn�D�Aadd���W����num��
			}
		}
	}

	for (int num, part; cin >> num >> part, num; cout << way[num][part] << "\n"); //�ھڿ�J���ȦL�X��������k�ơA�Y��J0�h���X
	system("pause");
}