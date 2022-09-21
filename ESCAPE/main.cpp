#include "All_lib.h"
#include "Check_key.h"
#include "Title.h"
#include "Utils.h"
#include "Draw.h"
#include "Time.h"
#include "Trap.h"
#include "Sound.h"

// �ܼ�â ������
// cols 160 lines 60

int g_stageLeftTimes[6] = { 0, TIME_STAGE_ONE,TIME_STAGE_TWO ,TIME_STAGE_THREE ,TIME_STAGE_FOUR ,TIME_STAGE_FIVE }; // �� ���������� ���� �ð��� �����ϴ� �迭
int g_mazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X]; // Ű �Է� �� ��ȣ�ۿ� �����ؼ� �� �迭�� �����ϰ� _copyMazePlayBoard�� ���ؼ� �ٲ� �κи� Draw_PlayBoard�� �����Ѵ�. �׸��� ������ �Ѿ�� �� _copyMazePlayBoard�� ����
int g_copyMazePlayBoard[MAZE_SIZE_Y][MAZE_SIZE_X]; // �ٷ� �� �������� �̷� ���¸� ������.

int g_stageCount = 1; // �������� üũ ���� ����
int g_playerDir;
bool g_stageClear = false; // �� ���������� Ŭ�����ߴ��� üũ�ϴ� ���� ����
int remainTime = 0;

int main()
{
	srand(time(NULL));
    SetCursorType(NOCURSOR); // Ŀ�� ��� ����
    system("mode con cols=160 lines=45 | title ESCAPE"); // �ܼ�â ����s
	
	SoundSystem(); // Sound �迭 Init

	PlayBGM(BGM_TITLE);
	Sleep(2000);
	
	Title(); // Ÿ��Ʋ ȭ���̴�.
	StopBGM(); // Ÿ��Ʋ ȭ�� ������ BGM ����.
	Draw_Story();

	Time* _time = (Time*)malloc(sizeof(Time));
	_time->stageTotalPauseTime = 0;
	Player* _player = (Player*)malloc(sizeof(Player));
	Inventory* _inven = (Inventory*)malloc(sizeof(Inventory));
	Trap* _trap = (Trap*)malloc(sizeof(Trap));

	_player->Init(); // �÷��̾� ��ü �ʱ�ȭ
	g_playerDir = _player->_direction;

	_StageUP:
	// �̰� �Լ�ȭ�ϸ� ������ ..? (�����丵 ������ ���� ����)

	switch (g_stageCount)
	{
		case 1:
			// (1, 21) ���� ��ǥ
			InputStageData(g_mazePlayBoard, g_stageCount, 1, 21, 18, 20, "..\\4_Resources\\Maps\\CircleMap.txt");
			_player->_pos_x = 21;
			_player->_pos_y = 1;
			_player->_goal_x = 18; // 18
			_player->_goal_y = 20; // 20
			_time->stageLeftTime = g_stageLeftTimes[g_stageCount]; // ���������� ���� �ð��� �ҷ��� �����Ѵ�.
			_time->stageStartTime = GetTickCount64(); // ���������� ������ ���� �ð��� �����Ѵ�. �̰� �̿��ؼ� ����� �Ҳ���.
			_inven->Init(); // �������� �Ѿ ������ �κ��丮 �ʱ�ȭ
			PlayBGM(BGM_INGAME_3); // �ΰ��ӿ� BGM ���
			break;
		case 2:
			// (1, 19) ���� ��ǥ
			InputStageData(g_mazePlayBoard, g_stageCount, 1, 19, 19, 19, "..\\4_Resources\\Maps\\HexaMap.txt");
			_player->_pos_x = 19;
			_player->_pos_y = 1;
			_player->_goal_x = 19;
			_player->_goal_y = 19;
			_time->stageLeftTime = g_stageLeftTimes[g_stageCount]; // ���������� ���� �ð��� �ҷ��� �����Ѵ�.
			_time->stageStartTime = GetTickCount64(); // ���������� ������ ���� �ð��� �����Ѵ�. �̰� �̿��ؼ� ����� �Ҳ���.
			_inven->Init(); // �������� �Ѿ ������ �κ��丮 �ʱ�ȭ
			PlayBGM(BGM_INGAME_2); // �ΰ��ӿ� BGM ���
			break;
		case 3:
			// (1, 1) �ϴ� ������ǥ �̰ɷ� ��..
			InputStageData(g_mazePlayBoard, g_stageCount, 1, 1, 39, 39);
			_player->_pos_x = 1;
			_player->_pos_y = 1;
			_player->_goal_x = 39;
			_player->_goal_y = 39;
			_time->stageLeftTime = g_stageLeftTimes[g_stageCount]; // ���������� ���� �ð��� �ҷ��� �����Ѵ�.
			_time->stageStartTime = GetTickCount64(); // ���������� ������ ���� �ð��� �����Ѵ�.�̰� �̿��ؼ� ����� �Ҳ���.
			_inven->Init(); // �������� �Ѿ ������ �κ��丮 �ʱ�ȭ
			PlayBGM(BGM_INGAME_1); // �ΰ��ӿ� BGM ���
			break;
	}

	g_mazePlayBoard[_player->_pos_y][_player->_pos_x] = PLAYER;
	Reset_CopyMazePlayBoard(g_copyMazePlayBoard);

	Draw_UI_FIXED(g_stageCount);

	while (true)
	{
		Check_Key(g_mazePlayBoard, _player, _inven, _time, _trap); // �̰ŷ� g_mazPlayBoard�� �ٲ۴�
		_inven->Checking_Item_Time(_time);

		if (_inven->itemFlag[TIME_ITEM_FAIRY] == false)
			_inven->BFS_Fariy_End(g_mazePlayBoard);

		if (_inven->itemFlag[TIME_ITEM_TORCH] == false)
			_inven->Torch_End(_player, _inven);

		if (_inven->itemFlag[TIME_ITEM_DRILL] == true) // �帱 ������ �÷��װ� �������� ���� �ظӸ� ��� ����ϴ°��� ..
			_inven->HammerForDrill(g_mazePlayBoard, _player);
		
		// Ŭ���� ���� üũ
		if ((_player->_pos_y == _player->_goal_y) && (_player->_pos_x == _player->_goal_x)) // �÷��̾ �� ������ �����ϸ� StageClear �÷��׸� ���ش�
		{
			g_stageClear = true;
			PlayEFFECT(EFFECT_GOAL_SOUND); // �� ���� ���� �� ������ ȿ����
		}

		_time->diffTime = GetTickCount64() -_time->stageStartTime - _time->stageTotalPauseTime; // �������� ��ŸƮ �ð��� �󸶳� �귶�°�, ������ �ð��� ���༭ ��Ȯ�ϰ� ����Ѵ�.

		if ((float)((_time->stageLeftTime - _time->diffTime) / SEC_PER_MILI) <= 0.5f) // ���� �ð��� 0�� ��������� ���� ���� ���� ���μ����� �ǽ��Ѵ�.
		{
			Draw_GameOver();
		}
		else // �ƴϸ� ��� ������ �Ѵ�.
		{
			Reset_CopyMazePlayBoard(g_copyMazePlayBoard);
			Draw_UI_CHANGED(_inven, (LONGLONG)((_time->stageLeftTime - _time->diffTime) / SEC_PER_MILI));
			Draw_PlayBoard(g_mazePlayBoard, g_copyMazePlayBoard, _player, &g_playerDir);
		}

		// �������� Ŭ�����ߴٸ� !
		if (g_stageClear == true) // �������� Ŭ���� �÷��װ� ���������� �������� �� ���μ����� �����Ѵ�.
		{
			g_stageClear = false; // ���� ���� ���ִ°� ���� ����.

			_time->stageTotalPauseTime = 0; // �������� ��Ż PauseTime�� �ʱ�ȭ. �������� �Ѿ�ϱ� !
			StopEFFECT();
			StopBGM();

			if (g_stageCount < ALL_STAGE_COUNT) // ���� ������ ���������� �������� ���� ���� ���� ���������� �Ѿ�°ž� !
			{
				Draw_StageUp();
				
				g_stageCount++; // stage ī��Ʈ ��
				remainTime += (int)((_time->stageLeftTime - _time->diffTime) / SEC_PER_MILI);
				goto _StageUP; // ���� switch �� �ö�
			}
			else // �غ�� ��� ���������� Ŭ�����Ͽ����ϴ�.
			{ 
				remainTime += (int)((_time->stageLeftTime - _time->diffTime) / SEC_PER_MILI);
				Draw_GameClear(remainTime); // ��� �������� Ŭ���� ! ��ŷ ������� ���μ����� �����Ѵ�.
			}
		}
	}
}