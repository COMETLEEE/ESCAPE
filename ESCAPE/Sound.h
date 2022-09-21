#pragma once
#include "All_lib.h"
#include "Utils.h"

// 사운드 시스템을 이니셜라이징 하는 함수
void SoundSystem();

// BGM을 키는 함수 (루프)
void PlayBGM(int BGM_NUM);

// EFFECT를 키는 함수 (노 루프)
void PlayEFFECT(int EFFECT_NUM);

// BGM을 끄는 함수
void StopBGM();

// EFFECT를 끄는 함수
void StopEFFECT();