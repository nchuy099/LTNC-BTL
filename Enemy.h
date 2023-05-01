#ifndef ENEMY_H_
#define ENEMY_H_

#include "LTexture.h"
#include "Game_base.h"


#define ENEMY_MAX_HEIGHT 150
#define ENEMY_MIN_HEIGHT 200

#define ENEMY_POSITION_RANGE 450

#define ENEMY1_HEIGHT 73
#define ENEMY2_HEIGHT 70


class Enemy
{
    public:
        Enemy(int _type );

        ~Enemy();

        void reConstructor(int _type);

        bool check_Enemy_Deconstruct();

        void loadFromFile(std::string path, SDL_Renderer* gRenderer);

        void move();

        void render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = NULL);

        int getType();

        int getPosX();

        int getPosY();

        int getWidth();

        int getHeight();

    private:

        int posX, posY;

        int eWidth, eHeight;

        int type;

        SDL_Texture *enemyTexture;
};

#endif // !ENEMY_H_
