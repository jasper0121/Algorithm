#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int testCase, num, Case = 1; //����B�ؿv���ơB��e����
	vector<int>hight, width, LIS, LDS; //�ؿv�������P�e�B�̪��Y�滼�W�P����A�C��s�즹�ؿv�����L�{�����̤j�e���`�M
	for (cin >> testCase; testCase--;)
	{
		cin >> num; //��J�ؿv����
		int LIS_max = 0, LDS_max = 0; //�D�بD�����Y�滼�W�M����(���ΨD�̪�)�A�B�Ҧ����W���զX���e���`�M�̼e��
		hight.assign(num, int()); //�ؿv������
		width.assign(num, int()); //�ؿv���e��
		for (int i = 0; i < hight.size(); cin >> hight[i++]); //��J�Ҧ�����
		for (int i = 0; i < width.size(); cin >> width[i++]); //��J�Ҧ��e��
		LIS = LDS = width; //��lLIS�MLDS�����ȩMwidth�@��(�o�̦s���O���W/���C�ӫؿv���ɪ��ֿn�e��)
		for (int cur = 0; cur < hight.size(); cur++) //current�N�Ҧ������ר��L�@�M
		{
			for (int tar = 0; tar <= cur; tar++) //�C��current�Mcurrent�e���Ҧ����Ʀr���
			{
				if (hight[cur] > hight[tar]) //�Ycurrent��ؼмƦr�j�A�N���W
				{
					LIS[cur] = max(LIS[cur], LIS[tar] + width[cur]); //�Ytarget���ֿn�e�� + current���e�� > current���ֿn�e�סA�h��sLIS[cur]����
				}
				else if (hight[cur] < hight[tar]) //�Ycurrent��ؼмƦr�p�A�N����
				{
					LDS[cur] = max(LDS[cur], LDS[tar] + width[cur]); //�Ytarget���ֿn�e�� + current���e�� > current���ֿn�e�סA�h��sLDS[cur]����
				}

				LIS_max = max(LIS_max, LIS[cur]); //�̫����A��e��LIS[cur]�O�_��ثe���̤j���٤j
				LDS_max = max(LDS_max, LDS[cur]); //�̫����A��e��LDS[cur]�O�_��ثe���̤j���٤j
			}
		}

		cout << "Case " << Case++ << ". ";
		if (LIS_max >= LDS_max) //�D�حn�D���ӳ̤j�ȸ��j�N����X
		{
			cout << "Increasing (" << LIS_max << "). Decreasing (" << LDS_max << ").\n";
			continue;
		}

		cout << "Decreasing (" << LDS_max << "). Increasing (" << LIS_max << ").\n";
	}

	system("pause");
}