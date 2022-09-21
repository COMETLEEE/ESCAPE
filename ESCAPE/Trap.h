#pragma once
#include "All_lib.h"
#include "Utils.h"
#include "Draw.h"
#include "Sound.h"

struct Trap
{
	void Check_Key_Trap();
	void CommandTrapOperate();
	void HitterTrapOperate();

	void DrawCommandTrapInGame();
	void DrawHitterTrapInGame();
};