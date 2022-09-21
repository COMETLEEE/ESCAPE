#include "All_lib.h"
#include "Item.h"
#include "Utils.h"
#include "Sound.h"

// 요정 아이템에 필요한 변수와 BFS함수
int dx[] = { 0,0 ,1 ,-1 };
int dy[] = { 1,-1,0,0 };
bool visit[MAZE_SIZE_Y][MAZE_SIZE_X - 1];
pair<int, int> pa[MAZE_SIZE_Y][MAZE_SIZE_X - 1];

ULONGLONG LimitTimeOfItem[3] = { TIME_FAIRY, TIME_TORCH, TIME_DRILL };

void Inventory::Init()
{
    this->item_DrillCnt = 0;
    this->item_FairyCnt = 0;
    this->item_HammerCnt = 0;
    this->item_TorchCnt = 0;
}

// 해머 전용 해머
void Inventory::Hammer(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player, Inventory* _inven)
{
    // 플레이어가 바라보는 방향을 판단해서 그 방향 앞에있는 WALL 을 부수고 PATH 상태로 만든다.
    
    switch (_player->_direction)
    {
        case UP:
        {
            if (g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] == WALL)
            {
                PlayEFFECT(EFFECT_HAMMER); // 해머 사운드를 출력한다.
				_inven->item_HammerCnt--;
                g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] = PATH;
            }
        }
        break;
        case LEFT:
        {
            if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] == WALL)
            {
				PlayEFFECT(EFFECT_HAMMER); // 해머 사운드를 출력한다.
				_inven->item_HammerCnt--;
                g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] = PATH;
            }
        }
        break;
        case RIGHT:
        {
            if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] == WALL)
            {
                PlayEFFECT(EFFECT_HAMMER); // 해머 사운드를 출력한다.
				_inven->item_HammerCnt--;
                g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] = PATH;
            }
        }
        break;
        case DOWN:
        {
            if (g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] == WALL)
            {
				PlayEFFECT(EFFECT_HAMMER); // 해머 사운드를 출력한다.
				_inven->item_HammerCnt--;
                g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] = PATH;
            }
        }
        break;
    }
}

// 드릴 전용 해머
void Inventory::HammerForDrill(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], Player* _player)
{
	switch (_player->_direction)
	{
		case UP:
		{
			if (g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] == WALL)
			{
				PlayEFFECT(EFFECT_HAMMER); // 해머 사운드를 출력한다.
				g_mazePlayBoard[_player->_pos_y - 1][_player->_pos_x] = PATH;
			}
		}
		break;
		case LEFT:
		{
			if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] == WALL)
			{
				PlayEFFECT(EFFECT_HAMMER); // 해머 사운드를 출력한다.
				g_mazePlayBoard[_player->_pos_y][_player->_pos_x - 1] = PATH;
			}
		}
		break;
		case RIGHT:
		{
			if (g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] == WALL)
			{
				PlayEFFECT(EFFECT_HAMMER); // 해머 사운드를 출력한다.
				g_mazePlayBoard[_player->_pos_y][_player->_pos_x + 1] = PATH;
			}
		}
		break;
		case DOWN:
		{
			if (g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] == WALL)
			{
				PlayEFFECT(EFFECT_HAMMER); // 해머 사운드를 출력한다.
				g_mazePlayBoard[_player->_pos_y + 1][_player->_pos_x] = PATH;
			}
		}
		break;
	}
}

// BFS_Fairy 함수에서 불러오는 겁니당
void BFS(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int a, int b, int row, int col)
{
    queue<pair<int, int>> q;
    q.push({ a, b });
    fill(&visit[0][0], &visit[MAZE_SIZE_Y - 1][MAZE_SIZE_X - 1], false);
    visit[a][b] = true;

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx <= row && ny >= 0 && ny <= col && visit[nx][ny] == 0)
            {
                if (g_mazePlayBoard[nx][ny] == PATH || g_mazePlayBoard[nx][ny] == ITEM_HAMMER || g_mazePlayBoard[nx][ny] == ITEM_FAIRY || g_mazePlayBoard[nx][ny] == ITEM_TORCH || g_mazePlayBoard[nx][ny] == ITEM_DRILL || g_mazePlayBoard[nx][ny] == GOAL || g_mazePlayBoard[nx][ny] == TRAP_ONE || g_mazePlayBoard[nx][ny] == TRAP_TWO)
                {
                    q.push((make_pair(nx, ny)));
                    visit[nx][ny] = 1;
                    pa[nx][ny] = { x, y };
                }
            }
        }
    }

    printf("\n");
}

// 이 함수를 써야합니다!
// BFS_Fairy(출발 좌표x, 출발 좌표y, 도착 좌표x, 도착 좌표y);
void Inventory::BFS_Fairy(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X], int playerX, int playerY, int goalX, int goalY, Inventory* inven)
{
    inven->itemFlag[0] = true;
    vector<pair<int, int>> v;

    // ex) 0, 18(출발 좌표)  y크기 x크기   
    BFS(g_mazePlayBoard, playerX, playerY, MAZE_SIZE_Y, MAZE_SIZE_X);

    // ex) ->   39, 20(도착 좌표)
    int curx = goalX, cury = goalY;

    while (true)
    {
        v.push_back(make_pair(curx, cury));
        if (curx == playerX && cury == playerY) break; // 출발 좌표
        int nx = pa[curx][cury].first;
        int ny = pa[curx][cury].second;
        curx = nx;
        cury = ny;
    }

    //GoToxy(0, 0); // gotoxy 위치 잘 조정해야함 !

    // 아이템일 수도 있어서 PATH인 부분만 FAIRY_WAY 로 바꾼다.
    
    PlayEFFECT(EFFECT_FAIRY); // 페어리 사운드를 출력한다.

    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (g_mazePlayBoard[v[i].first][v[i].second] == PATH)
        {
            g_mazePlayBoard[v[i].first][v[i].second] = FAIRY_WAY;
        }
    }

    g_mazePlayBoard[playerX][playerY] = PLAYER;
}

void Inventory::Checking_Item_Time(Time* _time)
{
    LONGLONG nowTime = GetTickCount64();

    for (int k = 0; k < 3; k++)
    {
        if ((this->itemFlag[k]) && (nowTime - _time->itemStartTime[k] >= LimitTimeOfItem[k]))
        {
            this->itemFlag[k] = false;
        }
    }
}

void Inventory::BFS_Fariy_End(int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X])
{
    for (int y = 0; y < MAZE_SIZE_Y; y++)
    {
        for (int x = 0; x < MAZE_SIZE_X; x++)
        {
            if (g_mazePlayBoard[y][x] == FAIRY_WAY)
            {
                g_mazePlayBoard[y][x] = PATH;
            }
        }
    }
}

void Inventory::Torch(Player* _player, Inventory* inven)
{
    inven->itemFlag[1] = true;
    PlayEFFECT(EFFECT_TORCH);
    _player->_eyeSight = 10;
}

void Inventory::Torch_End(Player* _player, Inventory* inven)
{
    inven->itemFlag[1] = false;
    _player->_eyeSight = 3;
}