#include "Ranking.h"

void RankRecord(int remainTime)
{
Re_RankRecord:
	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();

	system("cls");

	FILE* fp;
	char name[4];
	int x = 0; int y = 4;

	
	GoToxy(x, y); printf("<< �̸��� �Է��ϼ��� �빮�� 3����>>");
	GoToxy(x, y + 1); scanf("%s", name);

	//fgets(name, sizeof(name), stdin);

	if (name[3] != '\0')
	{
		GoToxy(x, y + 2);
		printf("���̰� 3�̾ƴմϴ�. �ٽ� �Է��ϼ���!");
		goto Re_RankRecord;
	}

	for (int i = 0; i < 3; i++)
	{
		if (!(name[i] >= 'A' && name[i] <= 'Z'))
		{
			GoToxy(x, y + 2);
			printf("�빮�ڿ���� �ٽ� �Է��ϼ��� !");
			Sleep(1000);

			goto Re_RankRecord;
		}
	}

	fp = fopen("..\\4_Resources\\Ranking\\rank.txt", "at");
	if (fp == NULL) { fp = fopen("..\\4_Resources\\Ranking\\rank.txt", "wt"); }

	fprintf(fp, "%s %d \n", name, remainTime);
	fclose(fp);

	GoToxy(x, y + 5); printf("�� ���� �Ͽ����ϴ� ��");
	
	int _frames = 0;

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 200 == 0) // 200 �����Ӹ��� ���
		{
			GoToxy(x + 25, y + 25); printf("PRESS ANY KEY TO GO TO EXIT"); // ��¦�Ÿ��� �ϰ� ���� ���
		}
		else if ((_frames % 200 - 100) == 0) // 100 ������ �������� ���� (1�� + @) 
		{
			GoToxy(x + 25, y + 25); printf("                                       "); // ��¦�Ÿ��� �ϰ� ���� ���
		}

		Sleep(10);
	}

	exit(0);
}