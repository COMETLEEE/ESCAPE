#pragma once
#include "All_lib.h"
#include "Utils.h"
#include "Player.h"
#include "Time.h"

struct Inventory
{
	int item_HammerCnt;
	int item_FairyCnt;
	int item_TorchCnt;
	int item_DrillCnt;

	void Hammer(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, Inventory* _inven);
	void HammerForDrill(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player);
	void BFS_Fairy(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int playerX, int playerY, int goalX, int goalY, Inventory* inven);
	void Torch(Player* _player, Inventory* inven);
	void Drill(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int playerX, int playerY);
	void Checking_Item_Time(Time* _time);
	void BFS_Fariy_End(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X]);
	void Torch_End(Player* _player, Inventory* inven);

	bool itemFlag[3] = { false };

	void Init();
};

void BFS(int _mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int a, int b, int row, int col);