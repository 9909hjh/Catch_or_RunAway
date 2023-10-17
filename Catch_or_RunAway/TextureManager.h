#pragma once
#include "SDL.h"
#include "map"
#include <string>
#include "SDL_ttf.h"


class TextureManager {
public:
    ~TextureManager() {}

    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

    void draw(std::string id, int x, int y, int width, int height, float rotationAngle,
        SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    //rotationAngle
    void drawFrame(std::string id, int x, int y, int width, int height, float rotationAngle, int currentRow, int currenFrame,
        SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int TTF_drawFont(const char* id, int x, int y, int width, int height, SDL_Renderer* pRenderer);

    static TextureManager* Instance()
    {
        if (s_pInstance == 0) {
            s_pInstance = new TextureManager();
        }
        return s_pInstance;
    }

    void clearFromTextureMap(std::string id)
    {
        m_textureMap.erase(id);
    }

private:
    

    TextureManager() {}
    static TextureManager* s_pInstance;
    std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;