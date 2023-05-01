#include "Character.h"

Character::Character()
{
	posX = SCREEN_WIDTH - 700;
	posY = GROUND - CHARACTER_HEIGHT + 3 ;
	status = 0;
	jumpStatus = false;
	shootStatus = false;
}

void Character::resetCharacter()
{
	posX = SCREEN_WIDTH - 700;
	posY = GROUND - CHARACTER_HEIGHT + 3 ;
	status = 0;
	jumpStatus = false;
}

bool Character::onGround()
{
	return posY == GROUND - CHARACTER_HEIGHT + 3 ;
}

bool Character::isJumpingUp()
{
    return jumpStatus ;
}

bool Character::isShooting()
{
    return shootStatus ;
}

void Character::getStatus(bool status)
{
    shootStatus = status;
}

void Character::handleEvent(SDL_Event& e,Mix_Chunk* gJump, Mix_Chunk* gShoot, SDL_Renderer* gRenderer, int &char_mp)
{
    if(e.type == SDL_KEYDOWN )
    {
        switch(e.key.keysym.sym )
        {
                case SDLK_UP:
                    if (onGround())
                    {
                        Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                        status = JUMP;
                    }
                    break;
                case SDLK_s:
                    if(e.key.repeat == 0 && char_mp > 0 )
                    {
                        shootStatus = true;
                        Mix_PlayChannel(MIX_CHANNEL, gShoot, NOT_REPEATITIVE);
                        Ammo* dart = new Ammo();
                        dart->loadFromFile("imgs/dart.png",gRenderer);
                        dart->setMove(true);
                        dart->setPos(posX + 40, posY + 20);
                        ammos.insert(dart);
                        char_mp--;
                    }
                    break;
        }
    }

}

void Character::handleAmmo(SDL_Renderer* gRenderer, int &dart_frame, SDL_Rect* currentClip_Dart)
{
    SDL_Rect dartClips[DART_FRAMES];
    dartClips[0].x = 0;
    dartClips[0].y = 0;
    dartClips[0].w = 32;
    dartClips[0].h = 32;

    dartClips[1].x = 0;
    dartClips[1].y = 33;
    dartClips[1].w = 32;
    dartClips[1].h = 31;

    dartClips[2].x = 0;
    dartClips[2].y = 68;
    dartClips[2].w = 32;
    dartClips[2].h = 26;

    dartClips[3].x = 0;
    dartClips[3].y = 94;
    dartClips[3].w = 32;
    dartClips[3].h = 32;

    dartClips[4].x = 0;
    dartClips[4].y = 127;
    dartClips[4].w = 32;
    dartClips[4].h = 31;

    dartClips[5].x = 0;
    dartClips[5].y = 162;
    dartClips[5].w = 32;
    dartClips[5].h = 26;

    dartClips[6].x = 0;
    dartClips[6].y = 188;
    dartClips[6].w = 32;
    dartClips[6].h = 32;

    dartClips[7].x = 0;
    dartClips[7].y = 221;
    dartClips[7].w = 32;
    dartClips[7].h = 31;

    dartClips[8].x = 0;
    dartClips[8].y = 256;
    dartClips[8].w = 32;
    dartClips[8].h = 26;
    for(std::set<Ammo*>::iterator it = ammos.begin(); it!=ammos.end(); it++)
    {
        Ammo* shot = *it;
        if(shot != NULL)
        {
            if(shot->getMove())
            {
                shot->move();
                currentClip_Dart = &dartClips[dart_frame/SLOW_FRAME_DART];
                shot->render(gRenderer, currentClip_Dart);
            }
            else
            {
                ammos.erase(it);
                if(shot != NULL)
                {
                    delete shot;
                    shot = NULL;
                }
            }
        }
    }
}

void Character::removeAmmo(Ammo* shot)
{
    if(ammos.count(shot) !=0)
    {
        ammos.erase(shot);
        if(shot != NULL)
        {
            delete shot;
            shot = NULL;
        }
    }
}
void Character::move()
{
	if (status == JUMP && posY >= MAX_HEIGHT)
	{
		posY += -JUMP_SPEED ;
        jumpStatus = true;
	}
	if (posY <= MAX_HEIGHT )
	{
		status = FALL;
	}
	if (status == FALL && posY <  GROUND - CHARACTER_HEIGHT + 3 )
	{
		posY += FALL_SPEED ;
		jumpStatus = false;
	}
}

void Character::render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture &gCharacterTexture)
{
	gCharacterTexture.render(posX, posY, gRenderer, currentClip);
}

std::set<Ammo*> Character::getAmmoList()
{
    return ammos;
}

void Character::clearAmmos()
{
    for(std::set<Ammo*>::iterator it = ammos.begin(); it != ammos.end(); it++)
    {
        (**it).~Ammo();
    }
    ammos.clear();
}
int Character::getPosX()
{
	return posX;
}

int Character::getPosY()
{
	return posY;
}
