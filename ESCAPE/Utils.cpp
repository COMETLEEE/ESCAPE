#include "All_lib.h"
#include "Utils.h"

// 출력하는 문자 및 배경의 컬러 컨트롤입니다 ..
void SetColor(int _backColor, int _textColor)
{
	HANDLE _handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(_handle, (_backColor << 4) + _textColor);
}

// 콘솔 창 내부 커서 타입 컨트롤
void SetCursorType(CURSOR_TYPE c) // 커서 컨트롤 함수
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

// 콘솔창 내부 커서 위치 컨트롤
void GoToxy(int x, int y)
{
    COORD pos = { 2 * x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 맵 전용 텍스트 파일을 읽어오는 함수
void GetTextFileForMap(int (*_map)[MAZE_SIZE_X]) // 마지막에 \n 이 들어가서 101 칸으로 했습니다.
{
    FILE* fs; 

    fs = fopen("C:\\Users\\DongMin\\Desktop\\ascii.txt", "r"); // 받을 때 주소 바꾸는거 잊지 마세염 ..
    for (int y = 0; y < MAZE_SIZE_Y; y++)
    {
        for (int x = 0; x < MAZE_SIZE_X; x++)
        {
            fscanf(fs, "%c", &_map[y][x]);
        }
    }
}