#include "PlayState.h"
#include <iostream>
#include "Game.h"
#include "PauseState.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "PauseState.h"
#include "Tile.h"
#include "XTrap.h"
#include "YTrap.h"
#include "crossTrap.h"
#include "TargetTrap.h"



const std::string PlayState::s_playID = "PLAY";
PlayState* PlayState::s_pInstance = NULL;

void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->changeState(PauseState::Instance());
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	for (int i = 0; i < m_tile.size(); i++) // 타일 update
	{
		m_tile[i]->update();
	}

}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	for (int i = 0; i < m_tile.size(); i++) // 타일 update
	{
		m_tile[i]->draw();
	}
}

bool PlayState::onEnter()
{
	// 오디오 출력을 위한 변수
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	bgm = Mix_LoadMUS("res/bgm.mp3");
	Mix_VolumeMusic(5); // 오디오 볼륨을 5로 설정.
	Mix_PlayMusic(bgm, -1);


	if (!TheTextureManager::Instance()->load("Assets/alpha-Player.png", "Player", 
		TheGame::Instance()->getRenderer())) 
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("Assets/Wall.png", "Wall", 
		TheGame::Instance()->getRenderer())) 
	{
		return false;
	}

	for (int x = 0; x < 19; x++)
	{
		for (int y = 0; y < 19; y++)
		{
			if (map[x][y] == 1)
			{
				GameObject* tile = new Tile(new LoaderParams(1080 - (19 - x) * 60, 1080 - (19 - y) * 60, 60, 60, "Wall"));
				m_tile.push_back(tile);
			}
		}
	}

	GameObject* Xtrap = new XTrap(new LoaderParams(400, 600, 60, 60, "Wall"));
	GameObject* Ytrap = new YTrap(new LoaderParams(200, 300, 60, 60, "Wall"));
	GameObject* ctrap = new crossTrap(new LoaderParams(100, 0, 60, 60, "Wall"));

	GameObject* Ttrap = new TargetTrap(new LoaderParams(1080, 1080, 60, 60, "Wall"));


	GameObject* player = new Player(new LoaderParams(100, 200, 40, 40, "Player"));


	
	m_tile.push_back(Xtrap); // X move
	m_tile.push_back(Ytrap); // Y move
	m_tile.push_back(ctrap); // cross move
	m_tile.push_back(Ttrap); // 마우스를 쫒아가는 타깃트렙부분 (이부분은 딜레이를 통해 시간이 지나야 마우스를 따라가게 만들었습니다.)

	m_gameObjects.push_back(player);
	

	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	for (int i = 0; i < m_tile.size(); i++) // 타일 update
	{
		m_tile[i]->clean();
	}

	m_gameObjects.clear();
	m_tile.clear();

	Mix_FreeMusic(bgm);

	TheTextureManager::Instance()->clearFromTextureMap("Player");
	TheTextureManager::Instance()->clearFromTextureMap("Wall");
	return true;
}