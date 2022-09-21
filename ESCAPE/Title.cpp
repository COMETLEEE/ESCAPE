#include "All_lib.h"
#include "Title.h"
#include "Utils.h"
#include "Sound.h"

// 콘솔 프로그램 실행 후 가장 먼저 뜨는 화면, 게임의 타이틀을 보임.
// 1. Maze Runner (가칭) 렌더링 후 'PRESS ANY KEY' 깜빡깜빡.
// 어떤 키든 입력이 확인되면 함수 종료 후 게임 진입.
void Title()
{
Fir: // How To Play가 끝나면 여기로 다시 돌아와서 Title함수를 다시 시행한다.
	// 타이틀, 삼각형이 시간에 따라 깜빡거릴 수 있도록 시간 변수 저장, 모듈러 연산을 통해 깜빡거림 구현
	// 게임의 타이틀을 콘솔 중앙에 렌더링 (Escape)
	// 좌측 하단에 'Game Start, How to Play, Exit' 선택지 및 선택 화살표 -> 각각에 대하여 위치를 저장하고, 입력 시 함수 발동
	int x = 5; int y = 5;
	
	int _frames = 0; // 프레임을 재는 변수
	char _command = 0; // 유저 커맨드를 받는 변수

	int _posOfChoice = 0; // 선택 화살표의 위치를 나타내는 변수
	bool _enterFlag = false; // Enter가 눌려 선택 화살표의 위치에 따라 분기를 나눠야 한다는 신호
	bool _startFlag = false; // 게임 스타트를 알리는 신호

	// 사운드 출력 요망
	SetColor(BLACK, SKY);
	GoToxy(x, y    ); printf("        ####################  ####################    ##################      ################      ##################    ##################"); Sleep(100);
	GoToxy(x, y + 2); printf("       ###################  ######################  #####################   ##################    ####################   ##################"); Sleep(100);
	GoToxy(x, y + 4); printf("      ######               #####                  ######          ######  ######        ######   ######        ######   ######"); Sleep(100);
	GoToxy(x, y + 6); printf("     #################    ####################   ######                  ######        ######   ######        ######   #################"); Sleep(100);
	GoToxy(x, y + 8); printf("    ##################    ####################  ######                  ####################   ####################   #################"); Sleep(100);
	GoToxy(x, y + 10); printf("   #####                              #######  ######        ######    ####################   ####################   #######"); Sleep(100);
	GoToxy(x, y + 12); printf("  ###################  #####################   ####################   ######        ######   ######                 ##################"); Sleep(100);
	GoToxy(x, y + 14); printf(" ###################  ####################     ###################   ######        ######   ######                 ##################"); Sleep(100);

	SetColor(BLACK, WHITE);
	GoToxy(x + 29, y + 27 + _posOfChoice); printf("▶");
	GoToxy(x + 31, y + 27); printf("GAME START");
	GoToxy(x + 31, y + 29); printf("HOW TO PLAY");
	GoToxy(x + 31, y + 31); printf("RANKING");
	GoToxy(x + 31, y + 33); printf("EXIT");

	while (_kbhit()) // 모든 입력 버퍼를 초기화한다.
		_getch();

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
		{
			_command = _getch();
			switch (_command)
			{
				case ENTER:
				{
					_enterFlag = true;
					break;
				}
				case UP:
				{
					GoToxy(x + 29, y + 27 + _posOfChoice); printf("  ");

					if (_posOfChoice == 0)
						_posOfChoice = 6;
					else
						_posOfChoice -= 2;

					PlayEFFECT(EFFECT_MENU_MOVE);
					GoToxy(x + 29, y + 27 + _posOfChoice); printf("▶");
					break;
				}
				case DOWN:
				{
					GoToxy(x + 29, y + 27 + _posOfChoice); printf("  ");

					if (_posOfChoice == 6)
						_posOfChoice = 0;
					else
						_posOfChoice += 2;

					PlayEFFECT(EFFECT_MENU_MOVE);
					GoToxy(x + 29, y + 27 + _posOfChoice); printf("▶");
					break;
				}
				default:
				{
					break;
				}
			}

			if (_enterFlag)
			{
				switch (_posOfChoice)
				{
					case 0: // GAME START
					{
						_startFlag = true;
						break;
					}
					case 2: // HOW TO PLAY
					{
						HowToPlay();
						goto Fir; // 다시 Title() 함수의 처음으로 돌아간다.
						_enterFlag = false;
						break;
					}
					case 4: // Ranking
					{
						View_Ranking();
						goto Fir;
						break;
					}
					case 6: // EXIT
					{
						exit(0);
					}
				}
			}
		}

		if (_frames % 200 == 0) // 200 프레임마다 띄움
		{
			GoToxy(x + 26, y + 21); printf("PRESS ENTER KEY TO SELECT MENU"); // 반짝거리게 하고 싶은 욕심
		}
		else if ((_frames % 200 - 100) == 0) // 100 프레임 간격으로 지움 (1초 + @) 
		{
			GoToxy(x + 26, y + 21); printf("                              "); // 반짝거리게 하고 싶은 욕심
		}

		if (_startFlag)
			break;

		Sleep(10); // 0.01초 단위로 메인 화면 프레임 실행
	}

	while (_kbhit()) // 키 입력 버퍼를 비움
		_getch();

	system("cls");
	// 키 입력을 받았으면
	// 확인 (Enter이면 해당 위치 선택, 위, 아래 화살표면 그 쪽으로 이동할 수 있는지 확인하고 이동)
}

void HowToPlay()
{
	int x = 5; int y = 4;

	int _frames = 0;

	system("cls");

	GoToxy(x + 29, y); printf("○ HOW TO PLAY ○"); Sleep(50);
	GoToxy(x, y + 3);  printf("※ 게임 목표 : 여러가지 아이템을 사용하고 함정을 피해 제한시간 내에 주어진 미로들을 탈출하라 !"); Sleep(50);

	GoToxy(x, y + 6);  printf("- 조작법"); Sleep(50);
	GoToxy(x, y + 8);  printf("← : 좌측으로 회전 및 이동 / → : 우측으로 회전 및 이동 / ↑ : 위로 회전 및 이동 / ↓ : 아래로 회전 및 이동"); Sleep(50);
	GoToxy(x, y + 10); printf("1 : 망치 아이템 사용 / 2 : 요정 아이템 사용 / 3 : 횃불 아이템 사용 / 4 : 드릴 아이템 사용"); Sleep(50);
	GoToxy(x, y + 12); printf("P : PAUSE / Enter : 해당 옵션 선택"); Sleep(50);

	GoToxy(x, y + 15); printf("- 아이템"); Sleep(50);
	GoToxy(x, y + 17); printf("망치 (◆): 플레이어 기준 한 칸 앞에 벽이 있으면 사용 시 그 벽을 파괴합니다."); Sleep(50);
	GoToxy(x, y + 19); printf("요정 (◈): 사용시 플레이어의 위치를 기준으로 도착지까지의 최단 거리를 빨간 불빛으로 안내합니다."); Sleep(50);
	GoToxy(x, y + 21); printf("횃불 (♨) : 플레이어 주변의 시야를 한 층 더 넓힙니다."); Sleep(50);
	GoToxy(x, y + 23); printf("드릴 (★): 사용 시 일정 시간동안 플레이어 앞에 있는 모든 벽과 함정들을 파괴하면서 앞으로 전진합니다."); Sleep(50);

	GoToxy(x, y + 26); printf("- 함정 (※)"); Sleep(50);
	GoToxy(x, y + 28); printf("미로 여기 저기에 함정이 있습니다. 함정을 밟을 시 벌칙을 수행해야 합니다."); Sleep(50);
	GoToxy(x, y + 30); printf("커맨드 벌칙 : 주어진 화살표와 동일하게 화살표를 입력하면 해제됩니다."); Sleep(50);
	GoToxy(x, y + 32); printf("타자연습 벌칙 : 주어진 문장과 동일하게 입력하면 해제됩니다."); Sleep(50);

	while (_kbhit()) // 키 입력 버퍼를 비움
		_getch();

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 프레임마다 띄움
		{
			GoToxy(x + 26, y + 36); printf("PRESS ANY KEY TO GO TO TITLE"); // 반짝거리게 하고 싶은 욕심
		}
		else if ((_frames % 200 - 100) == 0) // 100 프레임 간격으로 지움 (1초 + @) 
		{
			GoToxy(x + 26, y + 36); printf("                              "); // 반짝거리게 하고 싶은 욕심
		}

		Sleep(10);
	}

	while (_kbhit()) // 키 입력 버퍼를 비움
		_getch();

	system("cls");
}

void View_Ranking()
{
	system("cls");

	int x = 24; int y = 5;
	int _frames = 0;

	SetColor(BLACK, WHITE);

	while (_kbhit()) // 키 입력 버퍼를 비움
		_getch();

	FILE* fp = fopen("..\\4_Resources\\Ranking\\rank.txt", "rt");
	multimap<int, string, greater<int>> mm;

	GoToxy(x + 10, y - 1); printf("○ RANKING ○"); Sleep(50);

	while (!feof(fp)) 
	{
		string str = "";
		char tempName[50] = { 0 };
		int tempScore = 0;
		
		fscanf(fp, "%s %d %d", tempName, &tempScore);  //파일에서 입력받음
		str = tempName;

		if(str != "")
			mm.insert({ tempScore, str});
	}

	multimap<int, string, greater<int>>::iterator iter;
	

	GoToxy(x + 4, y + 1);
	cout << "[순위]         " << "[이름]          " << "[남은 시간]"; 

	int idx = 1;

	if (mm.empty())
	{
		GoToxy(x + 4, y + 3); cout << "랭킹 목록이 없습니다.." << endl;
	}
	else
	{
		for (iter = mm.begin(); iter != mm.end(); iter++)
		{
			GoToxy(x + 5, y + idx + 2);  printf("%d", idx);
			GoToxy(x + 12, y + idx + 2);  cout << iter->second;
			GoToxy(x + 21, y + idx + 2); printf("%d", iter->first);
			idx++;

			if (idx == 11)
				break;
		}
	}

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 프레임마다 띄움
		{
			GoToxy(x + 7, y + 36); printf("PRESS ANY KEY TO GO TO TITLE"); // 반짝거리게 하고 싶은 욕심
		}
		else if ((_frames % 200 - 100) == 0) // 100 프레임 간격으로 지움 (1초 + @) 
		{
			GoToxy(x + 7, y + 36); printf("                              "); // 반짝거리게 하고 싶은 욕심
		}

		Sleep(10);
	}

	while (_kbhit()) // 키 입력 버퍼를 비움
		_getch();

	system("cls");
}