#include<iostream>
#include<vector>
using namespace std;

struct two //���C�ӼƦC�A���쥻���Ʀr���~�A�ٷ|����ӼƦr�b�l�r�ꤤ������
{
	int num, len;
};

int main()
{
	vector<two>seq; //�ƦC
	vector<int>LIS; //�̪��Y�滼�W�l�ǦC
	for (int num; cin >> num; seq.push_back({ num,1 })); //��J�ƦC�A��l�Ҧ��Ʀr���׳��w�]��1(�Y�Ҧ��Ʀr�@�}�l���i�ন���l�r�ꪺ�}�Y)
	LIS.push_back(seq[0].num); //�@�}�l���N�ƦC���̶}�Y���Ʀr�[�J�̪��Y�滼�W�l�ǦC
	for (int i = 1; i < seq.size(); i++) //LIS�t��k�A�q�ƦC��index == 1����m�}�l
	{
		if (seq[i].num > LIS.back()) //�Y�ƦC����e���Ʀr > LIS���̫᭱���Ʀr
		{
			LIS.push_back(seq[i].num); //�h�����N��e���Ʀr�[�JLIS��
			seq[i].len = LIS.size(); //�ӼƦbLIS�������� == LIS���j�p
			continue;
		}

		auto it = lower_bound(LIS.begin(), LIS.end(), seq[i].num); //�Ϥ��A�h����XLIS���A�Ҧ��j��seq[i].num�������̤p��
		*it = seq[i].num; //����N���w��m���ƥ�seq[i].num���N�A�ϱo�bseq[i].num����i������h���Ʀr
		seq[i].len = (it - LIS.begin() + 1); //��e�ƪ����� == �Ҧb��index + 1
	}

	//�̫᪺LIS��size()�Y���ҨD���סA�]�P�˪��ת��ƥi��|���ܦh�ӡA���Plen���ƥѫe��ᥲ�w�O�Ѥj��p�A�G�qseq���̫�}�l���e��
	for (int i = seq.size() - 1, maxLen = LIS.size(); i >= 0; i--) //��lmaxLen == LIS���סB�qseq����X�ݩ�̪��Y�滼�W�l�ǦC���ƨé�iLIS
	{
		if (seq[i].len == maxLen) //�Y��e�ƪ�len == maxLen
		{
			LIS[maxLen - 1] = seq[i].num; //�h�N�ӼƩ�J��������m
			maxLen--;
		}
	}

	cout << LIS.size() << "\n-\n";
	for (int i = 0; i < LIS.size(); cout << LIS[i++] << "\n"); //�L�XLIS
	system("pause");
}