#include "Trap.h"
#include <Windows.h>

vector<pair<int, bool>> trapCommandVec; // 함정 쓰고 클리어 해줄것
int trapCommandIdx = 0; // 함정 쓰고 클리어 해줄것
extern int g_stageCount;

void Trap::Check_Key_Trap()
{
	int _userCommand;

	if (_kbhit())
	{
		_userCommand = _getch();

		if (_userCommand == 224) // 받은 것이 방향키이면 !
		{
			do
			{
				_userCommand = _getch(); // 방향키 값을 얻을 때까지 고고
			} while (_userCommand == 224);

			switch (_userCommand)
			{
				case UP:
				{
					if (trapCommandVec[trapCommandIdx].first == UP && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case RIGHT:
				{
					if (trapCommandVec[trapCommandIdx].first == RIGHT && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case DOWN:
				{
					if (trapCommandVec[trapCommandIdx].first == DOWN && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case LEFT:
				{
					if (trapCommandVec[trapCommandIdx].first == LEFT && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
			}
		}
		else // 방향키가 아니라면
		{
			switch (_userCommand)
			{
				case 'A':
				case alphabet_a:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_a && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'C':
				case alphabet_c:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_c && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'D':
				case alphabet_d:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_d && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'E':
				case alphabet_e:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_e && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'H':
				case alphabet_h:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_h && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'I':
				case alphabet_i:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_i && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'L':
				case alphabet_l:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_l && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'M':
				case alphabet_m:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_m && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'N':
				case alphabet_n:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_n && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'O':
				case alphabet_o:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_o && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'P':
				case alphabet_p:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_p && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'R':
				case alphabet_r:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_r && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'S':
				case alphabet_s:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_s && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'T':
				case alphabet_t:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_t && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case 'U':
				case alphabet_u:
				{
					if (trapCommandVec[trapCommandIdx].first == alphabet_u && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case LESS_THAN_SIGN:
				{
					if (trapCommandVec[trapCommandIdx].first == LESS_THAN_SIGN && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case GREATER_THAN_SIGN:
				{
					if (trapCommandVec[trapCommandIdx].first == GREATER_THAN_SIGN && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case SHARP:
				{
					if (trapCommandVec[trapCommandIdx].first == SHARP && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				case DOT:
				{
					if (trapCommandVec[trapCommandIdx].first == DOT && trapCommandVec[trapCommandIdx].second == false)
					{
						PlayEFFECT(EFFECT_HITTER);
						trapCommandVec[trapCommandIdx].second = true;
						trapCommandIdx++;
					}
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}

	while (_kbhit()) // 키 입력 버퍼 클리어
		_getch();
}

void Trap::CommandTrapOperate()
{
	int commandKey[4] = { UP, RIGHT, DOWN, LEFT };
	int randomKeyIndex = rand() % 4;
	int commandCount = 8; // 커맨드 몇개 뜨개 할지

	for (int i = 0; i < commandCount; i++)
	{
		trapCommandVec.push_back({ commandKey[randomKeyIndex], false });
		randomKeyIndex = rand() % 4;
	}
}

void Trap::HitterTrapOperate()
{
	int randomKeyIndex = rand() % 2;
	vector<vector<int>> keywordVec = 
	{ 
		{
			SHARP, alphabet_i, alphabet_n, alphabet_c,
			alphabet_l, alphabet_u, alphabet_d, alphabet_e,
			LESS_THAN_SIGN, alphabet_s, alphabet_t, alphabet_d,
			alphabet_i, alphabet_o, DOT, alphabet_h ,GREATER_THAN_SIGN
		},
		{
			SHARP, alphabet_i, alphabet_n, alphabet_c,
			alphabet_l, alphabet_u, alphabet_d, alphabet_e,
			LESS_THAN_SIGN, alphabet_i, alphabet_o, alphabet_s,
			alphabet_t, alphabet_r, alphabet_e, alphabet_a, 
			alphabet_m,GREATER_THAN_SIGN
		}
	};

	for (int i = 0; i < keywordVec[randomKeyIndex].size(); i++)
	{
		trapCommandVec.push_back({ keywordVec[randomKeyIndex][i], false });
	}
}

void Trap::DrawHitterTrapInGame()
{
	PlayEFFECT(EFFECT_TRAP);

	while (trapCommandIdx != trapCommandVec.size())
	{
		int x = 53;
		int y = 19;

		GoToxy(x, y + 1);		printf("┌───────────────────────────────────────────┐ ");
		GoToxy(x, y + 2);		printf("│                                           │ ");
		GoToxy(x, y + 3);		printf("│           H I T T E R   T R A P           │ ");
		GoToxy(x, y + 4);		printf("│                                           │ ");
		GoToxy(x, y + 5);		printf("│                                           │ ");
		GoToxy(x, y + 6);		printf("│                                           │ ");
		GoToxy(x, y + 7);		printf("│ ");
		GoToxy(x + 22, y + 7);		printf("│ "); // 단차 맞춰야해서 ..
		GoToxy(x, y + 8);		printf("│                                           │ ");
		GoToxy(x, y + 9);		printf("└───────────────────────────────────────────┘ ");
		GoToxy(x + 3, y + 7);

		for (int i = 0; i < trapCommandVec.size(); i++)
		{
			if (trapCommandVec[i].second == true)
			{
				SetColor(BLACK, RED);
				if (trapCommandVec[i].first == SHARP)
					printf("# ");
				else if (trapCommandVec[i].first == LESS_THAN_SIGN)
					printf("< ");
				else if (trapCommandVec[i].first == GREATER_THAN_SIGN)
					printf("> ");
				else if (trapCommandVec[i].first == alphabet_i)
					printf("i ");
				else if (trapCommandVec[i].first == alphabet_n)
					printf("n ");
				else if (trapCommandVec[i].first == alphabet_c)
					printf("c ");
				else if (trapCommandVec[i].first == alphabet_l)
					printf("l ");
				else if (trapCommandVec[i].first == alphabet_u)
					printf("u ");
				else if (trapCommandVec[i].first == alphabet_d)
					printf("d ");
				else if (trapCommandVec[i].first == alphabet_e)
					printf("e ");
				else if (trapCommandVec[i].first == alphabet_s)
					printf("s ");
				else if (trapCommandVec[i].first == alphabet_t)
					printf("t ");
				else if (trapCommandVec[i].first == alphabet_o)
					printf("o ");
				else if (trapCommandVec[i].first == alphabet_a)
					printf("a ");
				else if (trapCommandVec[i].first == alphabet_r)
					printf("r ");
				else if (trapCommandVec[i].first == alphabet_h)
					printf("h ");
				else if (trapCommandVec[i].first == alphabet_m)
					printf("m ");
				else if (trapCommandVec[i].first == DOT)
					printf(". ");
			}
			else
			{
				SetColor(BLACK, WHITE);
				if (trapCommandVec[i].first == SHARP)
					printf("# ");
				else if (trapCommandVec[i].first == LESS_THAN_SIGN)
					printf("< ");
				else if (trapCommandVec[i].first == GREATER_THAN_SIGN)
					printf("> ");
				else if (trapCommandVec[i].first == alphabet_i)
					printf("i ");
				else if (trapCommandVec[i].first == alphabet_n)
					printf("n ");
				else if (trapCommandVec[i].first == alphabet_c)
					printf("c ");
				else if (trapCommandVec[i].first == alphabet_l)
					printf("l ");
				else if (trapCommandVec[i].first == alphabet_u)
					printf("u ");
				else if (trapCommandVec[i].first == alphabet_d)
					printf("d ");
				else if (trapCommandVec[i].first == alphabet_e)
					printf("e ");
				else if (trapCommandVec[i].first == alphabet_s)
					printf("s ");
				else if (trapCommandVec[i].first == alphabet_t)
					printf("t ");
				else if (trapCommandVec[i].first == alphabet_o)
					printf("o ");
				else if (trapCommandVec[i].first == alphabet_a)
					printf("a ");
				else if (trapCommandVec[i].first == alphabet_r)
					printf("r ");
				else if (trapCommandVec[i].first == alphabet_h)
					printf("h ");
				else if (trapCommandVec[i].first == alphabet_m)
					printf("m ");
				else if (trapCommandVec[i].first == DOT)
					printf(". ");
			}

		}

		Check_Key_Trap();
	}

	trapCommandVec.clear();
	trapCommandIdx = 0;
	system("cls");
	Draw_UI_FIXED(g_stageCount);
}

void Trap::DrawCommandTrapInGame()
{
	PlayEFFECT(EFFECT_TRAP);

	while (trapCommandIdx != trapCommandVec.size())
	{
		int x = 53;
		int y = 19;

		SetColor(BLACK, WHITE);
		
		GoToxy(x, y + 1);		printf("┌───────────────────────────────────────────┐ ");
		GoToxy(x, y + 2);		printf("│                                           │ ");
		GoToxy(x, y + 3);		printf("│           C O M M A N D  T R A P          │ ");
		GoToxy(x, y + 4);		printf("│                                           │ ");
		GoToxy(x, y + 5);		printf("│                                           │ ");
		GoToxy(x, y + 6);		printf("│                                           │ ");
		GoToxy(x, y + 7);		printf("│ ");
		GoToxy(x + 22, y + 7);		printf("│ "); // 단차 맞춰야해서 ..
		GoToxy(x, y + 8);		printf("│                                           │ ");
		GoToxy(x, y + 9);		printf("└───────────────────────────────────────────┘ ");
		GoToxy(x + 6, y + 7); 
		
		for (int i = 0; i < trapCommandVec.size(); i++)
		{
			if (trapCommandVec[i].second == true)
			{
				SetColor(BLACK, RED);
				if (trapCommandVec[i].first == UP)
					printf("↑ ");
				else if (trapCommandVec[i].first == RIGHT)
					printf("→ ");
				else if (trapCommandVec[i].first == LEFT)
					printf("← ");
				else if (trapCommandVec[i].first == DOWN)
					printf("↓ ");
			}
			else
			{
				SetColor(BLACK, WHITE);
				if (trapCommandVec[i].first == UP)
					printf("↑ ");
				else if (trapCommandVec[i].first == RIGHT)
					printf("→ ");
				else if (trapCommandVec[i].first == LEFT)
					printf("← ");
				else if (trapCommandVec[i].first == DOWN)
					printf("↓ ");
			}
			
		}

		Check_Key_Trap();
	}

	trapCommandVec.clear();
	trapCommandIdx = 0;
	system("cls");
	Draw_UI_FIXED(g_stageCount);
}