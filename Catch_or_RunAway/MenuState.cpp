#include "MenuState.h"
#include <iostream>
#include "MenuButton.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"



const std::string MenuState::s_menuID = "MENU";
MenuState* MenuState::s_pInstance = NULL;

void MenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

}

void MenuState::render()
{
	TheTextureManager::Instance()->TTF_drawFont("The control keys are above the arrow keys, left, and right.", 150, 500, 700, 30, TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->TTF_drawFont("made by 20181289_HAN JU-HYEONG", 300, 700, 400, 30, TheGame::Instance()->getRenderer());
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}

}

bool MenuState::onEnter()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Startbgm = Mix_LoadMUS("res/Startbgm.mp3");
	Mix_VolumeMusic(5);
	Mix_PlayMusic(Startbgm, -1);

	
	if (!TheTextureManager::Instance()->load("Assets/button.png", "playbutton",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/exit.png","exitbutton",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(
		new LoaderParams(450, 100, 128, 128, "playbutton"),
		s_menuToPlay);

	GameObject* button2 = new MenuButton(
		new LoaderParams(450, 300, 128, 128, "exitbutton"),
		s_exitFromMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	Mix_FreeMusic(Startbgm);

	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");
	std::cout << "onEnter MENU\n";
	return true;
}

void MenuState::s_menuToPlay()
{
	std::cout << "Play button clicked\n";
	TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
}

void MenuState::s_exitFromMenu()
{
	std::cout << "Exit button clicked\n";
	TheGame::Instance()->quit();
}
