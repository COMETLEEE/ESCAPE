#pragma once
#define _CRT_SECURE_NO_WARNINGS 

// 키보드 조작
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define alphabet_a 97
#define alphabet_c 99
#define alphabet_d 100
#define alphabet_e 101
#define alphabet_h 104
#define alphabet_i 105
#define alphabet_l 108
#define alphabet_m 109
#define alphabet_n 110
#define alphabet_o 111
#define alphabet_p 112
#define alphabet_r 114
#define alphabet_s 115
#define alphabet_t 116
#define alphabet_u 117
#define P 80
#define ENTER 13
#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define SHARP 35
#define LESS_THAN_SIGN 60
#define GREATER_THAN_SIGN 62
#define DOT 46


// Gaming Logic
#define SPEED 1000 // 게임의 진행 속도 (몇 프레임)
#define MAZE_SIZE_X 41 // 미로의 가로 사이즈
#define MAZE_SIZE_Y 41 // 미로의 세로 사이즈
#define PLAYER 0 // 플레이어
#define START 1 // 출발지
#define GOAL 2 // 도착지
#define PATH 3 // 미로의 길
#define WALL 4 // 미로의 벽
#define BACK 5 // 미로 안보이는 부분
#define HARD_WALL 6 // 미로의 못부수는 벽
#define FAIRY_WAY 7 // 요정 스킬 쓸때 보이는 길
#define TRAP_ONE 8 // 미로의 함정 (화살표 함정)
#define TRAP_TWO 9 // 미로의 함정 (빨리치기 함정)
#define ITEM_HAMMER 10 // 해머 아이템
#define ITEM_TORCH 11 // 횃불 아이템
#define ITEM_FAIRY 12 // A* 요정
#define ITEM_DRILL 13 // 도리루
#define ALL_STAGE_COUNT 3

// Graphic
#define PLAYBOARD_ADJ_X 3 // 플레이보드 출력 위치 조정 of X
#define PLAYBOARD_ADJ_Y 2 // 플레이보드 출력 위치 조정 of Y

// Time
#define SEC_PER_MILI 1000
#define TIME_STAGE_ONE 180000 // 스테이지 별 제한시간 (밀리초)
#define TIME_STAGE_TWO 180000
#define TIME_STAGE_THREE 180000
#define TIME_STAGE_FOUR 180000
#define TIME_STAGE_FIVE 180000
#define TIME_FAIRY 10000
#define TIME_TORCH 10000
#define TIME_DRILL 5000
#define TIME_ITEM_FAIRY 0
#define TIME_ITEM_TORCH 1
#define TIME_ITEM_DRILL 2

// Sound. BGM
#define BGM_TITLE 0
#define BGM_INGAME_1 1
#define BGM_INGAME_2 2
#define BGM_INGAME_3 3

// Sound. EFFECT
#define EFFECT_MENU_MOVE 0
#define EFFECT_PAUSE 1
#define EFFECT_WALKING_LEFT 2
#define EFFECT_WALKING_RIGHT 3
#define EFFECT_HAMMER 4
#define EFFECT_FAIRY 5
#define EFFECT_TORCH 6
#define EFFECT_DRILL 7
#define EFFECT_ITEM_PICKUP 8
#define EFFECT_GOAL_SOUND 9
#define EFFECT_TRAP 10
#define EFFECT_HITTER 11

typedef enum ColorKinds
{
	BLACK,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	PINK,
	ORANGE,
	WHITE,
	GRAY,
	LIGHTBLUE,
	BRIGHTGREEN,
	SKY,
	BRIGHTRED,
	BRIGHTPINK,
	BRIGHTYELLOW,
	BRIGHTWHITE,
} ColorKinds;

typedef enum CURSOR_TYPE
{ 
	NOCURSOR, 
	SOLIDCURSOR, 
	NORMALCURSOR 
} CURSOR_TYPE;

// 출력하는 문자 및 콘솔 배경 색칠하는 함수
void SetColor(int _backColor, int _textColor);

// 콘솔창 커서의 타입을 컨트롤하는 함수
void SetCursorType(CURSOR_TYPE c);

// 콘솔창 내부 커서 위치 컨트롤하는 함수
void GoToxy(int x, int y);

// 맵 전용 텍스트 파일을 읽어오는 함수
void GetTextFileForMap(int (*_map)[MAZE_SIZE_X]);