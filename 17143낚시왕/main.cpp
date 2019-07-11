#include <stdio.h>
#include <vector>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int nfiled[101][101];
int total_shark;
int r, c;
int nRet;

typedef struct inf{
	int x, y, s, d, z; // x위치, y위치, 속도, 이동방향 1 : 위 2 : 아래 3 : 오른쪽 4 : 왼쪽, 크기
};

int dirx[] = { 0, 0, 0, 1, -1 };
int diry[] = { 0, -1, 1, 0, 0 };

vector <inf> shark_inf;

int fnchange_dir(int cur_dir)
{
	int next_dir = 0;
	switch (cur_dir)
	{
	case 1:
		next_dir = 2; break;
	case 2:
		next_dir = 1; break;
	case 3:
		next_dir = 4; break;
	case 4:
		next_dir = 3; break;
	}
	return next_dir;
}


void fnshark_move(int *posx, int *posy, int *dir, int num)
{
	int cur_dir = *dir;
	for (int i = 0; i < num; i++)
	{
		*posx += dirx[cur_dir];
		*posy += diry[cur_dir];

		if (*posx >= 0 && *posx < r && *posy >= 0 && *posy < c){
			continue;
		}
		else{
			cur_dir = fnchange_dir(cur_dir);
			*posx += dirx[cur_dir];
			*posy += diry[cur_dir];
			*posx += dirx[cur_dir];
			*posy += diry[cur_dir];
		}
	}
	*dir = cur_dir;
}

int fnSol()
{
	for (int t = 0; t < r; t++)
	{
		for (int j = 0; j < c; j++){
			if (nfiled[j][t]){
				nRet += shark_inf[nfiled[j][t] - 1].z;
				nfiled[j][t] = 0; // shark die
				break;
			}
		}

		int nfiled_copy[101][101] = { 0, };

		for (int i = 0; i < shark_inf.size(); i++){
			if (nfiled[shark_inf[i].y][shark_inf[i].x])
			{
				if (shark_inf[i].s)
				{
					nfiled_copy[shark_inf[i].y][shark_inf[i].x] = 0;
					fnshark_move(&shark_inf[i].x, &shark_inf[i].y, &shark_inf[i].d, shark_inf[i].s);
				}
				else
				{
					nfiled_copy[shark_inf[i].y][shark_inf[i].x] = i + 1;
					continue;
				}
				if (nfiled_copy[shark_inf[i].y][shark_inf[i].x])
				{
					int move_param = nfiled_copy[shark_inf[i].y][shark_inf[i].x] - 1;
					if (shark_inf[i].z > shark_inf[move_param].z)
						nfiled_copy[shark_inf[i].y][shark_inf[i].x] = i + 1;
				}
				else
				{
					nfiled_copy[shark_inf[i].y][shark_inf[i].x] = i + 1;
				}
			}
		}

		for (int i = 0; i < c; i++)
			for (int j = 0; j < r; j++)
				nfiled[i][j] = nfiled_copy[i][j];
	}

	return 0;
}

int main()
{
	int t;
	int test_case;

	freopen("input.txt", "r", stdin);

	scanf("%d", &t);
	for (test_case = 1; test_case <= t; ++test_case)
	{
		scanf("%d %d %d", &c, &r, &total_shark);
		
		for (int i = 0; i < c; i++)
			for (int j = 0; j < r; j++)
				nfiled[i][j] = 0;
			
		shark_inf.clear();
		for (int i = 0; i < total_shark; i++){
			inf temp;
			scanf("%d %d %d %d %d", &temp.y, &temp.x, &temp.s, &temp.d, &temp.z);
			temp.x -= 1;
			temp.y -= 1;
			shark_inf.push_back(temp);
			nfiled[temp.y][temp.x] = i + 1;
		}

		nRet = 0;
		fnSol();

		printf("%d\n", nRet);

	}
	return 0;
}