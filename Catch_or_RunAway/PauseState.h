#pragma once
#include "GameState.h"

class GameObject;

class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_pauseID; }

	static PauseState* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new PauseState();
		}
		return s_pInstance;
	}


private:
	static void s_pauseToMain(); // 정지상태에서 메인버튼을 눌렀을때.
	static void s_resumePlay(); // 정지상태에서 다시 시작버튼을 눌렀을때.
	static const std::string s_pauseID;

	PauseState() {};
	static PauseState* s_pInstance;
};