#include "Enemy.h"

Enemy::Enemy(int _type)
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = _type;
	if (type == ENEMY_TYPE_1)
	{
		posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = GROUND - ENEMY1_HEIGHT;
	}
	else if (type == ENEMY_TYPE_2)
    {
        posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = GROUND - ENEMY2_HEIGHT + 4;
    }
    else if (type == ENEMY_TYPE_3)
    {
        posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = 250;//rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
    }
	else if (type == ENEMY_TYPE_4)
    {
        posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + (ENEMY_MIN_HEIGHT );
    }

	enemyTexture = NULL;
}

Enemy::~Enemy()
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	if (enemyTexture != NULL)
	{
		enemyTexture = NULL;
	}
}

void Enemy::reConstructor(int _type)
{
    posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = _type;
	if (type == ENEMY_TYPE_1)
	{
		posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = GROUND - ENEMY1_HEIGHT;
	}
	else if (type == ENEMY_TYPE_2)
    {
        posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = GROUND - ENEMY2_HEIGHT + 4;
    }
    else if (type == ENEMY_TYPE_3)
    {
        posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = 250;//rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
    }
	else if (type == ENEMY_TYPE_4)
    {
        posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + (ENEMY_MIN_HEIGHT );
    }

	enemyTexture = NULL;
}

bool Enemy::check_Enemy_Deconstruct()
{
    return enemyTexture == NULL;
}

void Enemy::loadFromFile(std::string path, SDL_Renderer* gRenderer)
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
			eWidth = tmpSurface->w;
			eHeight = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	enemyTexture = tmpTexture;
}

void Enemy::move()
{
    int t = time(0);
	if(type == ENEMY_TYPE_1) posX += -ENEMY1_SPEED;
	else if(type == ENEMY_TYPE_3)
    {
        posX += -ENEMY2_SPEED ;
        //posY += 2*cos(10*t);
    }
    else if(type == ENEMY_TYPE_4)
    {
        posX += -ENEMY2_SPEED ;
        posY += 2*sin(10*t);
    }
	else                     posX += -ENEMY2_SPEED;
	if (posX + 200< 0)
	{
		posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;

		if (type == ENEMY_TYPE_4 )//|| type == ENEMY_TYPE_3)
		{
			posY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
		}
	}
}

void Enemy::render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
	SDL_Rect renderSpace = { posX, posY, eWidth, eHeight };
	if (currentClip != NULL)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, enemyTexture, currentClip, &renderSpace);
}

int Enemy::getType()
{
	return type;
}

int Enemy::getPosX()
{
	return posX;
}

int Enemy::getPosY()
{
	return posY;
}

int Enemy::getWidth()
{
	return eWidth;
}

int Enemy::getHeight()
{
	return eHeight;
}
