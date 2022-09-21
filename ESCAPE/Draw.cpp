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
						printf("■");
					}
					else if (g_mazePlayBoard[y][x] == GOAL)
					{
						SetColor(WHITE, BLUE);
						printf("▩");
					}
					else if (g_mazePlayBoard[y][x] == WALL)
					{
						SetColor(BRIGHTYELLOW, BLUE);
						printf("■");
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
							printf("▲");
							*_playerDir = UP;
						}
						else if (_player->_direction == DOWN)
						{
							printf("▼");
							*_playerDir = DOWN;
						}
						else if (_player->_direction == RIGHT)
						{
							printf("▶");
							*_playerDir = RIGHT;
						}
						else if (_player->_direction == LEFT)
						{
							printf("◀");
							*_playerDir = LEFT;
						}
					}
					else if (g_mazePlayBoard[y][x] == FAIRY_WAY)
					{
						SetColor(WHITE, RED);
						printf("¤");
					}
					else if (g_mazePlayBoard[y][x] == ITEM_HAMMER)
					{
						SetColor(WHITE, RED);
						printf("◆");
					}
					else if (g_mazePlayBoard[y][x] == ITEM_TORCH)
					{
						SetColor(WHITE, RED);
						printf("♨");
					}
					else if (g_mazePlayBoard[y][x] == ITEM_FAIRY)
					{
						SetColor(WHITE, RED);
						printf("◈");
					}
					else if (g_mazePlayBoard[y][x] == ITEM_DRILL)
					{
						SetColor(WHITE, RED);
						printf("★");
					}
					else if ((g_mazePlayBoard[y][x] == TRAP_ONE) || (g_mazePlayBoard[y][x] == TRAP_TWO))
					{
						SetColor(WHITE, RED);
						printf("※");
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

// 인게임 UI 고정 부분
void Draw_UI_FIXED(int g_stageCount)
{
	SetColor(BLACK, BRIGHTWHITE);
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y - 1);  printf("┌──────────────────────────┐ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y);	    printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 1);  printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 2);  printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 3);  printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 4);  printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 5);  printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 6);  printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 7);  printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 8);  printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 9);  printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 10); printf("│                          │ ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 11); printf("└──────────────────────────┘ ");
	GoToxy(PLAYBOARD_ADJ_X + 56, PLAYBOARD_ADJ_Y);	   printf("  I N V E N T O R Y ");
	SetColor(BLACK, BRIGHTRED);
	GoToxy(PLAYBOARD_ADJ_X + 55, PLAYBOARD_ADJ_Y + 3); printf("   ◆  - 망 치      개");
	GoToxy(PLAYBOARD_ADJ_X + 55, PLAYBOARD_ADJ_Y + 5); printf("   ◈  - 요 정      개");
	GoToxy(PLAYBOARD_ADJ_X + 55, PLAYBOARD_ADJ_Y + 7); printf("   ♨  - 횃 불      개");
	GoToxy(PLAYBOARD_ADJ_X + 55, PLAYBOARD_ADJ_Y + 9); printf("   ★  - 드 릴      개");

	SetColor(BLACK, WHITE);
	GoToxy(PLAYBOARD_ADJ_X + 57, PLAYBOARD_ADJ_Y + 13); printf("  - S T A G E  %d -", g_stageCount);

	SetColor(BLACK, BRIGHTWHITE);
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 16); printf("【함정】 - 커맨드 입력 함정");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 18); printf("【함정】 - 타자 입력 함정");

	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 22); printf(" ○ 남은 시간 :       "); 

	GoToxy(PLAYBOARD_ADJ_X + 58, PLAYBOARD_ADJ_Y + 28); printf(" -  조 작 법  - ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 30); printf(" 1 : 망치 사용 / 2 : 요정 사용 ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 32); printf(" 3 : 횃불 사용 / 4 : 드릴 사용 ");
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 34); printf(" 방향키 : 이동 / P : 일시 정지 ");

	// 스테이지별 도착지 힌트
	GoToxy(PLAYBOARD_ADJ_X + 54, PLAYBOARD_ADJ_Y + 38); 
	
	if (g_stageCount == 1) // 1스테이지인 경우
	{
		printf(" ※ 도착지는 중앙 방향에 있습니다.");
	}
	else if (g_stageCount == 2) // 2스테이지인 경우
	{
		printf(" ※ 도착지는 중앙 방향에 있습니다.");
	}
	else if (g_stageCount == 3) // 3스테이지인 경우
	{
		printf(" ※ 도착지는 5시 방향에 있습니다.");
	}
}

// 인게임 UI 바뀌는 부분
void Draw_UI_CHANGED(Inventory* _inven, ULONGLONG _leftSec)
{
	SetColor(BLACK, BRIGHTWHITE);
	GoToxy(PLAYBOARD_ADJ_X + 63, PLAYBOARD_ADJ_Y + 3); printf("%d", _inven->item_HammerCnt);
	GoToxy(PLAYBOARD_ADJ_X + 63, PLAYBOARD_ADJ_Y + 5); printf("%d", _inven->item_FairyCnt);
	GoToxy(PLAYBOARD_ADJ_X + 63, PLAYBOARD_ADJ_Y + 7); printf("%d", _inven->item_TorchCnt);
	GoToxy(PLAYBOARD_ADJ_X + 63, PLAYBOARD_ADJ_Y + 9); printf("%d", _inven->item_DrillCnt);
	
	GoToxy(PLAYBOARD_ADJ_X + 62, PLAYBOARD_ADJ_Y + 22); printf("%lld초   ", _leftSec);
}

// 스테이지가 종료되었고 다음 스테이지로 넘어갈 때 진행되는 프로세스
void Draw_StageUp()
{
	int x = 5; int y = 4;

	int _frames = 0;
	SetColor(BLACK, WHITE);

	system("cls");

	GoToxy(x + 29, y); printf("○ STAGE CLEAR ○");

	Sleep(1500);

	while (_kbhit()) // 현재까지의 입력 버퍼를 초기화한다.
		_getch();

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 프레임마다 띄움
		{
			GoToxy(x + 25, y + 25); printf("PRESS ANY KEY TO GO TO NEXT STAGE"); // 반짝거리게 하고 싶은 욕심
		}
		else if ((_frames % 200 - 100) == 0) // 100 프레임 간격으로 지움 (1초 + @) 
		{
			GoToxy(x + 25, y + 25); printf("                                       "); // 반짝거리게 하고 싶은 욕심
		}

		Sleep(10);
	}

	system("cls");

	while (_kbhit()) // 입력 버퍼 초기화
		_getch();
}

// 모든 스테이지를 클리어하였고 게임 클리어, 랭킹 작성 프로세스로 진입한다.
void Draw_GameClear(int remainTime)
{
	int x = 5; int y = 4;

	int _frames = 0;
	SetColor(BLACK, WHITE);

	system("cls");

	GoToxy(x + 29, y); printf("○ GAME CLEAR ○");

	Sleep(1500);

	while (_kbhit()) // 현재까지의 입력 버퍼를 초기화한다.
		_getch();

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 프레임마다 띄움
		{
			GoToxy(x + 25, y + 25); printf("PRESS ANY KEY TO GO TO RANKING PAGE"); // 반짝거리게 하고 싶은 욕심
		}
		else if ((_frames % 200 - 100) == 0) // 100 프레임 간격으로 지움 (1초 + @) 
		{
			GoToxy(x + 25, y + 25); printf("                                       "); // 반짝거리게 하고 싶은 욕심
		}

		Sleep(10);
	}

	RankRecord(remainTime);

	system("cls");

	exit(0); // 랭킹 프로세스 후 정상 종료합니다.
}

// 시간이 다 되어서 게임 오버 프로세스로 진입할 때 사용하는 함수.
void Draw_GameOver()
{
	int x = 5; int y = 4;

	int _frames = 0;

	system("cls");

	SetColor(BLACK, WHITE);
	GoToxy(x + 29, y); printf("○ GAME OVER ○");

	Sleep(1500);

	while (_kbhit()) // 현재까지의 입력 버퍼를 초기화한다.
		_getch();

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 프레임마다 띄움
		{
			GoToxy(x + 25, y + 25); printf("PRESS ANY KEY TO GO TO EXIT MAZE"); // 반짝거리게 하고 싶은 욕심
		}
		else if ((_frames % 200 - 100) == 0) // 100 프레임 간격으로 지움 (1초 + @) 
		{
			GoToxy(x + 25, y + 25); printf("                                       "); // 반짝거리게 하고 싶은 욕심
		}

		Sleep(10);
	}

	system("cls");

	exit(0); 
}


// 랜덤 DFS에서 사용될 좌표의 이동값을 저장한 배열 (랜덤성 향상을 위해 따로 저장한다.)
const int g_delta[4][2] = { {0, -2}, {0, 2}, {-2, 0}, {2, 0} };

// 랜덤 DFS로 맵을 만든다. InputStageData에 종속될 함수.
void MakeMapByRandomizedDFS(int nowY, int nowX, int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X])
{
	int _directions[4] = { 0,1,2,3 };

	int _nextY;
	int _nextX;

	for (int i = 0; i < 4; i++) // 방향을 나타낼 배열 섞어주기 (랜덤성 향상)
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

		if ((_nextY < 0) || (_nextY >= MAZE_SIZE_Y) || (_nextX < 0) || (_nextX >= MAZE_SIZE_X)) // 범위 넘어간 부분
			continue;

		if (g_mazePlayBoard[_nextY][_nextX] != WALL) // 벽이 아니라면 이미 연결된 부분이 있다는 것, 더이상 연결하지 않는다
			continue;

		MakeMapByRandomizedDFS(_nextY, _nextX, g_mazePlayBoard);

		if (_nextY != nowY) // 세로축 이동인 경우
			g_mazePlayBoard[(nowY + _nextY) / 2][nowX] = PATH;
		else // 가로축 이동인 경우
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

			fs = fopen(_address.c_str(), "r"); // 경로 지정 잘 할것
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

			// 끝에 빈부분 BACK 으로 처리
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

			int _startY = 1 + rand() % (MAZE_SIZE_Y - 1); // 랜덤 스타팅 포인트 셋팅
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

	// Back 부분을 Path로 뚫어주는 부분
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

	// 아이템, 함정 랜덤 배치하는 부분
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

	while (_kbhit()) // 현재까지의 입력 버퍼를 초기화한다.
		_getch();

	int x = 5; int y = 4;

	SetColor(BLACK, WHITE);

	char story[255] = "게임인재원에 가기 위해 집을 나선 혜성이는 갑자기 생긴 이세계 미로에 빠지게 된다. 지각하지 않기 위해 미로를 탈출하라 !";
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
	GoToxy(x + 23, y + 15); printf(" 지각하지 않기 위해 미로를 탈출하라 !");

	while (_kbhit()) // 현재까지의 입력 버퍼를 초기화한다.
		_getch();

	int _frames = 0;

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 프레임마다 띄움
		{
			GoToxy(x + 25, y + 25); printf("PRESS ANY KEY TO GO TO MAZE"); // 반짝거리게 하고 싶은 욕심
		}
		else if ((_frames % 200 - 100) == 0) // 100 프레임 간격으로 지움 (1초 + @) 
		{
			GoToxy(x + 25, y + 25); printf("                                       "); // 반짝거리게 하고 싶은 욕심
		}

		Sleep(10);
	}

	system("cls");
}