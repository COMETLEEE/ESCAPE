#pragma once
#include "All_lib.h"
#include "Utils.h"
#include "Player.h"
#include "Item.h"
#include "Ranking.h"

// �������� �׸��� �Լ� (�ٲ� �κи� �ٲ㼭 �׸���.)
void Draw_PlayBoard(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int g_copyMazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, int* _playerDir);

// UI�� �׸��� �Լ� (Ű ����, ������ �κ��丮)
void Draw_UI_FIXED(int g_stageCount);
void Draw_UI_CHANGED(Inventory* _inven, ULONGLONG _leftSec);

// ���������� ����Ǿ��� ���� ���������� �Ѿ ���� �ִϸ��̼�
void Draw_StageUp();

// ��� ���������� Ŭ�����Ͽ��� ���� Ŭ����, ��ŷ �ۼ� ���μ����� �����Ѵ�.
void Draw_GameClear(int remainTime);

// �ð��� �ٵǾ ���� ���� ���μ����� �����Ѵ�.
void Draw_GameOver();

// Randomized DFS�� �̿��ؼ� ���� �̷θ� �����Ѵ�. InputStageData�� ���ӵ� �Լ�
void MakeMapByRandomizedDFS(int nowY, int nowX, int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X]);

// �������� ���� ������ �����͸� 2���� �迭�� ��ǲ�ϴ� �Լ�
void InputStageData(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int stageCnt, int startX, int startY, int GoalX, int GoalY, string _address = "");

// ���纻 �ʱ�ȭ�ϴ� �Լ�
void Reset_CopyMazePlayBoard(int g_copyMazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X]);

// ���丮
void Draw_Story();