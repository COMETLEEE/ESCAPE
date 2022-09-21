#pragma once
#include "All_lib.h"
#include "Utils.h"

// ���� �ý����� �̴ϼȶ���¡ �ϴ� �Լ�
void SoundSystem();

// BGM�� Ű�� �Լ� (����)
void PlayBGM(int BGM_NUM);

// EFFECT�� Ű�� �Լ� (�� ����)
void PlayEFFECT(int EFFECT_NUM);

// BGM�� ���� �Լ�
void StopBGM();

// EFFECT�� ���� �Լ�
void StopEFFECT();