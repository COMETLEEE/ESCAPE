#pragma once
// 콘솔 프로그램 실행 후 가장 먼저 뜨는 화면, 게임의 타이틀을 보이는 핵심 함수
// 1. Maze Runner (가칭) 렌더링 후 'PRESS ANY KEY' 깜빡깜빡.
// 어떤 키든 입력이 확인되면 함수 종료 후 게임 진입.
void Title();

// Title() 함수 내에서 유저가 "How To Play"를 선택했을 때 호출하는 함수
void HowToPlay();

void View_Ranking();