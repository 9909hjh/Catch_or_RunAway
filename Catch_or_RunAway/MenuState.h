#pragma once
#include "GameState.h"
#include <SDL_mixer.h>
#include "SDL_ttf.h"

class MenuState : public GameState
{
public:
	// 상속 받은 순수 가상 함수의 정의 입니다.
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_menuID; }

	static MenuState* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new MenuState();
		}
		return s_pInstance;
	}

private:
	static const std::string s_menuID;
	static void s_menuToPlay(); // 시작버튼을 눌렀을때 동작합니다.
	static void s_exitFromMenu(); // 나가기 버튼을 눌렀을때 동작합니다.

	Mix_Music* Startbgm; // 오디오를 출력해주는 멤버변수입니다.
	

	MenuState() {};
	static MenuState* s_pInstance;
};