#ifndef __Game__
#define __Game__

#include "SDL.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Tile.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "vector"

class GameStateMachine;

class Game {
public:
    Game() {}
    ~Game() {}
    bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
    
    void render();
    void update();
    bool running();
    void handleEvents();
    void clean();
    void quit() { m_bRunning = false; } // 게임 종류 함수

    GameStateMachine* getStateMachine()
    {
        return m_pGameStateMachine;
    }


    static Game* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new Game();
            return s_pInstance;
        }
        return s_pInstance;
    }
    SDL_Renderer* getRenderer() const { return m_pRenderer; }

private:
    static Game* s_pInstance;
    
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    bool m_bRunning;

    GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;

#endif