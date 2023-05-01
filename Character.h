#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Game_base.h"
#include "LTexture.h"
#include "Ammo.h"


#define JUMP 1
#define FALL 3
#define RUN	0
#define CHARACTER_HEIGHT 68
class Character
{
    public:
        static const int JUMP_SPEED = 6;
        static const int FALL_SPEED = 6;

        Character();

        void resetCharacter();

        bool onGround();

        bool isJumpingUp();

        bool isShooting();

        void getStatus(bool status);

        void handleEvent(SDL_Event& e, Mix_Chunk* gJump, Mix_Chunk* gShoot, SDL_Renderer* gRenderer, int &char_mp);

        void handleAmmo(SDL_Renderer* gRenderer, int &dart_frame, SDL_Rect* currentClip_Dart);

        void removeAmmo(Ammo* shot);

        void move();

        void render(SDL_Rect* currentClip , SDL_Renderer *gRenderer, LTexture &gCharacterTexture);

        std::set<Ammo*> getAmmoList();

        void clearAmmos();

        int getPosX();

        int getPosY();


    private:
        std::set<Ammo*> ammos;

        int posX, posY;

        int status;

        bool shootStatus;

        bool jumpStatus;
};

#endif // !CHARACTER_H_
