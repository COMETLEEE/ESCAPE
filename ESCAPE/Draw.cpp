#include "Draw.h"

extern int g_stageCount;

void Draw_PlayBoard(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int g_copyMazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, int* _playerDir)
{
	for (int y = 0; y < MAZE_SIZE_Y; y++)
	{
		for (int x = 0; x < MAZE_SIZE_X; x++)
		{
			if (g_mazePlayBoard[y][x] != g_copyMazePlayBoard[y][x] || *_playerDir != _player->_direction)
			{
				GoToxy(PLAYBOARD_ADJ_X + x, PLAYBOARD_ADJ_Y + y);

				int dist = (int)sqrt((_player->_pos_y - y) * (_player->_pos_y - y) + (_player->_pos_x - x) * (_player->_pos_x - x));

				if (dist <= _player->_eyeSight)
				{
					if (g_mazePlayBoard[y][x] == HARD_WALL)
					{
						SetColor(BRIGHTGREEN, RED);
						printf("��");
					}
					else if (g_mazePlayBoard[y][x] == GOAL)
					{
						SetColor(WHITE, BLUE);
						printf("��");
					}
					else if (g_mazePlayBoard[y][x] == WALL)
					{
						SetColor(BRIGHTYELLOW, BLUE);
						printf("��");
					}
					else if (g_mazePlayBoard[y][x] == PATH)
					{
						SetColor(WHITE, WHITE);
						printf("  ");
					}
					else if (g_mazePlayBoard[y][x] == BACK)
					{
						SetColor(BLACK, BLACK);
						printf("  ");
					}
					else if (g_mazePlayBoard[y][x] == PLAYER)
					{
						SetColor(WHITE, RED);
						if (_player->_direction == UP)
						{
							printf("��");
							*_playerDir = UP;
						}
						else if (_player->_direction == DOWN)
						{
							printf("��");
							*_playerDir = DOWN;
						}
						else if (_player->_direction == RIGHT)
						{
							printf("��");
							*_playerDir = RIGHT;
						}
						else if (_player->_direction == LEFT)
						{
							printf("��");
							*_playerDir = LEFT;
						}
					}
					else if (g_mazePlayBoard[y][x] == FAIRY_WAY)
					{
						SetColor(WHITE, RED);
						printf("��");
					}
					else if (g_mazePlayBoard[y][x] == ITEM_HAMMER)
					{
						SetColor(WHITE, RED);
						printf("��");
					}
					else if (g_mazePlayBoard[y][x] == ITEM_TORCH)
					{
						SetColor(WHITE, RED);
						printf("��");
					}
					else if (g_mazePlayBoard[y][x] == ITEM_FAIRY)
					{
						SetColor(WHITE, RED);
						printf("��");
					}
					else if (g_mazePlayBoard[y][x] == ITEM_DRILL)
					{
						SetColor(WHITE, RED);
						printf("��");
					}
					else if ((g_mazePlayBoard[y][x] == TRAP_ONE) || (g_mazePlayBoard[y][x] == TRAP_TWO))
					{
						SetColor(WHITE, RED);
						printf("��");
					}
				}
				else
				{
					SetColor(BLACK, BLACK);
					printf("  ");
				}
			}
		}
	}

	for (int y = 0; y < MAZE_SIZE_Y; y++)
	{
		for (int x = 0; x < MAZE_SIZE_X; x++)
		{
			g_copyMazePlayBoard[y][x] = g_mazePlayBoard[y][x];
		}
	}
}

// �ΰ��� UI ���� �κ�
void Draw_UI_FIXED(int g_stageCount)
{
	SetColor(BLACK, BRIGHTWHITE);
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y - 1);  printf("�������������������������������������������������������� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y);	    printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 1);  printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 2);  printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 3);  printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 4);  printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 5);  printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 6);  printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 7);  printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 8);  printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 9);  printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 10); printf("��                          �� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 11); printf("�������������������������������������������������������� ");
	GoToxy(PLAYBOARD_ADJ_X + 56, PLAYBOARD_ADJ_Y);	   printf("  I N V E N T O R Y ");
	SetColor(BLACK, BRIGHTRED);
	GoToxy(PLAYBOARD_ADJ_X + 55, PLAYBOARD_ADJ_Y + 3); printf("   ��  - �� ġ      ��");
	GoToxy(PLAYBOARD_ADJ_X + 55, PLAYBOARD_ADJ_Y + 5); printf("   ��  - �� ��      ��");
	GoToxy(PLAYBOARD_ADJ_X + 55, PLAYBOARD_ADJ_Y + 7); printf("   ��  - ȶ ��      ��");
	GoToxy(PLAYBOARD_ADJ_X + 55, PLAYBOARD_ADJ_Y + 9); printf("   ��  - �� ��      ��");

	SetColor(BLACK, WHITE);
	GoToxy(PLAYBOARD_ADJ_X + 57, PLAYBOARD_ADJ_Y + 13); printf("  - S T A G E  %d -", g_stageCount);

	SetColor(BLACK, BRIGHTWHITE);
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 16); printf("�������� - Ŀ�ǵ� �Է� ����");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 18); printf("�������� - Ÿ�� �Է� ����");

	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 22); printf(" �� ���� �ð� :       "); 

	GoToxy(PLAYBOARD_ADJ_X + 58, PLAYBOARD_ADJ_Y + 28); printf(" -  �� �� ��  - ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 30); printf(" 1 : ��ġ ��� / 2 : ���� ��� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 32); printf(" 3 : ȶ�� ��� / 4 : �帱 ��� ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 34); printf(" ����Ű : �̵� / P : �Ͻ� ���� ");

	// ���������� ������ ��Ʈ
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 38); 
	
	if (g_stageCount == 1) // 1���������� ���
	{
		printf(" �� �������� �߾� ���⿡ �ֽ��ϴ�.");
	}
	else if (g_stageCount == 2) // 2���������� ���
	{
		printf(" �� �������� �߾� ���⿡ �ֽ��ϴ�.");
	}
	else if (g_stageCount == 3) // 3���������� ���
	{
		printf(" �� �������� 5�� ���⿡ �ֽ��ϴ�.");
	}
}

// �ΰ��� UI �ٲ�� �κ�
void Draw_UI_CHANGED(Inventory* _inven, ULONGLONG _leftSec)
{
	SetColor(BLACK, BRIGHTWHITE);
	GoToxy(PLAYBOARD_ADJ_X + 63, PLAYBOARD_ADJ_Y + 3); printf("%d", _inven->item_HammerCnt);
	GoToxy(PLAYBOARD_ADJ_X + 63, PLAYBOARD_ADJ_Y + 5); printf("%d", _inven->item_FairyCnt);
	GoToxy(PLAYBOARD_ADJ_X + 63, PLAYBOARD_ADJ_Y + 7); printf("%d", _inven->item_TorchCnt);
	GoToxy(PLAYBOARD_ADJ_X + 63, PLAYBOARD_ADJ_Y + 9); printf("%d", _inven->item_DrillCnt);
	
	GoToxy(PLAYBOARD_ADJ_X + 62, PLAYBOARD_ADJ_Y + 22); printf("%lld��   ", _leftSec);
}

// ���������� ����Ǿ��� ���� ���������� �Ѿ �� ����Ǵ� ���μ���
void Draw_StageUp()
{
	int x = 5; int y = 4;

	int _frames = 0;
	SetColor(BLACK, WHITE);

	system("cls");

	GoToxy(x + 29, y); printf("�� STAGE CLEAR ��");

	Sleep(1500);

	while (_kbhit()) // ��������� �Է� ���۸� �ʱ�ȭ�Ѵ�.
		_getch();

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 �����Ӹ��� ���
		{
			GoToxy(x + 25, y + 25); printf("PRESS ANY KEY TO GO TO NEXT STAGE"); // ��¦�Ÿ��� �ϰ� ���� ���
		}
		else if ((_frames % 200 - 100) == 0) // 100 ������ �������� ���� (1�� + @) 
		{
			GoToxy(x + 25, y + 25); printf("                                       "); // ��¦�Ÿ��� �ϰ� ���� ���
		}

		Sleep(10);
	}

	system("cls");

	while (_kbhit()) // �Է� ���� �ʱ�ȭ
		_getch();
}

// ��� ���������� Ŭ�����Ͽ��� ���� Ŭ����, ��ŷ �ۼ� ���μ����� �����Ѵ�.
void Draw_GameClear(int remainTime)
{
	int x = 5; int y = 4;

	int _frames = 0;
	SetColor(BLACK, WHITE);

	system("cls");

	GoToxy(x + 29, y); printf("�� GAME CLEAR ��");

	Sleep(1500);

	while (_kbhit()) // ��������� �Է� ���۸� �ʱ�ȭ�Ѵ�.
		_getch();

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 �����Ӹ��� ���
		{
			GoToxy(x + 25, y + 25); printf("PRESS ANY KEY TO GO TO RANKING PAGE"); // ��¦�Ÿ��� �ϰ� ���� ���
		}
		else if ((_frames % 200 - 100) == 0) // 100 ������ �������� ���� (1�� + @) 
		{
			GoToxy(x + 25, y + 25); printf("                                       "); // ��¦�Ÿ��� �ϰ� ���� ���
		}

		Sleep(10);
	}

	RankRecord(remainTime);

	system("cls");

	exit(0); // ��ŷ ���μ��� �� ���� �����մϴ�.
}

// �ð��� �� �Ǿ ���� ���� ���μ����� ������ �� ����ϴ� �Լ�.
void Draw_GameOver()
{
	int x = 5; int y = 4;

	int _frames = 0;

	system("cls");

	SetColor(BLACK, WHITE);
	GoToxy(x + 29, y); printf("�� GAME OVER ��");

	Sleep(1500);

	while (_kbhit()) // ��������� �Է� ���۸� �ʱ�ȭ�Ѵ�.
		_getch();

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 �����Ӹ��� ���
		{
			GoToxy(x + 25, y + 25); printf("PRESS ANY KEY TO GO TO EXIT MAZE"); // ��¦�Ÿ��� �ϰ� ���� ���
		}
		else if ((_frames % 200 - 100) == 0) // 100 ������ �������� ���� (1�� + @) 
		{
			GoToxy(x + 25, y + 25); printf("                                       "); // ��¦�Ÿ��� �ϰ� ���� ���
		}

		Sleep(10);
	}

	system("cls");

	exit(0); 
}


// ���� DFS���� ���� ��ǥ�� �̵����� ������ �迭 (������ ����� ���� ���� �����Ѵ�.)
const int g_delta[4][2] = { {0, -2}, {0, 2}, {-2, 0}, {2, 0} };

// ���� DFS�� ���� �����. InputStageData�� ���ӵ� �Լ�.
void MakeMapByRandomizedDFS(int nowY, int nowX, int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X])
{
	int _directions[4] = { 0,1,2,3 };

	int _nextY;
	int _nextX;

	for (int i = 0; i < 4; i++) // ������ ��Ÿ�� �迭 �����ֱ� (������ ���)
	{
		int j = rand() % 4;
		int temp = _directions[i];
		_directions[i] = _directions[j];
		_directions[j] = temp;
	}

	g_mazePlayBoard[nowY][nowX] = PATH;

	for (int i = 0; i < 4; i++)
	{
		_nextY = nowY + g_delta[_directions[i]][0];
		_nextX = nowX + g_delta[_directions[i]][1];

		if ((_nextY < 0) || (_nextY >= MAZE_SIZE_Y) || (_nextX < 0) || (_nextX >= MAZE_SIZE_X)) // ���� �Ѿ �κ�
			continue;

		if (g_mazePlayBoard[_nextY][_nextX] != WALL) // ���� �ƴ϶�� �̹� ����� �κ��� �ִٴ� ��, ���̻� �������� �ʴ´�
			continue;

		MakeMapByRandomizedDFS(_nextY, _nextX, g_mazePlayBoard);

		if (_nextY != nowY) // ������ �̵��� ���
			g_mazePlayBoard[(nowY + _nextY) / 2][nowX] = PATH;
		else // ������ �̵��� ���
			g_mazePlayBoard[nowY][(nowX + _nextX) / 2] = PATH;
	}
}

void InputStageData(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int g_stageCount, int startX, int startY, int GoalX, int GoalY, string _address)
{
	switch (g_stageCount)
	{
		case 1:
		case 2:
		{
			FILE* fs;

			fs = fopen(_address.c_str(), "r"); // ��� ���� �� �Ұ�
			for (int y = 0; y < MAZE_SIZE_Y; y++)
			{
				for (int x = 0; x < MAZE_SIZE_X; x++)
				{
					fscanf(fs, "%c", &g_mazePlayBoard[y][x]);

					//g_mazePlayBoard[y][x] == '#' ? g_mazePlayBoard[y][x] = WALL : g_mazePlayBoard[y][x] = BACK;

					if (g_mazePlayBoard[y][x] == '#')
					{
						g_mazePlayBoard[y][x] = WALL;
					}
					else if (g_mazePlayBoard[y][x] == ' ')
					{
						g_mazePlayBoard[y][x] = BACK;
					}
					else if (g_mazePlayBoard[y][x] == '@')
					{
						g_mazePlayBoard[y][x] = HARD_WALL;
					}
				}
			}

			// ���� ��κ� BACK ���� ó��
			for (int x = 0; x < MAZE_SIZE_X; x++)
			{
				g_mazePlayBoard[MAZE_SIZE_Y - 1][x] = BACK;
			}

			for (int y = 0; y < MAZE_SIZE_Y; y++)
			{
				g_mazePlayBoard[y][MAZE_SIZE_X - 1] = BACK;
			}
			break;
		}
		case 3:
		{
			for (int y = 0; y < MAZE_SIZE_Y; y++)
				for (int x = 0; x < MAZE_SIZE_X; x++)
					g_mazePlayBoard[y][x] = WALL;

			int _startY = 1 + rand() % (MAZE_SIZE_Y - 1); // ���� ��Ÿ�� ����Ʈ ����
			int _startX = 1 + rand() % (MAZE_SIZE_X - 1);

			if (_startY % 2 == 0) _startY--;
			if (_startX % 2 == 0) _startX--;

			MakeMapByRandomizedDFS(_startY, _startX, g_mazePlayBoard);

			for (int y = 0; y < MAZE_SIZE_Y; y++)
			{
				for (int x = 0; x < MAZE_SIZE_X; x++)
				{
					if (y == 0 || y == MAZE_SIZE_Y - 1 || x == 0 || x == MAZE_SIZE_X - 1)
					{
						g_mazePlayBoard[y][x] = HARD_WALL;
					}
				}
			}
			break;
		}
	}

	// Back �κ��� Path�� �վ��ִ� �κ�
	bool visit[MAZE_SIZE_Y - 1][MAZE_SIZE_X - 1];
	fill(&visit[0][0], &visit[MAZE_SIZE_Y - 2][MAZE_SIZE_X - 1], false);
	int dx[] = { 0,0,1,-1 };
	int dy[] = { 1,-1,0,0 };
	queue<pair<int, int>> q;

	q.push({ startX, startY });
	visit[startX][startY] = true;
	g_mazePlayBoard[startX][startY] = PATH;

	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (g_mazePlayBoard[nx][ny] == BACK && nx >= 0 && nx < MAZE_SIZE_Y && ny >= 0 && ny < MAZE_SIZE_X)
			{
				if (!visit[nx][ny])
				{
					q.push((make_pair(nx, ny)));
					visit[nx][ny] = 1;
					g_mazePlayBoard[nx][ny] = PATH;
				}
			}
		}
	}

	// ������, ���� ���� ��ġ�ϴ� �κ�
	int hammerCnt = 5;
	int fairyCnt = 4;
	int torchCnt = 10;
	int drillCnt = 1;
	int commandTrapCnt = 25;

	vector<pair<int, int>> pathVec;

	for (int y = 0; y < MAZE_SIZE_Y; y++)
	{
		for (int x = 0; x < MAZE_SIZE_X; x++)
		{
			if (g_mazePlayBoard[y][x] == PATH)
			{
				pathVec.push_back({ y,x });
			}
		}
	}

	int randomTrap = rand() % 2 + 8; // 8 ~ 9
	int randomItem = rand() % 4 + 10; // 10 ~ 13
	int randomPath = rand() % (pathVec.size() - 1);

	while (!(hammerCnt == 0 && fairyCnt == 0 && torchCnt == 0 && drillCnt == 0))
	{
		if (randomItem == ITEM_HAMMER && hammerCnt > 0)
		{
			g_mazePlayBoard[pathVec[randomPath].first][pathVec[randomPath].second] = ITEM_HAMMER;
			pathVec.erase(pathVec.begin() + randomPath);
			hammerCnt--;
		}
		else if (randomItem == ITEM_FAIRY && fairyCnt > 0)
		{
			g_mazePlayBoard[pathVec[randomPath].first][pathVec[randomPath].second] = ITEM_FAIRY;
			pathVec.erase(pathVec.begin() + randomPath);
			fairyCnt--;
		}
		else if (randomItem == ITEM_TORCH && torchCnt > 0)
		{
			g_mazePlayBoard[pathVec[randomPath].first][pathVec[randomPath].second] = ITEM_TORCH;
			pathVec.erase(pathVec.begin() + randomPath);
			torchCnt--;
		}
		else if (randomItem == ITEM_DRILL && drillCnt > 0)
		{
			g_mazePlayBoard[pathVec[randomPath].first][pathVec[randomPath].second] = ITEM_DRILL;
			pathVec.erase(pathVec.begin() + randomPath);
			drillCnt--;
		}

		randomItem = rand() % 4 + 10;
		randomPath = rand() % (pathVec.size() - 1);
	}

	while (commandTrapCnt != 0)
	{
		if (commandTrapCnt > 0)
		{
			g_mazePlayBoard[pathVec[randomPath].first][pathVec[randomPath].second] = randomTrap;
			pathVec.erase(pathVec.begin() + randomPath);
			commandTrapCnt--;
		}
		randomPath = rand() % (pathVec.size() - 1);
		randomTrap = rand() % 2 + 8;
	}

	g_mazePlayBoard[GoalY][GoalX] = GOAL;
}

void Reset_CopyMazePlayBoard(int g_copyMazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X])
{
	fill(&g_copyMazePlayBoard[0][0], &g_copyMazePlayBoard[MAZE_SIZE_Y - 1][MAZE_SIZE_X], -1);
}

void Draw_Story()
{
	system("cls");

	Sleep(500);

	while (_kbhit()) // ��������� �Է� ���۸� �ʱ�ȭ�Ѵ�.
		_getch();

	int x = 5; int y = 4;

	SetColor(BLACK, WHITE);

	char story[255] = "����������� ���� ���� ���� ���� �����̴� ���ڱ� ���� �̼��� �̷ο� ������ �ȴ�. �������� �ʱ� ���� �̷θ� Ż���϶� !";
	char* ptr = story;

	GoToxy(x + 15, y + 15);

	while(*ptr)
	{
		if (_kbhit()) 
			break;

		if (*ptr <= 128 && *ptr >= 0)
		{
			printf("%c", *ptr); Sleep(50);
			ptr += 1;
		}
		else
		{
			printf("%c%c", *ptr, *(ptr + 1)); Sleep(50);
			ptr += 2;
		}

		if (*ptr == '.')
		{
			Sleep(1000);
			system("cls");
			GoToxy(x + 23, y + 15);
			ptr += 1;
		}
	}

	system("cls");
	GoToxy(x + 23, y + 15); printf(" �������� �ʱ� ���� �̷θ� Ż���϶� !");

	while (_kbhit()) // ��������� �Է� ���۸� �ʱ�ȭ�Ѵ�.
		_getch();

	int _frames = 0;

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 �����Ӹ��� ���
		{
			GoToxy(x + 25, y + 25); printf("PRESS ANY KEY TO GO TO MAZE"); // ��¦�Ÿ��� �ϰ� ���� ���
		}
		else if ((_frames % 200 - 100) == 0) // 100 ������ �������� ���� (1�� + @) 
		{
			GoToxy(x + 25, y + 25); printf("                                       "); // ��¦�Ÿ��� �ϰ� ���� ���
		}

		Sleep(10);
	}

	system("cls");
}