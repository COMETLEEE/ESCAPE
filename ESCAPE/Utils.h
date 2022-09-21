#pragma once
#define _CRT_SECURE_NO_WARNINGS 

// Ű���� ����
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
#define SPEED 1000 // ������ ���� �ӵ� (�� ������)
#define MAZE_SIZE_X 41 // �̷��� ���� ������
#define MAZE_SIZE_Y 41 // �̷��� ���� ������
#define PLAYER 0 // �÷��̾�
#define START 1 // �����
#define GOAL 2 // ������
#define PATH 3 // �̷��� ��
#define WALL 4 // �̷��� ��
#define BACK 5 // �̷� �Ⱥ��̴� �κ�
#define HARD_WALL 6 // �̷��� ���μ��� ��
#define FAIRY_WAY 7 // ���� ��ų ���� ���̴� ��
#define TRAP_ONE 8 // �̷��� ���� (ȭ��ǥ ����)
#define TRAP_TWO 9 // �̷��� ���� (����ġ�� ����)
#define ITEM_HAMMER 10 // �ظ� ������
#define ITEM_TORCH 11 // ȶ�� ������
#define ITEM_FAIRY 12 // A* ����
#define ITEM_DRILL 13 // ������
#define ALL_STAGE_COUNT 3

// Graphic
#define PLAYBOARD_ADJ_X 3 // �÷��̺��� ��� ��ġ ���� of X
#define PLAYBOARD_ADJ_Y 2 // �÷��̺��� ��� ��ġ ���� of Y

// Time
#define SEC_PER_MILI 1000
#define TIME_STAGE_ONE 180000 // �������� �� ���ѽð� (�и���)
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

// ����ϴ� ���� �� �ܼ� ��� ��ĥ�ϴ� �Լ�
void SetColor(int _backColor, int _textColor);

// �ܼ�â Ŀ���� Ÿ���� ��Ʈ���ϴ� �Լ�
void SetCursorType(CURSOR_TYPE c);

// �ܼ�â ���� Ŀ�� ��ġ ��Ʈ���ϴ� �Լ�
void GoToxy(int x, int y);

// �� ���� �ؽ�Ʈ ������ �о���� �Լ�
void GetTextFileForMap(int (*_map)[MAZE_SIZE_X]);