#pragma once
#include "All_lib.h"

struct Player
{
	int _pos_x;
	int _pos_y;
	int _goal_x;
	int _goal_y;
	int _direction;
	int _eyeSight;

	void Init();
};