#include "Sound.h"

System* pSoundSystem;

Sound* pBGM[4];// BGM�� �迭

Sound* pEFFECT[15]; // EFFECT�� �迭

Channel* pBGMChannel; // BGM�� ä��, LOOP�� �⺻������ Ű�� ������ (pause �Ű� �����)

Channel* pEFFECTChannel; // EFFECT�� ä��, LOOP�� �⺻������ ���� ������ (pause �Ű� �� �����)

int index = 0;

void SoundSystem()
{
	System_Create(&pSoundSystem); // �ý����� ������ش�.

	pSoundSystem->init(32, FMOD_INIT_NORMAL, NULL); // �ý����� Init�� ���� �����Ѵ�.

	// BGM INIT() 
	FMOD_LOOP_NORMAL;
	pSoundSystem->createSound("..\\4_Resources\\BGM\\Shattered_Time.wav", FMOD_LOOP_NORMAL, 0, &pBGM[BGM_TITLE]);
	pSoundSystem->createSound("..\\4_Resources\\BGM\\FAKE_LOVE.wav", FMOD_LOOP_NORMAL, 0, &pBGM[BGM_INGAME_1]);
	pSoundSystem->createSound("..\\4_Resources\\BGM\\HITMAN.wav", FMOD_LOOP_NORMAL, 0, &pBGM[BGM_INGAME_2]);
	pSoundSystem->createSound("..\\4_Resources\\BGM\\Phantasmal_Woods.wav", FMOD_LOOP_NORMAL, 0, &pBGM[BGM_INGAME_3]);

	// EFFECT INIT()
	FMOD_DEFAULT;
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\MENU_MOVE.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_MENU_MOVE]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\PAUSE.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_PAUSE]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\WALKING_LEFT.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_WALKING_LEFT]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\WALKING_RIGHT.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_WALKING_RIGHT]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\HAMMER.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_HAMMER]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\FAIRY.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_FAIRY]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\TORCH.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_TORCH]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\DRILL.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_DRILL]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\ITEM_PICKUP.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_ITEM_PICKUP]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\GOAL_SOUND.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_GOAL_SOUND]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\TRAP.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_TRAP]);
	pSoundSystem->createSound("..\\4_Resources\\EFFECT\\HITTER.wav", FMOD_DEFAULT, 0, &pEFFECT[EFFECT_HITTER]);
}

void PlayBGM(int BGM_NUM)
{
	pSoundSystem->playSound(pBGM[BGM_NUM], NULL, 0, &pBGMChannel);
}

void PlayEFFECT(int EFFECT_NUM)
{
	pSoundSystem->update();
	pSoundSystem->playSound(pEFFECT[EFFECT_NUM], NULL, 0, &pEFFECTChannel);
}

void StopBGM()
{
	pBGMChannel->stop();
}

void StopEFFECT()
{
	pEFFECTChannel->stop();
}