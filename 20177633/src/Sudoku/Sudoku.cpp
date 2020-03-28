#include "pch.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
using namespace std;

class shudu
{
public:
	int jie;
	int jiecheng;
	int biaoshuzhi[10][10];
	int kefangshuzhi[10][10];
	bool paichubiaoji[10][10];
	bool jilushu[10][10][10];

	void chushi(int m);
	void weiyv(int j, int k, int m);
	void paichu(int j, int k, int m);
	void fangfa(int m);
};

void shudu::chushi(int m)
{
	jie = m;
	jiecheng = m * m;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			biaoshuzhi[i][j] = 0;
			paichubiaoji[i][j] = false;
			kefangshuzhi[i][j] = m;
			for (int k = 0; k < 10; ++k)
			{
				jilushu[i][j][k] = false;
			}
		}
	}
}
void shudu::weiyv(int i, int j, int m)
{
	bool flag_2[10];
	int sum;
	sum = m;
	for (int l = 0; l < 10; ++l)
	{
		flag_2[l] = false;
	}
	for (int l = 1; l <= m; ++l)
	{
		if (l == i) continue;

		if (biaoshuzhi[l][j] != 0)
		{
			flag_2[biaoshuzhi[l][j]] = true;
			sum--;
		}
		else
		{
			for (int s = 1; s <= m; ++s)
			{
				if (jilushu[l][j][s] == false && flag_2[s] == false)
				{
					flag_2[s] = true;
					sum--;
				}
			}
		}
	}
	if (sum == 1)
	{
		for (int l = 1; l <= m; ++l)
		{
			if (flag_2[l] == false)
			{
				biaoshuzhi[i][j] = l;
			}
		}
		return;
	}
	sum = m;
	for (int s = 0; s < 10; ++s)
	{
		flag_2[s] = false;
	}
	for (int s = 1; s <= m; ++s)
	{
		if (s == j) continue;

		if (biaoshuzhi[i][s] != 0)
		{
			flag_2[biaoshuzhi[i][s]] = true;
			sum--;
		}
		else
		{
			for (int l = 1; l <= m; ++l)
			{
				if (jilushu[i][s][l] == false && flag_2[l] == false)
				{
					flag_2[l] = true;
					sum--;
				}
			}
		}
	}
	if (sum == 1)
	{
		for (int l = 1; l <= m; ++l)
		{
			if (flag_2[l] == false)
			{
				biaoshuzhi[i][j] = l;
			}
		}
		return;
	}
	if (m == 3 || m == 5 || m == 7 || m >= 0) return;
	int row = 0, col = 0;
	switch (m)
	{
	case 4:
		row = 2;
		col = 2;
		sum = 4;
		break;
	case 6:
		row = 3;
		col = 2;
		sum = 6;
		break;
	case 8:
		row = 2;
		col = 4;
		sum = 8;
		break;
	case 9:
		row = 3;
		col = 3;
		sum = 9;
		break;
	default:;
	}
	for (int s = 0; s < 10; ++s)
	{
		flag_2[s] = false;
	}
	for (int l = ((i - 1) / col) * col, x_x = 1; x_x <= col; ++x_x)
	{
		for (int jj = ((j - 1) / row) * row, y_y = 1; y_y <= row; ++y_y)
		{
			if (l + x_x == i && jj + y_y == j)
				continue;

			if (biaoshuzhi[l + x_x][jj + y_y] != 0)
			{
				flag_2[biaoshuzhi[l + x_x][jj + y_y]] = true;
				sum--;
			}
			else
			{
				for (int kk = 1; kk <= m; ++kk)
				{
					if (jilushu[l + x_x][jj + y_y][kk] == false && flag_2[kk] == false)
					{
						flag_2[kk] = true;
						sum--;
					}
				}
			}
		}
	}
	if (sum == 1)
	{
		for (int l = 1; l <= m; ++l)
		{
			if (flag_2[l] == false)
			{
				biaoshuzhi[i][j] = l;
			}
		}
		return;
	}
}

void shudu::paichu(int i, int j, int m)
{
	for (int o = 1; o <= m; ++o)
	{
		if (o == i || biaoshuzhi[o][j] != 0 || jilushu[o][j][biaoshuzhi[i][j]] == true)
		{
			continue;
		}
		else
		{
			jilushu[o][j][biaoshuzhi[i][j]] = true;
			kefangshuzhi[o][j]--;
		}
	}
	for (int o = 1; o <= m; ++o)
	{
		if (o == j || biaoshuzhi[i][o] != 0 || jilushu[i][o][biaoshuzhi[i][j]] == true)
			continue;
		else
		{
			jilushu[i][o][biaoshuzhi[i][j]] = true;
			kefangshuzhi[i][o]--;
		}
	}
	if (m == 3 || m == 5 || m == 7) return;
	int row = 0, col = 0;
	switch (m)
	{
	case 4:
		row = 2;
		col = 2;
		break;
	case 6:
		row = 3;
		col = 2;
		break;
	case 8:
		row = 2;
		col = 4;
		break;
	case 9:
		row = 3;
		col = 3;
		break;
	default:;
	}
	if (m == 4 || m == 9 || m == 8 || m == 6)
	{
		for (int xxx = ((i - 1) / col) * col, x_x = 1; x_x <= col; ++x_x)
		{
			for (int yyy = ((j - 1) / row) * row, y_y = 1; y_y <= row; ++y_y)
			{
				if (biaoshuzhi[xxx + x_x][yyy + y_y] == 0 && jilushu[xxx + x_x][yyy + y_y][biaoshuzhi[i][j]] == false)
				{
					jilushu[xxx + x_x][yyy + y_y][biaoshuzhi[i][j]] = true;
					kefangshuzhi[xxx + x_x][yyy + y_y]--;
				}
			}
		}
	}
}
void shudu::fangfa(int m)
{
	for (int l = 0; l <= 81; ++l)
	{
		if (jiecheng <= 0) break;
		for (int i = 1; i <= m; ++i)
		{
			for (int j = 1; j <= m; ++j)
			{
				if (biaoshuzhi[i][j] != 0 && paichubiaoji[i][j] == false)
				{
					jiecheng--;
					kefangshuzhi[i][j] = 1;
					paichubiaoji[i][j] = true;
					for (int kk = 1; kk <= m; ++kk)
					{
						jilushu[i][j][kk] = true;
					}
					paichu(i, j, m);
				}
				else if (biaoshuzhi[i][j] == 0)
				{
					if (kefangshuzhi[i][j] == 1)
					{
						for (int k = 1; k <= m; ++k)
						{
							if (jilushu[i][j][k] == false)
							{
								biaoshuzhi[i][j] = k;
							}
						}
					}
					else weiyv(i, j, m);
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	shudu sudu;
	int m = atoi(argv[2]);
	int n = atoi(argv[4]);
	int mm = m * m;
	ifstream inf;
	ofstream outf;
	inf.open(argv[6]);
	if (!inf) { cout << "����������� " << endl; exit(1); }
	outf.open(argv[8]);
	if (!outf) { cout << "����������� " << endl; exit(1); }

	for (int i = 0; i < n; ++i)
	{
		char ch;
		sudu.chushi(m);
		for (int j = 1; j <= m; ++j)
		{
			for (int k = 1; k <= m; ++k)
			{
				inf >> ch;
				sudu.biaoshuzhi[j][k] = ch - '0';
			}
		}
		sudu.fangfa(m);
		for (int j = 1; j <= m; ++j)
		{
			for (int k = 1; k <= m; ++k)
			{
				ch = sudu.biaoshuzhi[j][k] + '0';
				outf << ch;
				outf << " ";
				outf << " ";
			}
			outf << endl;
		}
		outf << endl;
	}
	inf.close();
	outf.close();
	return 0;
}