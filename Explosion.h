#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Game_base.h"
#include "LTexture.h"

class Explosion
{
    public:
        Explosion();

        ~Explosion();

        void loadFromFile(std::string path, SDL_Renderer* gRenderer);

        void set_clip(SDL_Rect Clip);

        void render(SDL_Renderer* gRenderer);

        void setPos(const int x, const int y);

    private:

        int posX;

        int posY;

        SDL_Rect FrameClips;

        SDL_Texture* explosionTexture;
};
#endif // EXPLOSION_H_
