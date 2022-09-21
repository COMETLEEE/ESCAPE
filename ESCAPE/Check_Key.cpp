#include "All_lib.h"
#include "Check_Key.h"
#include "Utils.h"
#include "Sound.h"

extern int g_copyMazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X];
extern int g_playerDir;
extern int g_stageCount;

// 키 입력을 확인하여 각각의 키에 따라서 프로세스를 진행한다. (P : Pause() 함수 / 방향키 : 캐릭터가 바라보고 있는 방향을 방향키와 일치하게 변경 후 범위 및 이동 가능 여부 체크 후 캐릭터 이동 / 아이템 사용 : )
void Check_Key(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, Inventory* _inven, Time* _time, Trap* _trap)
{
	// 1. 화살표 누를 때 (이동 및 방향회전 -> 벽인지, 함정인지, 길이면 컨티뉴, 아이템, 골이면 다음 스테이지)
	// 2. P키 누를 때 (일시 정지 => 옮겨서 종료할지 계속할지 결정)
	// 3. 숫자키 (아이템 사용, 1 : 망치, 2 : 요정, 3 : 횃불, 4 : 드릴)

	int _userCommand;
	
	if (_kbhit())
	{
		_userCommand = _getch();

		if (_userCommand == 224) // 받은 것이 방향키이면 !
		{
			do
			{
				_userCommand = _getch(); // 방향키 값을 얻을 때까지 고고
			} while (_userCommand == 224);

			switch (_userCommand)
			{
				case UP:
				{
					Move(g_mazePlayBoard, _player, UP, _inven, _trap);
					break;
				}
				case RIGHT:
				{
					Move(g_mazePlayBoard, _player, RIGHT, _inven, _trap);
					break;
				}
				case DOWN:
				{
					Move(g_mazePlayBoard, _player, DOWN, _inven, _trap);
					break;
				}
				case LEFT:
				{
					Move(g_mazePlayBoard, _player, LEFT, _inven, _trap);
					break;
				}
			}
		}
		else // 방향키가 아니라면
		{
			switch (_userCommand)
			{
				case P:
				{
				}
				case alphabet_p:
				{
					PlayEFFECT(EFFECT_PAUSE);
					LONGLONG elapsedTime = PauseInGame(); // 인게임 내에서 잠깐 정지 모드, 퍼즈 한 시간을 다시 추가해준다. 어디다가 ..? 지속시간에.
					_time->stageTotalPauseTime += elapsedTime; // Pause한 시간을 더해준다.

					for (int k = 0; k < 3; k++) // 시간제 아이템 전부 확인
					{
						if (_inven->itemFlag[k] == true) // Pause 전에 아이템 플래그가 켜져 있었다면, 즉, 사용 중이였다면 Pause한 시간을 
							_time->itemStartTime[k] += elapsedTime; // itemStartTime에 Pause한 시간을 더해주어서 나중에 비교할 때 고려되도록 계산한다.
					}
					
					break;
				}
				case ONE:
				{
					// 해머
					if (_inven->item_HammerCnt > 0)
					{
						_inven->Hammer(g_mazePlayBoard, _player, _inven);
					}
					break;
				}
				case TWO:
				{
					// 요정
					if (_inven->item_FairyCnt > 0)
					{
						_time->itemStartTime[TIME_ITEM_FAIRY] = GetTickCount64();
						_inven->BFS_Fairy(g_mazePlayBoard, _player->_pos_y, _player->_pos_x, _player->_goal_y, _player->_goal_x, _inven);
						_inven->item_FairyCnt--;
					}
					break;
				}
				case THREE:
				{
					// 횃불
					if (_inven->item_TorchCnt > 0)
					{
						_time->itemStartTime[TIME_ITEM_TORCH] = GetTickCount64();
						_inven->Torch(_player, _inven);
						_inven->item_TorchCnt--;
					}
					break;
				}
				case FOUR:
				{
					if (_inven->item_DrillCnt > 0)
					{
						_time->itemStartTime[TIME_ITEM_DRILL] = GetTickCount64();
						_inven->itemFlag[TIME_ITEM_DRILL] = true;
						_inven->item_DrillCnt--;
						PlayEFFECT(EFFECT_DRILL);
					}
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}

	while (_kbhit()) // 키 입력 버퍼 클리아
		_getch();
}


LONGLONG WALKING_COUNT = 0;

// Check_Key 함수에서 무빙을 담당하는 함수
void Move(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, int _where, Inventory* _inven, Trap* _trap)
{
	if (_player->_direction != _where) // 지금 플레이어가 바라보고 있는 방향이 다르다면 
	{
		_player->_direction = _where; // 방향만 돌려주고 리턴
		return;
	}
	else
	{
		switch (_where) // 각 방향별 이동이 가능한 곳인지 체크하고 이동한다.
		{
			case UP:
			{
				if (g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] != WALL && g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] != HARD_WALL)
				{
					if (g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] == ITEM_HAMMER) { _inven->item_HammerCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] == ITEM_FAIRY) { _inven->item_FairyCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] == ITEM_TORCH) { _inven->item_TorchCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] == ITEM_DRILL) { _inven->item_DrillCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] == TRAP_ONE)
					{
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
						g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] = PLAYER;
						Draw_PlayBoard(g_mazePlayBoard, g_copyMazePlayBoard, _player, &g_playerDir);
						_trap->CommandTrapOperate();
						_trap->DrawCommandTrapInGame();
					}
					else if (g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] == TRAP_TWO)
					{
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
						g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] = PLAYER;
						Draw_PlayBoard(g_mazePlayBoard, g_copyMazePlayBoard, _player, &g_playerDir);
						_trap->HitterTrapOperate();
						_trap->DrawHitterTrapInGame();
					}

					if (WALKING_COUNT++ % 2 == 0)
						PlayEFFECT(EFFECT_WALKING_LEFT);
					else
						PlayEFFECT(EFFECT_WALKING_RIGHT);

					g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
					_player->_pos_y -= 1;
					g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PLAYER;
				}
				break;
			}
			case RIGHT:
			{
				if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] != WALL && g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] != HARD_WALL)
				{
					if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] == ITEM_HAMMER) { _inven->item_HammerCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] == ITEM_FAIRY) { _inven->item_FairyCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] == ITEM_TORCH) { _inven->item_TorchCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] == ITEM_DRILL) { _inven->item_DrillCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] == TRAP_ONE)
					{
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] = PLAYER;
						Draw_PlayBoard(g_mazePlayBoard, g_copyMazePlayBoard, _player, &g_playerDir);
						_trap->CommandTrapOperate();
						_trap->DrawCommandTrapInGame();
					}
					else if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] == TRAP_TWO)
					{
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] = PLAYER;
						Draw_PlayBoard(g_mazePlayBoard, g_copyMazePlayBoard, _player, &g_playerDir);
						_trap->HitterTrapOperate();
						_trap->DrawHitterTrapInGame();
					}

					if (WALKING_COUNT++ % 2 == 0)
						PlayEFFECT(EFFECT_WALKING_LEFT);
					else
						PlayEFFECT(EFFECT_WALKING_RIGHT);

					g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
					_player->_pos_x += 1;
					g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PLAYER;
				}
				break;
			}
			case DOWN:
			{
				if (g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] != WALL && g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] != HARD_WALL)
				{
					if (g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] == ITEM_HAMMER) { _inven->item_HammerCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] == ITEM_FAIRY) { _inven->item_FairyCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] == ITEM_TORCH) { _inven->item_TorchCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] == ITEM_DRILL) { _inven->item_DrillCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] == TRAP_ONE)
					{
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
						g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] = PLAYER;
						Draw_PlayBoard(g_mazePlayBoard, g_copyMazePlayBoard, _player, &g_playerDir);
						_trap->CommandTrapOperate();
						_trap->DrawCommandTrapInGame();
					}
					else if (g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] == TRAP_TWO)
					{
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
						g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] = PLAYER;
						Draw_PlayBoard(g_mazePlayBoard, g_copyMazePlayBoard, _player, &g_playerDir);
						_trap->HitterTrapOperate();
						_trap->DrawHitterTrapInGame();
					}

					if (WALKING_COUNT++ % 2 == 0)
						PlayEFFECT(EFFECT_WALKING_LEFT);
					else
						PlayEFFECT(EFFECT_WALKING_RIGHT);

					g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
					_player->_pos_y += 1;
					g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PLAYER;
				}
				break;
			}
			case LEFT:
			{
				if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] != WALL && g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] != HARD_WALL)
				{
					if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] == ITEM_HAMMER) { _inven->item_HammerCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] == ITEM_FAIRY) { _inven->item_FairyCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] == ITEM_TORCH) { _inven->item_TorchCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] == ITEM_DRILL) { _inven->item_DrillCnt++; PlayEFFECT(EFFECT_ITEM_PICKUP); }
					else if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] == TRAP_ONE)
					{
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] = PLAYER;
						Draw_PlayBoard(g_mazePlayBoard, g_copyMazePlayBoard, _player, &g_playerDir);
						_trap->CommandTrapOperate();
						_trap->DrawCommandTrapInGame();
					}
					else if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] == TRAP_TWO)
					{
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
						g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] = PLAYER;
						Draw_PlayBoard(g_mazePlayBoard, g_copyMazePlayBoard, _player, &g_playerDir);
						_trap->HitterTrapOperate();
						_trap->DrawHitterTrapInGame();
					}

					if (WALKING_COUNT++ % 2 == 0)
						PlayEFFECT(EFFECT_WALKING_LEFT);
					else
						PlayEFFECT(EFFECT_WALKING_RIGHT);

					g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PATH;
					_player->_pos_x -= 1;
					g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PLAYER;
				}
				break;
			}
		}
	}
}

// Pause 후 지난 시간을 반환한다.
LONGLONG PauseInGame()
{
	char _userCommand;

	LONGLONG nowTime = GetTickCount64();

	int x = 25;
	int y = 16;

	int _posOfChoice = 0;

	SetColor(BLACK, WHITE);

	GoToxy(x, y + 0);  printf("┌───────────────────────────────────────────────┐  ");  // 왠지는 모르겠는데 뒤에 무슨 문자가 있어야지 출력이 잘됨 .. 신기한 컴퓨터의 세상
	GoToxy(x, y + 1);  printf("│                                               │  ");
	GoToxy(x, y + 2);  printf("│                                               │  ");
	GoToxy(x, y + 3);  printf("│                                               │  ");
	GoToxy(x, y + 4);  printf("│                                               │  ");
	GoToxy(x, y + 5);  printf("│            P A U S E  I N  G A M E            │  ");
	GoToxy(x, y + 6);  printf("│                                               │  ");
	GoToxy(x, y + 7);  printf("│                                               │  ");
	GoToxy(x, y + 8);  printf("│                  R E S U M E                  │  ");
	GoToxy(x, y + 9);  printf("│                                               │  ");
	GoToxy(x, y + 10); printf("│                    Q U I T                    │  ");
	GoToxy(x, y + 11); printf("│                                               │  ");
	GoToxy(x, y + 12); printf("│                                               │  ");
	GoToxy(x, y + 13); printf("└───────────────────────────────────────────────┘  ");  // 왠지는 모르겠는데 뒤에 무슨 문자가 있어야지 출력이 잘됨 .. 신기한 컴퓨터의 세상

	GoToxy(x + 7, y + 8 + _posOfChoice); printf("▶");

	_getch();

	bool _enterFlag = false; // Enter키가 눌렸는지 체크

	while (true)
	{
		if (_kbhit())
		{
			_userCommand = _getch();

			switch (_userCommand)
			{
				case UP:
				{
					GoToxy(x + 7, y + 8 + _posOfChoice); printf("  ");

					if (_posOfChoice == 0)
						_posOfChoice = 2;
					else
						_posOfChoice = 0;

					GoToxy(x + 7, y + 8 + _posOfChoice); printf("▶");
					break;
				}
				case DOWN:
				{
					GoToxy(x + 7, y + 8 + _posOfChoice); printf("  ");

					if (_posOfChoice == 2)
						_posOfChoice = 0;
					else
						_posOfChoice = 2;

					GoToxy(x + 7, y + 8 + _posOfChoice); printf("▶");
					break;
				}
				case ENTER:
				{
					_enterFlag = true;

					break;
				}
				default:
				{
					break;
				}
			}
		}

		if (_enterFlag == true)
		{
			if (_posOfChoice == 0)
				break;
			else
				exit(0);
		}
	}

	while (_kbhit()) // 입력 버퍼를 비워준다.
		_getch();

	LONGLONG elapsedTime = GetTickCount64() - nowTime; // Pause 후 지난 시간을 계산한다. 리턴해서 InGame에 적용 후 퍼즈는 시간이 가지 않은 것으로 계산한다.

	system("cls"); //화면 지우고 새로 그림
	Draw_UI_FIXED(g_stageCount); // 고정 UI는 다시 그려준다

	return elapsedTime; // 퍼즈한 시간 리턴해서 메인 시간 시스템에 반영한다.
}

// 현재 상황
// Pause를 걸면 시간은 간다.
// Pause한 시간을 구해서 .. 다시 줘서 ..
// Pause한 만큼 ItemStartTime에 더해준다
// Pause한 만큼