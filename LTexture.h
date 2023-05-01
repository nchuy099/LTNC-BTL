#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include "Game_Base.h"

class LTexture
{
	public:

        LTexture();

		~LTexture();

        bool loadFromFile( std::string path , SDL_Renderer* gRenderer );

		#if defined(SDL_TTF_MAJOR_VERSION)
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* gRenderer );
		#endif

		void free();

		void render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);

		int getWidth();

		int getHeight();


	private:
		SDL_Texture* mTexture;

		int mWidth;

		int mHeight;
};

#endif // LTEXTURE_H_
