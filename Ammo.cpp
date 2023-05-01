#include "Ammo.h"

Ammo::Ammo()
{
    posX = 0;
	posY = 0;
    isMove = false;
}

Ammo::~Ammo()
{
    posX = 0;
	posY = 0;
    isMove = false;
    if(ammoTexture != NULL) ammoTexture = NULL;
}

void Ammo::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	SDL_Texture* tmpTexture = NULL;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if (tmpSurface == NULL)
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == NULL)
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			width = tmpSurface->w;
			height = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	ammoTexture = tmpTexture;
}

void Ammo::setMove(bool is_Move)
{
    isMove = is_Move;
}

bool Ammo::getMove()
{
    return isMove;

}

void Ammo::move()
{
    posX += AMMO_VEL;
    if(posX > SCREEN_WIDTH)
    {
        isMove = false;
    }
}

void Ammo::render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
    SDL_Rect renderSpace = {posX, posY, width, height};
	if (currentClip != NULL)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, ammoTexture, currentClip, &renderSpace);
}

void Ammo::setPos(int x, int y)
{
    posX = x;
    posY = y;
}

int Ammo::getPosX()
{
	return posX;
}

int Ammo::getPosY()
{
	return posY;
}

int Ammo::getWidth()
{
	return width;
}

int Ammo::getHeight()
{
	return height;
}
