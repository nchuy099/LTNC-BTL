#include "Explosion.h"

Explosion::Explosion()
{
    posX = 0;
    posY = 0;
    explosionTexture = NULL;
}

Explosion::~Explosion()
{
    posX = 0;
    posY = 0;
	if (explosionTexture != NULL)
	{
		explosionTexture = NULL;
	}
}

void Explosion::loadFromFile(std::string path, SDL_Renderer* gRenderer)
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
		SDL_FreeSurface(tmpSurface);
	}
	explosionTexture = tmpTexture;
}

void Explosion::set_clip(SDL_Rect Clip)
{
    FrameClips = Clip;
}


void Explosion::render(SDL_Renderer* gRenderer)
{
    SDL_Rect* currentClip = &FrameClips;
	SDL_Rect renderSpace = { posX, posY, 0, 0};
	if (currentClip != NULL)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, explosionTexture, currentClip, &renderSpace);
}


void Explosion::setPos(const int x, const int y)
{
    posX = x;
    posY = y;
}



