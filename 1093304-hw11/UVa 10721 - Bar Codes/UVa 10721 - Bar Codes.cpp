#include<iostream>
using namespace std;

long long bar[51][51][51]; //0���ΡAbarNum(�`����)�Bzone(�¥զX�p���X�Ӱϰ�)�Bwidth(�P�C�⪺�����e��)

int main()
{
	for (int barNum = 1; barNum <= 50; barNum++) //�D�سW�w��1��������
	{
		for (int width = barNum; width <= 50; bar[barNum][1][width++] = 1); //�Y�ϰ쬰1�A�h�Ӱϰ쥲�u���¦�A�G�u��1�زզX
	}

	for (int barNum = 1; barNum <= 50; barNum++)
	{
		for (int zone = 1; zone <= 50; zone++)
		{
			for (int width = 1; width <= 50; width++)
			{
				if (width > barNum) //�Y�����e�� > �`���ơA�h�Ӥ�k�Ƶ��P�󷥭��e�� == �`����
				{
					bar[barNum][zone][width] = bar[barNum][zone][barNum];
					continue;
				}

				for (int add = 1; add <= width; add++) //���add�Ƶ��P��b�̧��ݥ[�W�P���C�⪺���ơA�]��zone�n - 1�Cadd���W�����Pwidth
				{
					bar[barNum][zone][width] += bar[barNum - add][zone - 1][width];
				}
			}
		}
	}

	for (int barNum, zone, width; cin >> barNum >> zone >> width; cout << bar[barNum][zone][width] << "\n"); //�ھڿ�J����L�X��������
	system("pause");
}