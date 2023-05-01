#include "Button.h"

Button::Button(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

bool Button::inInside( SDL_Event& e, SDL_Rect button)
{
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(x < mPosition.x)
        {
            inside = false;
        }
        else if( x > mPosition.x + button.w)
        {
            inside = false;
        }
        else if( y < mPosition.y)
        {
            inside = false;
        }
        else if( y > mPosition.y + button.h)
        {
            inside = false;
        }
        return inside;
    }
    return false;
}

void Button::render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture &gButtonTexture)
{
    gButtonTexture.render(mPosition.x, mPosition.y, gRenderer, currentClip);
}
