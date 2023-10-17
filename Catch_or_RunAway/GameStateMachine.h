#pragma once
#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
    void changeState(GameState* pState); // 상태를 바꿔주는 역할을 합니다.
    void popState();
    void update();
    void render();
    GameState* m_currentState; // 현재 상태를 채크
    GameState* m_prevState; // 이전 상태를 채크
};