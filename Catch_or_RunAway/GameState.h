#pragma once
#include <string>
#include <vector>

class GameObject;

// 추상클래스
class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getStateID() const = 0;


protected:
	std::vector<GameObject*> m_gameObjects;
	// 오브잭트를 저장할 백터 변수입니다.
};
