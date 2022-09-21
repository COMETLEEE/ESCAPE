#include "All_lib.h"
#include "Check_Key.h"
#include "Utils.h"
#include "Sound.h"

extern int g_copyMazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X];
extern int g_playerDir;
extern int g_stageCount;

// Ű �Է��� Ȯ���Ͽ� ������ Ű�� ���� ���μ����� �����Ѵ�. (P : Pause() �Լ� / ����Ű : ĳ���Ͱ� �ٶ󺸰� �ִ� ������ ����Ű�� ��ġ�ϰ� ���� �� ���� �� �̵� ���� ���� üũ �� ĳ���� �̵� / ������ ��� : )
void Check_Key(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, Inventory* _inven, Time* _time, Trap* _trap)
{
	// 1. ȭ��ǥ ���� �� (�̵� �� ����ȸ�� -> ������, ��������, ���̸� ��Ƽ��, ������, ���̸� ���� ��������)
	// 2. PŰ ���� �� (�Ͻ� ���� => �Űܼ� �������� ������� ����)
	// 3. ����Ű (������ ���, 1 : ��ġ, 2 : ����, 3 : ȶ��, 4 : �帱)

	int _userCommand;
	
	if (_kbhit())
	{
		_userCommand = _getch();

		if (_userCommand == 224) // ���� ���� ����Ű�̸� !
		{
			do
			{
				_userCommand = _getch(); // ����Ű ���� ���� ������ ���
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
		else // ����Ű�� �ƴ϶��
		{
			switch (_userCommand)
			{
				case P:
				{
				}
				case alphabet_p:
				{
					PlayEFFECT(EFFECT_PAUSE);
					LONGLONG elapsedTime = PauseInGame(); // �ΰ��� ������ ��� ���� ���, ���� �� �ð��� �ٽ� �߰����ش�. ���ٰ� ..? ���ӽð���.
					_time->stageTotalPauseTime += elapsedTime; // Pause�� �ð��� �����ش�.

					for (int k = 0; k < 3; k++) // �ð��� ������ ���� Ȯ��
					{
						if (_inven->itemFlag[k] == true) // Pause ���� ������ �÷��װ� ���� �־��ٸ�, ��, ��� ���̿��ٸ� Pause�� �ð��� 
							_time->itemStartTime[k] += elapsedTime; // itemStartTime�� Pause�� �ð��� �����־ ���߿� ���� �� ����ǵ��� ����Ѵ�.
					}
					
					break;
				}
				case ONE:
				{
					// �ظ�
					if (_inven->item_HammerCnt > 0)
					{
						_inven->Hammer(g_mazePlayBoard, _player, _inven);
					}
					break;
				}
				case TWO:
				{
					// ����
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
					// ȶ��
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

	while (_kbhit()) // Ű �Է� ���� Ŭ����
		_getch();
}


LONGLONG WALKING_COUNT = 0;

// Check_Key �Լ����� ������ ����ϴ� �Լ�
void Move(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, int _where, Inventory* _inven, Trap* _trap)
{
	if (_player->_direction != _where) // ���� �÷��̾ �ٶ󺸰� �ִ� ������ �ٸ��ٸ� 
	{
		_player->_direction = _where; // ���⸸ �����ְ� ����
		return;
	}
	else
	{
		switch (_where) // �� ���⺰ �̵��� ������ ������ üũ�ϰ� �̵��Ѵ�.
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

// Pause �� ���� �ð��� ��ȯ�Ѵ�.
LONGLONG PauseInGame()
{
	char _userCommand;

	LONGLONG nowTime = GetTickCount64();

	int x = 25;
	int y = 16;

	int _posOfChoice = 0;

	SetColor(BLACK, WHITE);

	GoToxy(x, y + 0);  printf("��������������������������������������������������������������������������������������������������  ");  // ������ �𸣰ڴµ� �ڿ� ���� ���ڰ� �־���� ����� �ߵ� .. �ű��� ��ǻ���� ����
	GoToxy(x, y + 1);  printf("��                                               ��  ");
	GoToxy(x, y + 2);  printf("��                                               ��  ");
	GoToxy(x, y + 3);  printf("��                                               ��  ");
	GoToxy(x, y + 4);  printf("��                                               ��  ");
	GoToxy(x, y + 5);  printf("��            P A U S E  I N  G A M E            ��  ");
	GoToxy(x, y + 6);  printf("��                                               ��  ");
	GoToxy(x, y + 7);  printf("��                                               ��  ");
	GoToxy(x, y + 8);  printf("��                  R E S U M E                  ��  ");
	GoToxy(x, y + 9);  printf("��                                               ��  ");
	GoToxy(x, y + 10); printf("��                    Q U I T                    ��  ");
	GoToxy(x, y + 11); printf("��                                               ��  ");
	GoToxy(x, y + 12); printf("��                                               ��  ");
	GoToxy(x, y + 13); printf("��������������������������������������������������������������������������������������������������  ");  // ������ �𸣰ڴµ� �ڿ� ���� ���ڰ� �־���� ����� �ߵ� .. �ű��� ��ǻ���� ����

	GoToxy(x + 7, y + 8 + _posOfChoice); printf("��");

	_getch();

	bool _enterFlag = false; // EnterŰ�� ���ȴ��� üũ

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

					GoToxy(x + 7, y + 8 + _posOfChoice); printf("��");
					break;
				}
				case DOWN:
				{
					GoToxy(x + 7, y + 8 + _posOfChoice); printf("  ");

					if (_posOfChoice == 2)
						_posOfChoice = 0;
					else
						_posOfChoice = 2;

					GoToxy(x + 7, y + 8 + _posOfChoice); printf("��");
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

	while (_kbhit()) // �Է� ���۸� ����ش�.
		_getch();

	LONGLONG elapsedTime = GetTickCount64() - nowTime; // Pause �� ���� �ð��� ����Ѵ�. �����ؼ� InGame�� ���� �� ����� �ð��� ���� ���� ������ ����Ѵ�.

	system("cls"); //ȭ�� ����� ���� �׸�
	Draw_UI_FIXED(g_stageCount); // ���� UI�� �ٽ� �׷��ش�

	return elapsedTime; // ������ �ð� �����ؼ� ���� �ð� �ý��ۿ� �ݿ��Ѵ�.
}

// ���� ��Ȳ
// Pause�� �ɸ� �ð��� ����.
// Pause�� �ð��� ���ؼ� .. �ٽ� �༭ ..
// Pause�� ��ŭ ItemStartTime�� �����ش�
// Pause�� ��ŭ