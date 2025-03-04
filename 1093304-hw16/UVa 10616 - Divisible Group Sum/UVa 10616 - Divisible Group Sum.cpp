#include<iostream>
#include<vector>
using namespace std;

int main()
{
	vector<int>num, rmd; //number�Bremainder
	vector<vector<long long>>dp; //dp[i][j] == ��e���Ƭ�i�A��j�ӼƬۥ[����k��
	for (int Case = 1, N, Q; cin >> N >> Q, N;) //N == �ӼƦC���h�ּƦr�BQ == �d�ߦ���
	{
		num.assign(N, int()); //�إ߼ƦC�j�p
		rmd = num; //remainder���j�p�Pnum�ۦP
		for (int i = 0; i < num.size(); cin >> num[i++]); //��JN�ӼƦr
		cout << "SET " << Case++ << ":\n";
		for (int M, D, q = 1; q <= Q;) //M�ӼƦr�ۥ[�A�ϵ��G��㰣D
		{
			cin >> D >> M; //��J�㰣D�BM�ӼƬۥ[
			dp.assign(M * D + 1, vector<long long>(M + 1)); //dp[i][j] == i��Qj�ӼƬۥ[�㰣����k��
			for (int n = 0; n < num.size(); n++) //�Y�����ƫh������D���l�ơF�Ϥ��Y���t�ƫh�����l�N��n�A�[�WD�A�ϩҦ��ƭ���b0 ~ D - 1���d��
			{
				rmd[n] = num[n] % D + (num[n] > 0 ? 0 : D);
			}

			dp[0][0] = 1; //0�ӼƦr�ۥ[����0����k�� == 1
			for (int r = 0; r < rmd.size(); r++) //���Ҧ����l��
			{
				for (int y = dp.size() - 1; y >= rmd[r]; y--) //�I�]���D�@�ߥѫ᩹�e��
				{
					for (int x = M; x; x--) //�D�س̦h��M�ӼƬۥ[
					{
						//�۷��y�ȨC����h�@�Ӿl�ơB�@��dp[y - rmd[r]][x - 1] == dp[0][0]�A�N��y��x�Ӥ��P���l�Ʋզ��A�G��k�� + 1
						dp[y][x] += dp[y - rmd[r]][x - 1]; 
					}
				}
			}

			long long way = 0;
			for (int n = 0; n < dp.size(); n += D) //�`��k�� == 0�[�WD�����ƪ���k���`�M
			{
				way += dp[n][M]; //n��QM�ӼƦr�[�`�㰣����k��
			}

			cout << "QUERY " << q++ << ": " << way << "\n"; //�DN�Ӽƪ��ƦC���A��M�ӼƦr�ۥ[�A�䵲�G��㰣D����k��
		}
	}

	system("pause");
}