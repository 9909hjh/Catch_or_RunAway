#pragma once
#include "GameState.h"
#include <SDL_mixer.h>
#include <vector>

class GameObject;

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_gameOverID; }

	static GameOverState* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new GameOverState();
		}
		return s_pInstance;
	}

private:
	static const std::string s_gameOverID;
	static void s_gameOverToMain(); // 게임오버를한 상태에서 메인버튼을 눌렀을때.
	static void s_restartPlay(); // 오버상태에서 리스타트 버튼을 눌렀을때.

	Mix_Music* overbgm; // 오버상태의 오디오출력 변수

	GameOverState() {};
	static GameOverState* s_pInstance;
};