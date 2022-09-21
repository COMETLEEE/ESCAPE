#pragma once
#include "Utils.h"
#include "Player.h"
#include "Item.h"
#include "Time.h"
#include "Trap.h"
#include "Draw.h"

// Ű �Է��� Ȯ���Ͽ� ������ Ű�� ���� ���μ����� �����Ѵ�. (P : Pause() �Լ� / ����Ű : ĳ���Ͱ� �ٶ󺸰� �ִ� ������ ����Ű�� ��ġ�ϰ� ���� �� ���� �� �̵� ���� ���� üũ �� ĳ���� �̵� / ������ ��� : )
void Check_Key(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, Inventory* _inven, Time* _time, Trap* _trap);

// Check_Key �ȿ��� ������ ����ϴ� �Լ�
void Move(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, int _where, Inventory* _inven, Trap* _trap);

// Check_Key �ȿ��� Pause�� ����ϴ� �Լ�, Pause�� �ð��� ��ȯ�ϴ� �Լ��̴�.
LONGLONG PauseInGame();