#include "All_lib.h"
#include "Check_key.h"
#include "Title.h"
#include "Utils.h"
#include "Draw.h"
#include "Time.h"
#include "Trap.h"
#include "Sound.h"

// 콘솔창 사이즈
// cols 160 lines 60

int g_stageLeftTimes[6] = { 0, TIME_STAGE_ONE,TIME_STAGE_TWO ,TIME_STAGE_THREE ,TIME_STAGE_FOUR ,TIME_STAGE_FIVE }; // 각 스테이지별 제한 시간을 관리하는 배열
int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X]; // 키 입력 후 상호작용 관련해서 이 배열을 변경하고 _copyMazePlayBoard와 비교해서 바뀐 부분만 Draw_PlayBoard에 적용한다. 그리고 프레임 넘어가기 전 _copyMazePlayBoard에 복사
int g_copyMazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X]; // 바로 전 프레임의 미로 상태를 저장함.

int g_stageCount = 1; // 스테이지 체크 전역 변수
int g_playerDir;
bool g_stageClear = false; // 그 스테이지를 클리어했는지 체크하는 전역 변수
int remainTime = 0;

int main()
{
	srand(time(NULL));
    SetCursorType(NOCURSOR); // 커서 모드 셋팅
    system("mode con cols=160 lines=45 | title ESCAPE"); // 콘솔창 셋팅s
	
	SoundSystem(); // Sound 계열 Init

	PlayBGM(BGM_TITLE);
	Sleep(2000);
	
	Title(); // 타이틀 화면이다.
	StopBGM(); // 타이틀 화면 끝나면 BGM 끈다.
	Draw_Story();

	Time* _time = (Time*)malloc(sizeof(Time));
	_time->stageTotalPauseTime = 0;
	Player* _player = (Player*)malloc(sizeof(Player));
	Inventory* _inven = (Inventory*)malloc(sizeof(Inventory));
	Trap* _trap = (Trap*)malloc(sizeof(Trap));

	_player->Init(); // 플레이어 객체 초기화
	g_playerDir = _player->_direction;

	_StageUP:
	// 이거 함수화하면 좋을듯 ..? (리팩토링 과정에 넣을 에정)

	switch (g_stageCount)
	{
		case 1:
			// (1, 21) 시작 좌표
			InputStageData(g_mazePlayBoard, g_stageCount, 1, 21, 18, 20, "..\\4_Resources\\Maps\\CircleMap.txt");
			_player->_pos_x = 21;
			_player->_pos_y = 1;
			_player->_goal_x = 18; // 18
			_player->_goal_y = 20; // 20
			_time->stageLeftTime = g_stageLeftTimes[g_stageCount]; // 스테이지별 제한 시간을 불러서 저장한다.
			_time->stageStartTime = GetTickCount64(); // 스테이지가 시작할 때의 시각을 저장한다. 이걸 이용해서 계산을 할꺼야.
			_inven->Init(); // 스테이지 넘어갈 때마다 인벤토리 초기화
			PlayBGM(BGM_INGAME_3); // 인게임용 BGM 재생
			break;
		case 2:
			// (1, 19) 시작 좌표
			InputStageData(g_mazePlayBoard, g_stageCount, 1, 19, 19, 19, "..\\4_Resources\\Maps\\HexaMap.txt");
			_player->_pos_x = 19;
			_player->_pos_y = 1;
			_player->_goal_x = 19;
			_player->_goal_y = 19;
			_time->stageLeftTime = g_stageLeftTimes[g_stageCount]; // 스테이지별 제한 시간을 불러서 저장한다.
			_time->stageStartTime = GetTickCount64(); // 스테이지가 시작할 때의 시각을 저장한다. 이걸 이용해서 계산을 할꺼야.
			_inven->Init(); // 스테이지 넘어갈 때마다 인벤토리 초기화
			PlayBGM(BGM_INGAME_2); // 인게임용 BGM 재생
			break;
		case 3:
			// (1, 1) 일단 시작좌표 이걸로 했..
			InputStageData(g_mazePlayBoard, g_stageCount, 1, 1, 39, 39);
			_player->_pos_x = 1;
			_player->_pos_y = 1;
			_player->_goal_x = 39;
			_player->_goal_y = 39;
			_time->stageLeftTime = g_stageLeftTimes[g_stageCount]; // 스테이지별 제한 시간을 불러서 저장한다.
			_time->stageStartTime = GetTickCount64(); // 스테이지가 시작할 때의 시각을 저장한다.이걸 이용해서 계산을 할꺼야.
			_inven->Init(); // 스테이지 넘어갈 때마다 인벤토리 초기화
			PlayBGM(BGM_INGAME_1); // 인게임용 BGM 재생
			break;
	}

	g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PLAYER;
	Reset_CopyMazePlayBoard(g_copyMazePlayBoard);

	Draw_UI_FIXED(g_stageCount);

	while (true)
	{
		Check_Key(g_mazePlayBoard, _player, _inven, _time, _trap); // 이거로 g_mazPlayBoard를 바꾼다
		_inven->Checking_Item_Time(_time);

		if (_inven->itemFlag[TIME_ITEM_FAIRY] == false)
			_inven->BFS_Fariy_End(g_mazePlayBoard);

		if (_inven->itemFlag[TIME_ITEM_TORCH] == false)
			_inven->Torch_End(_player, _inven);

		if (_inven->itemFlag[TIME_ITEM_DRILL] == true) // 드릴 아이템 플래그가 켜져있을 때는 해머를 계속 사용하는거임 ..
			_inven->HammerForDrill(g_mazePlayBoard, _player);
		
		// 클리어 조건 체크
		if ((_player->_pos_y == _player->_goal_y) && (_player->_pos_x == _player->_goal_x)) // 플레이어가 골 지역에 도착하면 StageClear 플래그를 켜준다
		{
			g_stageClear = true;
			PlayEFFECT(EFFECT_GOAL_SOUND); // 골 지역 도착 시 나오는 효과음
		}

		_time->diffTime = GetTickCount64() -_time->stageStartTime - _time->stageTotalPauseTime; // 스테이지 스타트 시간이 얼마나 흘렀는가, 퍼즈한 시간도 빼줘서 정확하게 계산한다.

		if ((float)((_time->stageLeftTime - _time->diffTime) / SEC_PER_MILI) <= 0.5f) // 남은 시간이 0에 가까워지면 이제 게임 오버 프로세스를 실시한다.
		{
			Draw_GameOver();
		}
		else // 아니면 계속 게임을 한다.
		{
			Reset_CopyMazePlayBoard(g_copyMazePlayBoard);
			Draw_UI_CHANGED(_inven, (LONGLONG)((_time->stageLeftTime - _time->diffTime) / SEC_PER_MILI));
			Draw_PlayBoard(g_mazePlayBoard, g_copyMazePlayBoard, _player, &g_playerDir);
		}

		// 스테이지 클리어했다면 !
		if (g_stageClear == true) // 스테이지 클리어 플래그가 켜져있으면 스테이지 업 프로세스에 진입한다.
		{
			g_stageClear = false; // 가기 전에 꺼주는거 잊지 말고.

			_time->stageTotalPauseTime = 0; // 스테이지 토탈 PauseTime을 초기화. 스테이지 넘어가니까 !
			StopEFFECT();
			StopBGM();

			if (g_stageCount < ALL_STAGE_COUNT) // 현재 구성된 스테이지의 갯수보다 작을 때만 다음 스테이지로 넘어가는거야 !
			{
				Draw_StageUp();
				
				g_stageCount++; // stage 카운트 업
				remainTime += (int)((_time->stageLeftTime - _time->diffTime) / SEC_PER_MILI);
				goto _StageUP; // 위의 switch 로 올라감
			}
			else // 준비된 모든 스테이지를 클리어하였습니다.
			{ 
				remainTime += (int)((_time->stageLeftTime - _time->diffTime) / SEC_PER_MILI);
				Draw_GameClear(remainTime); // 모든 스테이지 클리어 ! 랭킹 도장찍는 프로세스로 진입한다.
			}
		}
	}
}