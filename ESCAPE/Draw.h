#pragma once
#include "All_lib.h"
#include "Utils.h"
#include "Player.h"
#include "Item.h"
#include "Ranking.h"

// 게임판을 그리는 함수 (바뀐 부분만 바꿔서 그린다.)
void Draw_PlayBoard(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int g_copyMazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, int* _playerDir);

// UI를 그리는 함수 (키 도움말, 아이템 인벤토리)
void Draw_UI_FIXED(int g_stageCount);
void Draw_UI_CHANGED(Inventory* _inven, ULONGLONG _leftSec);

// 스테이지가 종료되었고 다음 스테이지로 넘어갈 때의 애니메이션
void Draw_StageUp();

// 모든 스테이지를 클리어하였고 게임 클리어, 랭킹 작성 프로세스로 진입한다.
void Draw_GameClear(int remainTime);

// 시간이 다되어서 게임 오버 프로세스로 진입한다.
void Draw_GameOver();

// Randomized DFS를 이용해서 랜덤 미로를 형성한다. InputStageData에 종속될 함수
void MakeMapByRandomizedDFS(int nowY, int nowX, int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X]);

// 스테이지 별로 지정된 데이터를 2차원 배열에 인풋하는 함수
void InputStageData(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int stageCnt, int startX, int startY, int GoalX, int GoalY, string _address = "");

// 복사본 초기화하는 함수
void Reset_CopyMazePlayBoard(int g_copyMazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X]);

// 스토리
void Draw_Story();