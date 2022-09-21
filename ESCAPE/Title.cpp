#include "All_lib.h"
#include "Title.h"
#include "Utils.h"
#include "Sound.h"

// �ܼ� ���α׷� ���� �� ���� ���� �ߴ� ȭ��, ������ Ÿ��Ʋ�� ����.
// 1. Maze Runner (��Ī) ������ �� 'PRESS ANY KEY' ��������.
// � Ű�� �Է��� Ȯ�εǸ� �Լ� ���� �� ���� ����.
void Title()
{
Fir: // How To Play�� ������ ����� �ٽ� ���ƿͼ� Title�Լ��� �ٽ� �����Ѵ�.
	// Ÿ��Ʋ, �ﰢ���� �ð��� ���� �����Ÿ� �� �ֵ��� �ð� ���� ����, ��ⷯ ������ ���� �����Ÿ� ����
	// ������ Ÿ��Ʋ�� �ܼ� �߾ӿ� ������ (Escape)
	// ���� �ϴܿ� 'Game Start, How to Play, Exit' ������ �� ���� ȭ��ǥ -> ������ ���Ͽ� ��ġ�� �����ϰ�, �Է� �� �Լ� �ߵ�
	int x = 5; int y = 5;
	
	int _frames = 0; // �������� ��� ����
	char _command = 0; // ���� Ŀ�ǵ带 �޴� ����

	int _posOfChoice = 0; // ���� ȭ��ǥ�� ��ġ�� ��Ÿ���� ����
	bool _enterFlag = false; // Enter�� ���� ���� ȭ��ǥ�� ��ġ�� ���� �б⸦ ������ �Ѵٴ� ��ȣ
	bool _startFlag = false; // ���� ��ŸƮ�� �˸��� ��ȣ

	// ���� ��� ���
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
	GoToxy(x + 29, y + 27 + _posOfChoice); printf("��");
	GoToxy(x + 31, y + 27); printf("GAME START");
	GoToxy(x + 31, y + 29); printf("HOW TO PLAY");
	GoToxy(x + 31, y + 31); printf("RANKING");
	GoToxy(x + 31, y + 33); printf("EXIT");

	while (_kbhit()) // ��� �Է� ���۸� �ʱ�ȭ�Ѵ�.
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
					GoToxy(x + 29, y + 27 + _posOfChoice); printf("��");
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
					GoToxy(x + 29, y + 27 + _posOfChoice); printf("��");
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
						goto Fir; // �ٽ� Title() �Լ��� ó������ ���ư���.
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

		if (_frames % 200 == 0) // 200 �����Ӹ��� ���
		{
			GoToxy(x + 26, y + 21); printf("PRESS ENTER KEY TO SELECT MENU"); // ��¦�Ÿ��� �ϰ� ���� ���
		}
		else if ((_frames % 200 - 100) == 0) // 100 ������ �������� ���� (1�� + @) 
		{
			GoToxy(x + 26, y + 21); printf("                              "); // ��¦�Ÿ��� �ϰ� ���� ���
		}

		if (_startFlag)
			break;

		Sleep(10); // 0.01�� ������ ���� ȭ�� ������ ����
	}

	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();

	system("cls");
	// Ű �Է��� �޾�����
	// Ȯ�� (Enter�̸� �ش� ��ġ ����, ��, �Ʒ� ȭ��ǥ�� �� ������ �̵��� �� �ִ��� Ȯ���ϰ� �̵�)
}

void HowToPlay()
{
	int x = 5; int y = 4;

	int _frames = 0;

	system("cls");

	GoToxy(x + 29, y); printf("�� HOW TO PLAY ��"); Sleep(50);
	GoToxy(x, y + 3);  printf("�� ���� ��ǥ : �������� �������� ����ϰ� ������ ���� ���ѽð� ���� �־��� �̷ε��� Ż���϶� !"); Sleep(50);

	GoToxy(x, y + 6);  printf("- ���۹�"); Sleep(50);
	GoToxy(x, y + 8);  printf("�� : �������� ȸ�� �� �̵� / �� : �������� ȸ�� �� �̵� / �� : ���� ȸ�� �� �̵� / �� : �Ʒ��� ȸ�� �� �̵�"); Sleep(50);
	GoToxy(x, y + 10); printf("1 : ��ġ ������ ��� / 2 : ���� ������ ��� / 3 : ȶ�� ������ ��� / 4 : �帱 ������ ���"); Sleep(50);
	GoToxy(x, y + 12); printf("P : PAUSE / Enter : �ش� �ɼ� ����"); Sleep(50);

	GoToxy(x, y + 15); printf("- ������"); Sleep(50);
	GoToxy(x, y + 17); printf("��ġ (��): �÷��̾� ���� �� ĭ �տ� ���� ������ ��� �� �� ���� �ı��մϴ�."); Sleep(50);
	GoToxy(x, y + 19); printf("���� (��): ���� �÷��̾��� ��ġ�� �������� ������������ �ִ� �Ÿ��� ���� �Һ����� �ȳ��մϴ�."); Sleep(50);
	GoToxy(x, y + 21); printf("ȶ�� (��) : �÷��̾� �ֺ��� �þ߸� �� �� �� �����ϴ�."); Sleep(50);
	GoToxy(x, y + 23); printf("�帱 (��): ��� �� ���� �ð����� �÷��̾� �տ� �ִ� ��� ���� �������� �ı��ϸ鼭 ������ �����մϴ�."); Sleep(50);

	GoToxy(x, y + 26); printf("- ���� (��)"); Sleep(50);
	GoToxy(x, y + 28); printf("�̷� ���� ���⿡ ������ �ֽ��ϴ�. ������ ���� �� ��Ģ�� �����ؾ� �մϴ�."); Sleep(50);
	GoToxy(x, y + 30); printf("Ŀ�ǵ� ��Ģ : �־��� ȭ��ǥ�� �����ϰ� ȭ��ǥ�� �Է��ϸ� �����˴ϴ�."); Sleep(50);
	GoToxy(x, y + 32); printf("Ÿ�ڿ��� ��Ģ : �־��� ����� �����ϰ� �Է��ϸ� �����˴ϴ�."); Sleep(50);

	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 �����Ӹ��� ���
		{
			GoToxy(x + 26, y + 36); printf("PRESS ANY KEY TO GO TO TITLE"); // ��¦�Ÿ��� �ϰ� ���� ���
		}
		else if ((_frames % 200 - 100) == 0) // 100 ������ �������� ���� (1�� + @) 
		{
			GoToxy(x + 26, y + 36); printf("                              "); // ��¦�Ÿ��� �ϰ� ���� ���
		}

		Sleep(10);
	}

	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();

	system("cls");
}

void View_Ranking()
{
	system("cls");

	int x = 24; int y = 5;
	int _frames = 0;

	SetColor(BLACK, WHITE);

	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();

	FILE* fp = fopen("..\\4_Resources\\Ranking\\rank.txt", "rt");
	multimap<int, string, greater<int>> mm;

	GoToxy(x + 10, y - 1); printf("�� RANKING ��"); Sleep(50);

	while (!feof(fp)) 
	{
		string str = "";
		char tempName[50] = { 0 };
		int tempScore = 0;
		
		fscanf(fp, "%s %d %d", tempName, &tempScore);  //���Ͽ��� �Է¹���
		str = tempName;

		if(str != "")
			mm.insert({ tempScore, str});
	}

	multimap<int, string, greater<int>>::iterator iter;
	

	GoToxy(x + 4, y + 1);
	cout << "[����]         " << "[�̸�]          " << "[���� �ð�]"; 

	int idx = 1;

	if (mm.empty())
	{
		GoToxy(x + 4, y + 3); cout << "��ŷ ����� �����ϴ�.." << endl;
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

		if (_frames % 200 == 0) // 200 �����Ӹ��� ���
		{
			GoToxy(x + 7, y + 36); printf("PRESS ANY KEY TO GO TO TITLE"); // ��¦�Ÿ��� �ϰ� ���� ���
		}
		else if ((_frames % 200 - 100) == 0) // 100 ������ �������� ���� (1�� + @) 
		{
			GoToxy(x + 7, y + 36); printf("                              "); // ��¦�Ÿ��� �ϰ� ���� ���
		}

		Sleep(10);
	}

	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();

	system("cls");
}