#include<iostream>
#include<vector>
using namespace std;

int main()
{
	vector<int>num, rmd; //numberremainder
	vector<vector<long long>>dp; //dp[i][j] == 讽玡计ij计よ猭计
	for (int Case = 1, N, Q; cin >> N >> Q, N;) //N == 赣计Τぶ计Q == 琩高Ω计
	{
		num.assign(N, int()); //ミ计
		rmd = num; //remainder籔num
		for (int i = 0; i < num.size(); cin >> num[i++]); //块N计
		cout << "SET " << Case++ << ":\n";
		for (int M, D, q = 1; q <= Q;) //M计ㄏ挡狦俱埃D
		{
			cin >> D >> M; //块俱埃DM计
			dp.assign(M * D + 1, vector<long long>(M + 1)); //dp[i][j] == i砆j计俱埃よ猭计
			for (int n = 0; n < num.size(); n++) //璝タ计玥钡D緇计はぇ璝璽计玥Ч緇砃璶Dㄏ┮Τ计0 ~ D - 1絛瞅ず
			{
				rmd[n] = num[n] % D + (num[n] > 0 ? 0 : D);
			}

			dp[0][0] = 1; //0计单0よ猭计 == 1
			for (int r = 0; r < rmd.size(); r++) //癸┮Τ緇计
			{
				for (int y = dp.size() - 1; y >= rmd[r]; y--) //璉拜肈パ┕玡衡
				{
					for (int x = M; x; x--) //肈ヘ程ノM计
					{
						//讽y–Ω搭緇计スdp[y - rmd[r]][x - 1] == dp[0][0]yパxぃ緇计舱Θ珿よ猭计 + 1
						dp[y][x] += dp[y - rmd[r]][x - 1]; 
					}
				}
			}

			long long way = 0;
			for (int n = 0; n < dp.size(); n += D) //羆よ猭计 == 0D计よ猭计羆㎝
			{
				way += dp[n][M]; //n砆M计羆俱埃よ猭计
			}

			cout << "QUERY " << q++ << ": " << way << "\n"; //―N计计いM计ㄤ挡狦俱埃Dよ猭计
		}
	}

	system("pause");
}