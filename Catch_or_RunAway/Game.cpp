#include "Game.h"
#include "SDL_image.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0) 
  {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(m_pWindow != 0) {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
      if(m_pWindow != 0)
      {
        SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

        m_pGameStateMachine = new GameStateMachine();
        m_pGameStateMachine->changeState(MenuState::Instance());
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }

  if( !TheTextureManager::Instance()->load("Assets/backGR.png", "backGR", m_pRenderer))
  {
     return false;
  }
  
  m_bRunning = true;
  
  return true;
}

void Game::update()
{
  
    m_pGameStateMachine->update();
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);
  // 모든 상태에서 배경은 하나만 사용하기 때문에 조금이라도 효율을 높이기위해 game부분에서 처리하였습니다.
  TheTextureManager::Instance()->draw("backGR", 0, 0, 1080, 1080, 0, m_pRenderer, SDL_FLIP_NONE);

  m_pGameStateMachine->render();
  SDL_RenderPresent(m_pRenderer);
}

bool Game::running()
{
  return m_bRunning;
}

void Game::handleEvents()
{
  TheInputHandler::Instance()->update();
}

void Game::clean()
{
  TheInputHandler::Instance()->clean();
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}