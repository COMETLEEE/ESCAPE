#include "Ranking.h"

void RankRecord(int remainTime)
{
Re_RankRecord:
	while (_kbhit()) // 키 입력 버퍼를 비움
		_getch();

	system("cls");

	FILE* fp;
	char name[4];
	int x = 0; int y = 4;

	
	GoToxy(x, y); printf("<< 이름을 입력하세요 대문자 3글자>>");
	GoToxy(x, y + 1); scanf("%s", name);

	//fgets(name, sizeof(name), stdin);

	if (name[3] != '\0')
	{
		GoToxy(x, y + 2);
		printf("길이가 3이아닙니다. 다시 입력하세요!");
		goto Re_RankRecord;
	}

	for (int i = 0; i < 3; i++)
	{
		if (!(name[i] >= 'A' && name[i] <= 'Z'))
		{
			GoToxy(x, y + 2);
			printf("대문자영어로 다시 입력하세요 !");
			Sleep(1000);

			goto Re_RankRecord;
		}
	}

	fp = fopen("..\\4_Resources\\Ranking\\rank.txt", "at");
	if (fp == NULL) { fp = fopen("..\\4_Resources\\Ranking\\rank.txt", "wt"); }

	fprintf(fp, "%s %d \n", name, remainTime);
	fclose(fp);

	GoToxy(x, y + 5); printf("『 저장 하였습니다 』");
	
	int _frames = 0;

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 프레임마다 띄움
		{
			GoToxy(x + 25, y + 25); printf("PRESS ANY KEY TO GO TO EXIT"); // 반짝거리게 하고 싶은 욕심
		}
		else if ((_frames % 200 - 100) == 0) // 100 프레임 간격으로 지움 (1초 + @) 
		{
			GoToxy(x + 25, y + 25); printf("                                       "); // 반짝거리게 하고 싶은 욕심
		}

		Sleep(10);
	}

	exit(0);
}