#ifndef BUTTON_H
#define BUTTON_H

#include "Game_base.h"
#include "LTexture.h"

class Button
{
    public:
        ButtonSprite mCurrentSprite;

        Button(int x, int y);

        void setPosition(int x, int y);

        bool inInside(SDL_Event &e, SDL_Rect button);

        void render(SDL_Rect* currentClip , SDL_Renderer* gRenderer, LTexture &gButtonTexture);

    private:

        SDL_Point mPosition;
};
#endif // BUTTON_H
