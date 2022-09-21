#include "All_lib.h"
#include "Utils.h"

// ����ϴ� ���� �� ����� �÷� ��Ʈ���Դϴ� ..
void SetColor(int _backColor, int _textColor)
{
	HANDLE _handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(_handle, (_backColor << 4) + _textColor);
}

// �ܼ� â ���� Ŀ�� Ÿ�� ��Ʈ��
void SetCursorType(CURSOR_TYPE c) // Ŀ�� ��Ʈ�� �Լ�
{
    CONSOLE_CURSOR_INFO CurInfo;

    switch (c) {
        case NOCURSOR:
            CurInfo.dwSize = 1;
            CurInfo.bVisible = FALSE;
            break;
        case SOLIDCURSOR:
            CurInfo.dwSize = 100;
            CurInfo.bVisible = TRUE;
            break;
        case NORMALCURSOR:
            CurInfo.dwSize = 20;
            CurInfo.bVisible = TRUE;
            break;
    }

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// �ܼ�â ���� Ŀ�� ��ġ ��Ʈ��
void GoToxy(int x, int y)
{
    COORD pos = { 2 * x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// �� ���� �ؽ�Ʈ ������ �о���� �Լ�
void GetTextFileForMap(int (*_map)[MAZE_SIZE_X]) // �������� \n �� ���� 101 ĭ���� �߽��ϴ�.
{
    FILE* fs; 

    fs = fopen("C:\\Users\\DongMin\\Desktop\\ascii.txt", "r"); // ���� �� �ּ� �ٲٴ°� ���� ������ ..
    for (int y = 0; y < MAZE_SIZE_Y; y++)
    {
        for (int x = 0; x < MAZE_SIZE_X; x++)
        {
            fscanf(fs, "%c", &_map[y][x]);
        }
    }
}