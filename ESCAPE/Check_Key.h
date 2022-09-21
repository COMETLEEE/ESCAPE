#pragma once
#include "Utils.h"
#include "Player.h"
#include "Item.h"
#include "Time.h"
#include "Trap.h"
#include "Draw.h"

// 키 입력을 확인하여 각각의 키에 따라서 프로세스를 진행한다. (P : Pause() 함수 / 방향키 : 캐릭터가 바라보고 있는 방향을 방향키와 일치하게 변경 후 범위 및 이동 가능 여부 체크 후 캐릭터 이동 / 아이템 사용 : )
void Check_Key(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, Inventory* _inven, Time* _time, Trap* _trap);

// Check_Key 안에서 무빙을 담당하는 함수
void Move(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, int _where, Inventory* _inven, Trap* _trap);

// Check_Key 안에서 Pause를 담당하는 함수, Pause한 시간을 반환하는 함수이다.
LONGLONG PauseInGame();