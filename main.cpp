#include "Game_Base.h"
#include "Game_Utils.h"
#include "LTexture.h"
#include "Character.h"
#include "Enemy.h"
#include "Ammo.h"
#include "Explosion.h"

LTexture gGameTitleTexture;
LTexture gGround;
LTexture gBackgroundTexture[BACKGROUND_LAYER];
LTexture gCharacterTexture;
LTexture gCharacterFireTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gContinueButtonTexture;
LTexture gHomeButtonTexture;
LTexture gPlayAgainButtonTexture;
LTexture gInstructionTexture;
LTexture gPausedGameTexture;
LTexture gGameOverTexture;
LTexture gScoreTexture;
LTexture gHighScoreTexture;
LTexture gHP_img;
LTexture gHP_num;
LTexture gMP_img;
LTexture gMP_num;

TTF_Font* gFont = NULL;

Mix_Music* gMenuMusic = NULL;
Mix_Music* gInGameMusic = NULL;
Mix_Music* gGameOverMusic = NULL;
Mix_Chunk* gJump = NULL;
Mix_Chunk* gClick = NULL;
Mix_Chunk* gShoot = NULL;
Mix_Chunk* gHurt = NULL;
Mix_Chunk* gHit = NULL;
Mix_Chunk* gDie = NULL;

Character character;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
Button HomeButton(HOME_BUTTON_POSX, HOME_BUTTON_POSY);
Button PlayAgainButton(PLAY_AGAIN_BUTTON_POSX, PLAY_AGAIN_BUTTON_POSY);

const std::string LAYER[BACKGROUND_LAYER] = {
	"imgs/background/layer_sky.png",
    "imgs/background/layer_mountain.png",
    "imgs/background/layer_plain.png",
    "imgs/background/layer_grass.png",
    "imgs/background/layer_current.png",
    "imgs/background/layer_tree.png",
    "imgs/background/layer_ground.png"
};

SDL_Rect gCharacterClips[CHAR_FRAMES];
SDL_Rect gCharacterFireClips[CHAR_FIRE_FRAMES];
SDL_Rect gEnemy1Clips[ENEMY1_FRAMES];
SDL_Rect gEnemy2Clips[ENEMY2_FRAMES];
SDL_Rect gEnemy3Clips[ENEMY3_FRAMES];
SDL_Rect gEnemy4Clips[ENEMY4_FRAMES];
SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gHomeButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int main( int argc, char* argv[] )
{
    if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
		    bool quitGame = false;
		    while(!quitGame)
            {
                bool quitMenu = false;
                bool playAgain = false;
                Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
                std::vector <double> BaseSpeed_BackgroundMenu(BACKGROUND_LAYER, BASE_SPEED);
                while(!quitMenu)
                {
                    SDL_Event e;
                    while(SDL_PollEvent(&e) != 0)
                    {
                        if(e.type == SDL_QUIT)
                        {
                            quitMenu = true;
                            quitGame = true;
                        }
                        HandlePlayButton(e, PlayButton, gPlayButton[0], quitMenu, playAgain, gClick);
                        HandleHelpButton(e, HelpButton, gHelpButton[0], BackButton, gBackButton, gBackButtonTexture,
                                        gClick, gRenderer, BaseSpeed_BackgroundMenu, gBackgroundTexture,
                                        gInstructionTexture, quitMenu, quitGame);
                        HandleExitButton(e, ExitButton, gExitButton[0], quitMenu, quitGame, gClick);
                    }
                    if(!quitMenu)
                    {
                        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        SDL_RenderClear(gRenderer);
                        renderScrollingBackgroundMenu(BaseSpeed_BackgroundMenu, gBackgroundTexture, gRenderer);
                        gGameTitleTexture.render((SCREEN_WIDTH - gGameTitleTexture.getWidth())/2, 200 - gGameTitleTexture.getHeight(), gRenderer);
                        SDL_Rect* CurrentClip_Play = &gPlayButton[PlayButton.mCurrentSprite];
                        PlayButton.render(CurrentClip_Play, gRenderer, gPlayButtonTexture);
                        SDL_Rect* CurrentClip_Help = &gHelpButton[HelpButton.mCurrentSprite];
                        HelpButton.render(CurrentClip_Help, gRenderer, gHelpButtonTexture);
                        SDL_Rect* CurrentClip_Exit = &gExitButton[ExitButton.mCurrentSprite];
                        ExitButton.render(CurrentClip_Exit, gRenderer, gExitButtonTexture);
                        SDL_RenderPresent(gRenderer);
                    }
                }
                while(playAgain)
                {
                    Mix_PlayMusic(gInGameMusic, IS_REPEATITIVE);
                    srand(time(0));
                    bool quit = false;
                    bool GameState = true;
                    int time = 0;
                    int character_frame = 0;
                    int enemy1_frame = 0;
                    int enemy2_frame = 0;
                    int enemy3_frame = 0;
                    int enemy4_frame = 0;
                    int ammo_frame = 0;
                    int character_fire_frame = 0;
                    int score = 0;
                    int char_hp = 3;
                    int char_mp = 1;
                    int highScore = stoi(getHighScoreFromFile("high_score.txt"));
                    double BaseSpeed_Ground = BASE_SPEED;
                    std::vector <double> BaseSpeed_Background(BACKGROUND_LAYER, BASE_SPEED);
                    SDL_Event e;
                    Enemy enemy1(ENEMY_TYPE_1);
                    Enemy enemy2(ENEMY_TYPE_2);
                    Enemy enemy3(ENEMY_TYPE_3);
                    Enemy enemy4(ENEMY_TYPE_4);
                    GenerateEnemy(enemy1, enemy2, enemy3, enemy4, gRenderer);
                    int HP_temp1 = 0;
                    int HP_temp2 = 0;
                    Explosion Enemy1Explosion;
                    Explosion Enemy2Explosion;
                    Explosion Enemy3Explosion;
                    Explosion Enemy4Explosion;
                    Enemy1Explosion.loadFromFile("imgs/lon_rung.png", gRenderer);
                    Enemy2Explosion.loadFromFile("imgs/thich_khach.png", gRenderer);
                    Enemy3Explosion.loadFromFile("imgs/con_trung.png", gRenderer);
                    Enemy4Explosion.loadFromFile("imgs/dieu_hau.png", gRenderer);
                    int e1 = EXPLOSION_TIME;
                    int e2 = EXPLOSION_TIME;
                    int e3 = EXPLOSION_TIME;
                    int e4 = EXPLOSION_TIME;
                    while( !quit )
                    {
                        if(GameState)//for pause game
                        {
                            while( SDL_PollEvent( &e ) != 0 )
                            {
                                if( e.type == SDL_QUIT )
                                {
                                    quit = true;
                                    playAgain = false;
                                    quitGame = true;
                                }
                                HandlePauseButton(e, PauseButton, gPauseButton[0],
                                                    ContinueButton, gContinueButton, gContinueButtonTexture,
                                                    HomeButton, gHomeButton, gHomeButtonTexture, gPausedGameTexture,
                                                    GameState, gClick, gRenderer,
                                                    BackButton, gBackButton, gBackButtonTexture,
                                                    quit, playAgain, quitGame);
                                character.handleEvent(e, gJump, gShoot, gRenderer, char_mp);
                            }
                            if(!quit)
                            {
                                updateGameAndScore(time, score, highScore, enemy1, enemy2, enemy3, enemy4, gRenderer);
                                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                                SDL_RenderClear(gRenderer);
                                renderScrollingBackground(BaseSpeed_Background, gBackgroundTexture, gRenderer);
                                SDL_Rect* currentClip_Dart = NULL;
                                character.handleAmmo(gRenderer, ammo_frame, currentClip_Dart);
                                character.move();
                                SDL_Rect* currentClip_Enemy1 = NULL;
                                SDL_Rect* currentClip_Enemy2 = NULL;
                                SDL_Rect* currentClip_Enemy3 = NULL;
                                SDL_Rect* currentClip_Enemy4 = NULL;
                                std::set<Ammo*>  Darts = character.getAmmoList();
                                for(std::set<Ammo*>::iterator it = Darts.begin(); it!=Darts.end(); it++)
                                {
                                    Ammo* shot = *it;
                                    if(shot != NULL)
                                    {
                                        SDL_Rect shotRect;
                                        shotRect.x = shot->getPosX();
                                        shotRect.y = shot->getPosY();
                                        shotRect.w = 32;
                                        shotRect.h = 32;
                                        if (checkCollision2(*shot, shotRect, enemy1, gEnemy1Clips[0]) )
                                        {
                                            Mix_PlayChannel(MIX_CHANNEL, gHit, NOT_REPEATITIVE);
                                            Enemy1Explosion.setPos(enemy1.getPosX(), enemy1.getPosY());
                                            Enemy1Explosion.set_clip(gEnemy1Clips[3]);
                                            e1--;
                                            score += SCORE_INCREASEMENT_ENEMY1;
                                            character.removeAmmo(shot);
                                            char_mp++;
                                            enemy1.~Enemy();
                                        }
                                        else if (checkCollision2(*shot, shotRect, enemy2, gEnemy2Clips[0]) )
                                        {
                                            Mix_PlayChannel(MIX_CHANNEL, gHit, NOT_REPEATITIVE);
                                            Enemy2Explosion.setPos(enemy2.getPosX(), enemy2.getPosY());
                                            Enemy2Explosion.set_clip(gEnemy2Clips[3]);
                                            e2--;
                                            score += SCORE_INCREASEMENT_ENEMY2;
                                            character.removeAmmo(shot);
                                            char_mp++;
                                            enemy2.~Enemy();
                                        }
                                        else if (checkCollision2(*shot, shotRect, enemy3, gEnemy3Clips[0]) )
                                        {
                                            Mix_PlayChannel(MIX_CHANNEL, gHit, NOT_REPEATITIVE);
                                            Enemy3Explosion.setPos(enemy3.getPosX(), enemy3.getPosY());
                                            Enemy3Explosion.set_clip(gEnemy3Clips[3]);
                                            e3--;
                                            score += SCORE_INCREASEMENT_ENEMY3;
                                            character.removeAmmo(shot);
                                            char_mp++;
                                            enemy3.~Enemy();
                                        }
                                        else if (checkCollision2(*shot, shotRect, enemy4, gEnemy4Clips[0]) )
                                        {
                                            Mix_PlayChannel(MIX_CHANNEL, gHit, NOT_REPEATITIVE);
                                            Enemy4Explosion.setPos(enemy4.getPosX(), enemy4.getPosY());
                                            Enemy4Explosion.set_clip(gEnemy4Clips[3]);
                                            e4--;
                                            score += SCORE_INCREASEMENT_ENEMY4;
                                            character.removeAmmo(shot);
                                            char_mp++;
                                            enemy4.~Enemy();
                                        }
                                    }
                                }
                                if(e1<EXPLOSION_TIME)
                                {
                                    Enemy1Explosion.render(gRenderer);
                                    e1--;
                                    if(e1==0)   e1 = EXPLOSION_TIME;
                                }
                                if(e2<EXPLOSION_TIME)
                                {
                                    Enemy2Explosion.render(gRenderer);
                                    e2--;
                                    if(e2==0)   e2 = EXPLOSION_TIME;
                                }
                                if(e3<EXPLOSION_TIME)
                                {
                                    Enemy3Explosion.render(gRenderer);
                                    e3--;
                                    if(e3==0)   e3 = EXPLOSION_TIME;
                                }
                                if(e4<EXPLOSION_TIME)
                                {
                                    Enemy4Explosion.render(gRenderer);
                                    e4--;
                                    if(e4==0)   e4 = EXPLOSION_TIME;
                                }
                                if(!enemy1.check_Enemy_Deconstruct())
                                {
                                    currentClip_Enemy1 = &gEnemy1Clips[enemy1_frame / SLOW_FRAME_ENEMY1];
                                    enemy1.move();
                                    enemy1.render(gRenderer, currentClip_Enemy1);
                                }
                                if(!enemy2.check_Enemy_Deconstruct())
                                {
                                    currentClip_Enemy2 = &gEnemy2Clips[enemy2_frame / SLOW_FRAME_ENEMY2];
                                    enemy2.move();
                                    enemy2.render(gRenderer, currentClip_Enemy2);
                                }
                                if(!enemy3.check_Enemy_Deconstruct())
                                {
                                    currentClip_Enemy3 = &gEnemy3Clips[enemy3_frame / SLOW_FRAME_ENEMY3];
                                    enemy3.move();
                                    enemy3.render(gRenderer, currentClip_Enemy3);
                                }
                                if(!enemy4.check_Enemy_Deconstruct())
                                {
                                    currentClip_Enemy4 = &gEnemy4Clips[enemy4_frame / SLOW_FRAME_ENEMY4];
                                    enemy4.move();
                                    enemy4.render(gRenderer, currentClip_Enemy4);
                                }
                                SDL_Rect* currentClip_Character = NULL;
                                HP_temp2 = HP_temp1;
                                if(checkCollision1(character, gCharacterClips, enemy2, gEnemy2Clips) || checkCollision1(character, gCharacterClips, enemy1, gEnemy1Clips)
                                    || checkCollision1(character, gCharacterClips, enemy3, gEnemy3Clips) || checkCollision1(character, gCharacterClips, enemy4, gEnemy4Clips))
                                {
                                    if(HP_temp1 == 0)  Mix_PlayChannel(MIX_CHANNEL, gHurt, NOT_REPEATITIVE);
                                    HP_temp1++;
                                    currentClip_Character = &gCharacterClips[8];
                                    character.render(currentClip_Character, gRenderer, gCharacterTexture);
                                    updateHighScore("high_score.txt", highScore);
                                    SDL_Delay(40);
                                }
                                else if(HP_temp1 == HP_temp2 && HP_temp1>0)
                                {
                                    if(char_hp > 0) char_hp--;
                                    HP_temp1 = HP_temp2 = 0;
                                    currentClip_Character = &gCharacterClips[8];
                                    character.render(currentClip_Character, gRenderer, gCharacterTexture);
                                }
                                else if(character.isShooting())
                                {
                                    if(character.onGround())
                                    {
                                        currentClip_Character = &gCharacterFireClips[character_fire_frame / SLOW_FRAME_CHAR_FIRE];
                                        character.render(currentClip_Character, gRenderer, gCharacterFireTexture);
                                    }
                                    else if(character.isJumpingUp())
                                    {
                                        currentClip_Character = &gCharacterFireClips[4];
                                        character.render(currentClip_Character, gRenderer, gCharacterFireTexture);
                                    }
                                    else
                                    {
                                        currentClip_Character = &gCharacterFireClips[5];
                                        character.render(currentClip_Character, gRenderer, gCharacterFireTexture);
                                    }
                                }
                                else
                                {
                                    if (character.onGround())
                                    {
                                        currentClip_Character = &gCharacterClips[character_frame / SLOW_FRAME_CHAR];
                                        character.render(currentClip_Character, gRenderer, gCharacterTexture);
                                    }
                                    else if(character.isJumpingUp())
                                    {
                                        currentClip_Character = &gCharacterClips[6];
                                    }
                                    else
                                    {
                                        currentClip_Character = &gCharacterClips[7];
                                    }
                                    character.render(currentClip_Character, gRenderer, gCharacterTexture);
                                }
                                if(char_hp == 1 && HP_temp1 > 0)    Mix_PlayChannel(MIX_CHANNEL, gDie, NOT_REPEATITIVE);
                                renderCharacterPower(gHP_img, gMP_img, gHP_num, gMP_num, char_hp, char_mp, gRenderer, gFont);
                                SDL_Rect* CurrentClip_Pause = &gPauseButton[PauseButton.mCurrentSprite];
                                PauseButton.render(CurrentClip_Pause, gRenderer, gPauseButtonTexture);
                                renderScrollingGround(gGround, BaseSpeed_Ground, gRenderer);
                                DrawPlayerScore(gScoreTexture, score, gFont, gRenderer);
                                DrawPlayerHighScore(gHighScoreTexture, highScore, gFont, gRenderer);
                                SDL_RenderPresent(gRenderer);

                                ControlCharFrame(character_frame);
                                ControlEnemy1Frame(enemy1_frame);
                                ControlEnemy2Frame(enemy2_frame);
                                ControlEnemy3Frame(enemy3_frame);
                                ControlEnemy4Frame(enemy4_frame);
                                ControlAmmoFrame(ammo_frame);
                                ControlCharacterFireFrame(character_fire_frame, character);

                                if(char_hp == 0)
                                {
                                    Mix_PauseMusic();
                                    Mix_PlayMusic(gGameOverMusic, IS_REPEATITIVE);
                                   quit = true;
                                }

                            }
                        }
                    }
                    DrawEndGameSelection(e, gRenderer, gGameOverTexture, PlayAgainButton, gPlayAgainButton, gPlayAgainButtonTexture
                                         , HomeButton, gHomeButton, gHomeButtonTexture, gClick, playAgain, quitGame);
                    character.resetCharacter();
                    character.clearAmmos();
                    enemy1.~Enemy();
                    enemy2.~Enemy();
                    enemy3.~Enemy();
                    enemy4.~Enemy();
                    Enemy1Explosion.~Explosion();
                    Enemy2Explosion.~Explosion();
                    Enemy3Explosion.~Explosion();
                    Enemy4Explosion.~Explosion();
                }
            }
		}
    }
	close();
    return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Oda Run", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				#if defined (SDL_TTF_MAJOR_VERSION)
				if(TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",TTF_GetError());
                    success = false;
                }
                #endif
                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT ,2 , 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
			}
		}
	}

	return success;
}

bool loadMedia()
{
    bool success = true;
    if(!gGameTitleTexture.loadFromFile("imgs/game_title.png", gRenderer))
    {
        printf("Failed to render game title texture!\n");
        success = false;
    }
    if(!gGround.loadFromFile("imgs/ground.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","background.png",SDL_GetError());
        success = false;
    }
    for (int i = 0; i < BACKGROUND_LAYER; ++i)
    {
        if (!gBackgroundTexture[i].loadFromFile(LAYER[i].c_str(), gRenderer))
        {
            printf("Failed to load %s ! SDL Error: %s \n",LAYER[i].c_str(),SDL_GetError());
            success = false;
        }
    }
    if(!gCharacterTexture.loadFromFile("imgs/oda_animation.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","oda_animation.png",SDL_GetError());
        success = false;
    }
    else
    {
        gCharacterClips[0].x = 0;
        gCharacterClips[0].y = 0;
        gCharacterClips[0].w = 44;
        gCharacterClips[0].h = 68;

        gCharacterClips[1].x = 62;
        gCharacterClips[1].y = 0;
        gCharacterClips[1].w = 41;
        gCharacterClips[1].h = 68;

        gCharacterClips[2].x = 120;
        gCharacterClips[2].y = 0;
        gCharacterClips[2].w = 40;
        gCharacterClips[2].h = 68;

        gCharacterClips[3].x = 175;
        gCharacterClips[3].y = 0;
        gCharacterClips[3].w = 42;
        gCharacterClips[3].h = 68;

        gCharacterClips[4].x = 231;
        gCharacterClips[4].y = 0;
        gCharacterClips[4].w = 42;
        gCharacterClips[4].h = 68;

        gCharacterClips[5].x = 285;
        gCharacterClips[5].y = 0;
        gCharacterClips[5].w = 41;
        gCharacterClips[5].h = 68;

        gCharacterClips[6].x = 337;
        gCharacterClips[6].y = 0;
        gCharacterClips[6].w = 41;
        gCharacterClips[6].h = 68;

        gCharacterClips[7].x = 390;
        gCharacterClips[7].y = 0;
        gCharacterClips[7].w = 49;
        gCharacterClips[7].h = 68;

        gCharacterClips[8].x = 446;
        gCharacterClips[8].y = 0;
        gCharacterClips[8].w = 104;
        gCharacterClips[8].h = 68;
    }
    if(!gCharacterFireTexture.loadFromFile("imgs/oda_fire_animation.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","oda_fire_animation.png",SDL_GetError());
        success = false;
    }
    else
    {

        gCharacterFireClips[0].x = 0;
        gCharacterFireClips[0].y = 10;
        gCharacterFireClips[0].w = 47;
        gCharacterFireClips[0].h = 65;

        gCharacterFireClips[1].x = 47;
        gCharacterFireClips[1].y = 8;
        gCharacterFireClips[1].w = 47;
        gCharacterFireClips[1].h = 67;

        gCharacterFireClips[2].x = 95;
        gCharacterFireClips[2].y = 9;
        gCharacterFireClips[2].w = 43;
        gCharacterFireClips[2].h = 66;

        gCharacterFireClips[3].x = 138;
        gCharacterFireClips[3].y = 7;
        gCharacterFireClips[3].w = 48;
        gCharacterFireClips[3].h = 68;

        gCharacterFireClips[4].x = 193;
        gCharacterFireClips[4].y = 0;
        gCharacterFireClips[4].w = 45;
        gCharacterFireClips[4].h = 75;

        gCharacterFireClips[5].x = 243;
        gCharacterFireClips[5].y = 0;
        gCharacterFireClips[5].w = 45;
        gCharacterFireClips[5].h = 75;

    }
    if(!gPlayButtonTexture.loadFromFile("imgs/play_button.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","play_button.png",SDL_GetError());
        success = false;
    }
    else
    {
        gPlayButton[0].x = 0;
        gPlayButton[0].y = 0;
        gPlayButton[0].w = 107;
        gPlayButton[0].h = 109;

        gPlayButton[1].x = 107;
        gPlayButton[1].y = 0;
        gPlayButton[1].w = 107;
        gPlayButton[1].h = 109;
    }
    if(!gHelpButtonTexture.loadFromFile("imgs/help_button.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","help_button.png",SDL_GetError());
        success = false;
    }
    else
    {
        gHelpButton[0].x = 0;
        gHelpButton[0].y = 0;
        gHelpButton[0].w = 107;
        gHelpButton[0].h = 109;

        gHelpButton[1].x = 107;
        gHelpButton[1].y = 0;
        gHelpButton[1].w = 107;
        gHelpButton[1].h = 109;
    }
    if(!gExitButtonTexture.loadFromFile("imgs/exit_button.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","exit_button.png",SDL_GetError());
        success = false;
    }
    else
    {
        gExitButton[0].x = 0;
        gExitButton[0].y = 0;
        gExitButton[0].w = 107;
        gExitButton[0].h = 109;

        gExitButton[1].x = 107;
        gExitButton[1].y = 0;
        gExitButton[1].w = 107;
        gExitButton[1].h = 109;
    }
    if(!gBackButtonTexture.loadFromFile("imgs/back_button.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","back_button.png",SDL_GetError());
        success = false;
    }
    else
    {
        gBackButton[0].x = 0;
        gBackButton[0].y = 0;
        gBackButton[0].w = 72;
        gBackButton[0].h = 72;

        gBackButton[1].x = 72;
        gBackButton[1].y = 0;
        gBackButton[1].w = 71;
        gBackButton[1].h = 72;
    }
    if(!gPauseButtonTexture.loadFromFile("imgs/pause_button.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","pause_button.png",SDL_GetError());
        success = false;
    }
    else
    {
        gPauseButton[0].x = 0;
        gPauseButton[0].y = 0;
        gPauseButton[0].w = 72;
        gPauseButton[0].h = 72;

        gPauseButton[1].x = 72;
        gPauseButton[1].y = 0;
        gPauseButton[1].w = 71;
        gPauseButton[1].h = 72;
    }
    if(!gContinueButtonTexture.loadFromFile("imgs/continue_button.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","continue_button.png",SDL_GetError());
        success = false;
    }
    else
    {
        gContinueButton[0].x = 0;
        gContinueButton[0].y = 0;
        gContinueButton[0].w = 107;
        gContinueButton[0].h = 109;

        gContinueButton[1].x = 107;
        gContinueButton[1].y = 0;
        gContinueButton[1].w = 107;
        gContinueButton[1].h = 109;
    }
    if(!gHomeButtonTexture.loadFromFile("imgs/home_button.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","home_button.png",SDL_GetError());
        success = false;
    }
    else
    {
        gHomeButton[0].x = 0;
        gHomeButton[0].y = 0;
        gHomeButton[0].w = 107;
        gHomeButton[0].h = 109;

        gHomeButton[1].x = 107;
        gHomeButton[1].y = 0;
        gHomeButton[1].w = 107;
        gHomeButton[1].h = 109;
    }
    if(!gPlayAgainButtonTexture.loadFromFile("imgs/play_again_button.png",gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","play_again_button.png",SDL_GetError());
        success = false;
    }
    else
    {
        gPlayAgainButton[0].x = 0;
        gPlayAgainButton[0].y = 0;
        gPlayAgainButton[0].w = 107;
        gPlayAgainButton[0].h = 109;

        gPlayAgainButton[1].x = 107;
        gPlayAgainButton[1].y = 0;
        gPlayAgainButton[1].w = 107;
        gPlayAgainButton[1].h = 109;
    }
    if(!gInstructionTexture.loadFromFile("imgs/instruction.png", gRenderer))
    {
        printf("Failed to render instruction texture!\n");
        success = false;
    }
    if(!gPausedGameTexture.loadFromFile("imgs/paused.png", gRenderer))
    {
        printf("Failed to render paused game texture!\n");
        success = false;
    }
    if(!gGameOverTexture.loadFromFile("imgs/gameover.png", gRenderer))
    {
        printf("Faild to render Game over texture!\n");
        success = false;
    }
    if(!gHP_img.loadFromFile("imgs/hp.png", gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","hp.png",SDL_GetError());
        success = false;
    }
    if(!gMP_img.loadFromFile("imgs/mp.png", gRenderer))
    {
        printf("Failed to load %s ! SDL Error: %s \n","mp.png",SDL_GetError());
        success = false;
    }
    //
    gFont = TTF_OpenFont("njnaruto.ttf", 20);
    if(gFont == NULL)
    {
        printf("Failed to load ninja font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    //
    gMenuMusic = Mix_LoadMUS("sounds/menu_music.mp3");
    if(gMenuMusic == NULL)
    {
        printf( "Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gInGameMusic = Mix_LoadMUS("sounds/in-game_music.mp3");
    if(gInGameMusic == NULL)
    {
        printf( "Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gGameOverMusic = Mix_LoadMUS("sounds/game_over_music.mp3");
    if(gGameOverMusic == NULL)
    {
        printf( "Failed to load game over music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gJump = Mix_LoadWAV("sounds/jump.wav");
    if(gJump == NULL)
    {
        printf( "Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gClick = Mix_LoadWAV("sounds/mouse_click.wav");
    if(gClick == NULL)
    {
        printf( "Failed to load click sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gShoot = Mix_LoadWAV("sounds/shoot.wav");
    if(gShoot == NULL)
    {
        printf( "Failed to load shoot sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gHurt = Mix_LoadWAV("sounds/hurt.wav");
    if(gHurt == NULL)
    {
        printf( "Failed to load hurt sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gHit = Mix_LoadWAV("sounds/hit.wav");
    if(gHit == NULL)
    {
        printf( "Failed to load hit sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gDie = Mix_LoadWAV("sounds/die.wav");
    if(gDie == NULL)
    {
        printf( "Failed to load die sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    //Loading EnemyClips
    //Enemy1
	gEnemy1Clips[0].x = 0;
    gEnemy1Clips[0].y = 0;
    gEnemy1Clips[0].w = 114;
    gEnemy1Clips[0].h = 74;

    gEnemy1Clips[1].x = 122;
    gEnemy1Clips[1].y = 1;
    gEnemy1Clips[1].w = 108;
    gEnemy1Clips[1].h = 73;

    gEnemy1Clips[2].x = 235;
    gEnemy1Clips[2].y = 1;
    gEnemy1Clips[2].w = 109;
    gEnemy1Clips[2].h = 73;

    gEnemy1Clips[3].x = 352;
    gEnemy1Clips[3].y = 0;
    gEnemy1Clips[3].w = 145;
    gEnemy1Clips[3].h = 74;

	//Enemy2
    gEnemy2Clips[0].x = 0;
    gEnemy2Clips[0].y = 0;
    gEnemy2Clips[0].w = 40;
    gEnemy2Clips[0].h = 70;

    gEnemy2Clips[1].x = 52;
    gEnemy2Clips[1].y = 0;
    gEnemy2Clips[1].w = 41;
    gEnemy2Clips[1].h = 70;

    gEnemy2Clips[2].x = 101;
    gEnemy2Clips[2].y = 0;
    gEnemy2Clips[2].w = 64;
    gEnemy2Clips[2].h = 70;

    gEnemy2Clips[3].x = 189;
    gEnemy2Clips[3].y = 0;
    gEnemy2Clips[3].w = 63;
    gEnemy2Clips[3].h = 70;

    //Enemy3
    gEnemy3Clips[0].x = 0;
    gEnemy3Clips[0].y = 12;
    gEnemy3Clips[0].w = 40;
    gEnemy3Clips[0].h = 38;

    gEnemy3Clips[1].x = 45;
    gEnemy3Clips[1].y = 12;
    gEnemy3Clips[1].w = 38;
    gEnemy3Clips[1].h = 38;

    gEnemy3Clips[2].x = 88;
    gEnemy3Clips[2].y = 12;
    gEnemy3Clips[2].w = 42;
    gEnemy3Clips[2].h = 38;

    gEnemy3Clips[3].x = 137;
    gEnemy3Clips[3].y = 0;
    gEnemy3Clips[3].w = 58;
    gEnemy3Clips[3].h = 50;
    //Enemy4
    gEnemy4Clips[0].x = 0;
    gEnemy4Clips[0].y = 0;
    gEnemy4Clips[0].w = 76;
    gEnemy4Clips[0].h = 75;

    gEnemy4Clips[1].x = 84;
    gEnemy4Clips[1].y = 0;
    gEnemy4Clips[1].w = 97;
    gEnemy4Clips[1].h = 75;

    gEnemy4Clips[2].x = 199;
    gEnemy4Clips[2].y = 0;
    gEnemy4Clips[2].w = 74;
    gEnemy4Clips[2].h = 96;

    gEnemy4Clips[3].x = 278;
    gEnemy4Clips[3].y = 0;
    gEnemy4Clips[3].w = 112;
    gEnemy4Clips[3].h = 92;
    return success;
}
void close()
{
    gGameTitleTexture.free();
    gGround.free();
    for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		gBackgroundTexture[i].free();
	}
    gCharacterTexture.free();
    gCharacterFireTexture.free();
    gPlayButtonTexture.free();
    gHelpButtonTexture.free();
    gExitButtonTexture.free();
    gBackButtonTexture.free();
    gPauseButtonTexture.free();
    gContinueButtonTexture.free();
    gHomeButtonTexture.free();
    gPlayAgainButtonTexture.free();
    gInstructionTexture.free();
    gPausedGameTexture.free();
    gGameOverTexture.free();
    gScoreTexture.free();
    gHighScoreTexture.free();
    gHP_img.free();
    gHP_num.free();
    gMP_img.free();
    gMP_num.free();

    TTF_CloseFont(gFont);
    gFont = NULL;

    Mix_FreeMusic(gMenuMusic);
    gMenuMusic = NULL;
    Mix_FreeMusic(gInGameMusic);
    gInGameMusic = NULL;
    Mix_FreeMusic(gGameOverMusic);
    gInGameMusic = NULL;
    Mix_FreeChunk(gJump);
    gJump = NULL;
    Mix_FreeChunk(gClick);
    gClick = NULL;
    Mix_FreeChunk(gShoot);
    gShoot = NULL;
    Mix_FreeChunk(gHurt);
    gHurt = NULL;
    Mix_FreeChunk(gHit);
    gHit = NULL;
    Mix_FreeChunk(gDie);
    gDie = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gRenderer = NULL;
    gWindow = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}
