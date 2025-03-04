#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int testCase, width, length, height; //測資、長、寬、高
vector<vector<vector<long long>>>cube; //立方體
vector<vector<long long>>sum_yz; //當前的二維平面加總
vector<long long>sum_y; //當前的行加總

long long max1D()
{
	long long localMax = sum_y[0], globalMax = sum_y[0]; //區域和全域的最大值
	for (int i = 1; i < sum_y.size(); i++)
	{
		localMax = max(localMax + sum_y[i], sum_y[i]); //算出當前最大的子矩陣和
		globalMax = max(globalMax, localMax);
	}

	return globalMax; //回傳最大的一維矩陣和
}

long long max2D()
{
	long long globalMax = LLONG_MIN; //最大的子立方矩陣和，初始設為無限小
	for (int z_left = 0; z_left < height; z_left++) //從左邊的第0行開始，每次向右掃過一遍(在yz平面中，z當成平常的x)
	{
		sum_y.assign(width, 0); //每一輪都要初始化行加總的大小
		for (int z_right = z_left; z_right < height; z_right++) //每次向右掃過一遍
		{
			for (int y = 0; y < width; y++) //將當前行內的值加總
			{
				sum_y[y] += sum_yz[y][z_right];
			}

			globalMax = max(globalMax, max1D()); //每次取當前的最大的子矩陣和
		}
	}

	return globalMax; //回傳最大的二維矩陣和
}

int main()
{
	for (cin >> testCase; testCase--;)
	{
		cin >> length >> width >> height; //輸入長寬高
		cube.assign(height, vector<vector<long long>>(width, vector<long long>(length))); //建圖
		for (int z = 0; z < cube.size(); z++) //輸入矩陣中每一格的值
		{
			for (int y = 0; y < cube[z].size(); y++)
			{
				for (int x = 0; x < cube[z][y].size(); cin >> cube[z][y][x++]);
			}
		}

		long long globalMax = LLONG_MIN; //最大的子立方矩陣和，初始設為無限小
		for (int x_left = 0; x_left < length; x_left++) //從左邊的第0行開始，每次向右掃過一遍
		{
			sum_yz.assign(width, vector<long long>(height)); //每一輪都要初始化二維平面加總的大小
			for (int x_right = x_left; x_right < length; x_right++)
			{
				for (int y = 0; y < width; y++) //將當前二維平面內的值加總，以y為寬、以z為長
				{
					for (int z = 0; z < height; z++)
					{
						sum_yz[y][z] += cube[z][y][x_right];
					}
				}

				globalMax = max(globalMax, max2D()); //每次取當前的最大的子二維矩陣和
			}
		}

		cout << globalMax << (testCase ? "\n\n" : "\n"); //印出最大的子立方矩陣和
	}

	system("pause");
}