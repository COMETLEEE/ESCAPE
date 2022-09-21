#pragma once
#include <time.h>
struct Time
{
	LONGLONG stageLeftTime; // 스테이지별 제한 시간을 저장하는 변수
	LONGLONG stageStartTime; // 스테이지가 시작될 때의 시각을 저장하는 변수
	LONGLONG nowTime; // 각 프레임 별 현재의 시각을 측정할 때 사용하는 변수
	LONGLONG diffTime; // 시간의 차이를 구할 때 쓸 변수 
	LONGLONG stageTotalPauseTime;

	LONGLONG itemStartTime[3]; // 0 : 요정, 1: 횃불, 2 : 드릴 / 아이템을 사용했을 때의 시각을 저장한다.



	// 초 단위로 구해 (CLOCKS_PER_SEC로 나누어준다.)
	// 분과 초로 나눠 ~ (60으로 나누면 되겠죠)

	// 시간 측정의 설계
	// 우리가 필요한 시간 ? => 스테이지가 시작되고 얼마나 진행되었는가 ?
	// 0. 매 스테이지별 제한 시간을 놔둔다. (매 스테이지가 시작될 때 stageLeftTIme 변수를 스테이지에 맞게 초기화시킴.
	// 1. Stage가 시작될 때의 시각을 측정한다. (기준 시각)
	// 2. 매 프레임 별 현재의 시각을 측정해서 (nowTime - stageStartTime 을 해서 스테이지 시작 후 시간이 얼마나 흘렀는지 계산한다.)
	// 3. stageLeftTime - nowTime + stageStartTime 을 해서 제한시간이 얼마나 남았는지 체캉한다. 
	// 4. 제한 시간이 0보다 크거나 같으면 게임을 계속 진행시키고
	// 5. 제한 시간이 0보다 작으면 '패배 프로세스'를 진행한다.
	// 6. Draw_UI 함수에 매개변수로 '3'의 값을 넘겨준다.
};