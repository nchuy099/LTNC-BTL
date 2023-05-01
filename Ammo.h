#ifndef AMMO_H
#define AMMO_H

#include "Game_base.h"

class Ammo
{
    public:

        static const int AMMO_VEL = 3;
        Ammo();

        ~Ammo();

        void loadFromFile(std::string path, SDL_Renderer* gRenderer);

        void setMove(bool is_move);

        bool getMove();

        void move();

        void render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = NULL);

        void setPos(int x, int y);

        int getPosX();

        int getPosY();

        int getWidth();

        int getHeight();

    private:
        int posX;

        int posY;

        int width, height;

        bool isMove;

        SDL_Texture* ammoTexture;
};
#endif // AMMO_H
