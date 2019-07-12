#include <stdio.h>
#include <vector>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

int nfiled[101][101];
int total_shark;
int r, c;
int nRet;

typedef struct inf{
	int x, y, s, d, z, check /*상어의 생사 여부*/, num; // x위치, y위치, 속도, 이동방향 1 : 위 2 : 아래 3 : 오른쪽 4 : 왼쪽, 크기
};

int dirx[] = { 0, 0, 0, 1, -1 };
int diry[] = { 0, -1, 1, 0, 0 };

inf shark_arr[10001];

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
				nRet += shark_arr[nfiled[j][t] - 1].z;
				shark_arr[nfiled[j][t] - 1].check = 0;
				nfiled[j][t] = 0; // shark die
				break;
			}
		}

		for (int i = 0; i < total_shark; i++){
			if (shark_arr[i].check)
			{
				if (shark_arr[i].s)
				{
					nfiled[shark_arr[i].y][shark_arr[i].x] = 0;
					fnshark_move(&shark_arr[i].x, &shark_arr[i].y, &shark_arr[i].d, shark_arr[i].s);
				}
				else
				{
					nfiled[shark_arr[i].y][shark_arr[i].x] = 0;
					continue;
				}
			}
		}

		for (int i = 0; i < total_shark; i++){
			if (shark_arr[i].check)
			{
				if (nfiled[shark_arr[i].y][shark_arr[i].x]) // shark exist
				{
					if (shark_arr[nfiled[shark_arr[i].y][shark_arr[i].x] - 1].z < shark_arr[i].z) // eat shark
					{
						shark_arr[nfiled[shark_arr[i].y][shark_arr[i].x] - 1].check = 0;
						nfiled[shark_arr[i].y][shark_arr[i].x] = shark_arr[i].num;
					}
					else
					{
						shark_arr[i].check = 0;
					}
				}
				else // shark not exist
				{
					nfiled[shark_arr[i].y][shark_arr[i].x] = shark_arr[i].num;
				}
			}
		}


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

		for (int i = 0; i < total_shark; i++){
			inf temp;
			scanf("%d %d %d %d %d", &temp.y, &temp.x, &temp.s, &temp.d, &temp.z);
			temp.x -= 1;
			temp.y -= 1;
			temp.check = 1;
			temp.num = i + 1;
			shark_arr[i] = temp;
			
			nfiled[temp.y][temp.x] = i + 1;
		}

		nRet = 0;
		fnSol();

		printf("%d\n", nRet);
	}

	return 0;
}