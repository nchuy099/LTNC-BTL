#include "Game_Utils.h"

std::string getHighScoreFromFile(std::string path)
{
    std::ifstream infile(path);
    std::string  highScore;
    if(infile.is_open())
    {
        infile >> highScore;
        infile.close();
    }
    else
    {
        printf("Unable to open High Score file");
    }
    return highScore;
}

void updateHighScore(std::string path, const int &highScore)
{
    std::string HighScore = std::to_string(highScore);
    std::ofstream outfile(path);
    if(outfile.is_open())
    {
        outfile << HighScore;
        outfile.close();
    }
}

void GenerateEnemy(Enemy &enemy1, Enemy &enemy2, Enemy &enemy3, Enemy &enemy4, SDL_Renderer* gRenderer)
{
	enemy1.loadFromFile("imgs/lon_rung.png", gRenderer);
	enemy2.loadFromFile("imgs/thich_khach.png", gRenderer);
	enemy3.loadFromFile("imgs/con_trung.png", gRenderer);
	enemy4.loadFromFile("imgs/dieu_hau.png", gRenderer);

}
void updateGameAndScore(int &time, int &score, int &highScore, Enemy &enemy1, Enemy &enemy2, Enemy &enemy3, Enemy &enemy4, SDL_Renderer* gRenderer )
{
    if(time % 15 == 0)
    {
        score += SCORE_INCREASEMENT;
    }
    time += TIME_INCREASEMENT;
    if(score > highScore)
    {
        highScore = score;
    }
    if(enemy1.check_Enemy_Deconstruct())
    {
        enemy1.reConstructor(ENEMY_TYPE_1);
        enemy1.loadFromFile("imgs/lon_rung.png", gRenderer);
    }
    if(enemy2.check_Enemy_Deconstruct())
    {
        enemy2.reConstructor(ENEMY_TYPE_2);
        enemy2.loadFromFile("imgs/thich_khach.png", gRenderer);
    }
    if(enemy3.check_Enemy_Deconstruct())
    {
        enemy3.reConstructor(ENEMY_TYPE_3);
        enemy3.loadFromFile("imgs/con_trung.png", gRenderer);
    }
    if(enemy4.check_Enemy_Deconstruct())
    {
        enemy4.reConstructor(ENEMY_TYPE_4);
        enemy4.loadFromFile("imgs/dieu_hau.png", gRenderer);
    }
}

void renderScrollingBackgroundMenu(std::vector <double>& BaseSpeed_Background,
	LTexture gBackgroundTexture[],
	SDL_Renderer* gRenderer)
{
	std::vector <double> layer_speed;
	layer_speed.push_back(0.4);
	layer_speed.push_back(0.4);
	layer_speed.push_back(0.4);
	layer_speed.push_back(0.4);
    layer_speed.push_back(LAYER_5_SPEED);
	layer_speed.push_back(0.7);
	layer_speed.push_back(0.7);
	for (int i = 0; i < BACKGROUND_LAYER ; i++)
	{
	    if(i !=4 && i!=5 )
        {
            BaseSpeed_Background[i] -= layer_speed[i];
            if (BaseSpeed_Background[i] < -gBackgroundTexture[i].getWidth())
            {
                BaseSpeed_Background[i] = 0;
            }
            gBackgroundTexture[i].render(BaseSpeed_Background[i], 0, gRenderer);
            gBackgroundTexture[i].render(BaseSpeed_Background[i] + gBackgroundTexture[i].getWidth(), 0, gRenderer);
	    }
	}

}

void HandlePlayButton(SDL_Event &e, Button &PlayButton, SDL_Rect gPlayButton, bool &quitMenu, bool &playAgain, Mix_Chunk* gClick)
{
    if(PlayButton.inInside(e, gPlayButton))
    {
        if(e.type == SDL_MOUSEMOTION)
        {
            PlayButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
            PlayButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
            quitMenu = true;
            playAgain = true;
        }
    }
    else
    {
        PlayButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }
}
void HandleHelpButton(SDL_Event &e, Button &HelpButton, SDL_Rect gHelpButton,Button &BackButton, SDL_Rect gBackButton[], LTexture &gBackButtonTexture,
                      Mix_Chunk* gClick, SDL_Renderer* gRenderer, std::vector <double> &OffsetSpeed_BackgroundMenu, LTexture gBackgroundTexture[],
                      LTexture &gInstructionTexture, bool &quitMenu, bool &quitGame)
{
    if(HelpButton.inInside(e, gHelpButton))
    {
        if(e.type == SDL_MOUSEMOTION)
        {
            HelpButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
            HelpButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
            HandleBackButton(e, BackButton, gBackButton, gBackButtonTexture, gClick, gRenderer, OffsetSpeed_BackgroundMenu, gBackgroundTexture, gInstructionTexture, quitMenu, quitGame);
        }
    }
    else
    {
        HelpButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }
}

void HandleBackButton(SDL_Event &e, Button &BackButton, SDL_Rect gBackButton[], LTexture &gBackButtonTexture,
                      Mix_Chunk* gClick, SDL_Renderer* gRenderer, std::vector <double> &OffsetSpeed_BackgroundMenu, LTexture gBackgroundTexture[],
                      LTexture &gInstructionTexture, bool &quitMenu, bool &quitGame)
{
    bool readIns = true;
    while(readIns &&  !quitMenu && !quitGame)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quitMenu = true;
                quitGame = true;
            }
            if(BackButton.inInside(e, gBackButton[0]))
            {
                if(e.type == SDL_MOUSEMOTION)
                {
                    BackButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
                }
                else if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                    BackButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
                    readIns = false;
                }
            }
            else
            {
                BackButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        renderScrollingBackgroundMenu(OffsetSpeed_BackgroundMenu, gBackgroundTexture, gRenderer);
        SDL_Rect* CurrentClip_Back = &gBackButton[BackButton.mCurrentSprite];
        BackButton.render(CurrentClip_Back, gRenderer, gBackButtonTexture);
        gInstructionTexture.render((SCREEN_WIDTH - gInstructionTexture.getWidth())/2, (SCREEN_HEIGHT - gInstructionTexture.getHeight())/2 - 50, gRenderer);
        SDL_RenderPresent(gRenderer);
    }
}
void HandleExitButton(SDL_Event &e, Button &ExitButton, SDL_Rect gExitButton, bool &quitMenu, bool &quitGame, Mix_Chunk* gClick)
{
    if(ExitButton.inInside(e, gExitButton))
    {
        if(e.type == SDL_MOUSEMOTION)
        {
            ExitButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
            ExitButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
            quitMenu = true;
            quitGame = true;
        }
    }
    else
    {
        ExitButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }
}

void HandleContinueButton(SDL_Event &e, Button &ContinueButton, SDL_Rect gContinueButton[], LTexture &gContinueButtonTexture,
                          Button &HomeButton, SDL_Rect gHomeButton[], LTexture &gHomeButtonTexture,
                        LTexture &gPausedGameTexture, bool &GameState, Mix_Chunk* gClick, SDL_Renderer* gRenderer, bool &quit, bool &playAgain, bool &quitGame)
{
	while (!GameState && !quit && !quitGame)
	{
		while(SDL_PollEvent(&e) != 0)
		{
		    if(e.type == SDL_QUIT)
		    {
		        quit = true;
		        playAgain = false;
		        quitGame = true;
		    }
			if(ContinueButton.inInside(e, gContinueButton[0]))
            {
                if(e.type == SDL_MOUSEMOTION)
                {
                    ContinueButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
                }
                else if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                    ContinueButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
                    GameState = true;
                }
            }
            else
            {
                ContinueButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
            }
            if(HomeButton.inInside(e, gHomeButton[0]))
            {
                if(e.type == SDL_MOUSEMOTION)
                {
                    HomeButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
                }
                else if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                    HomeButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
                    quit = true;
                    playAgain = false;
                }
            }
            else
            {
                HomeButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
            }
		}
        gPausedGameTexture.render((SCREEN_WIDTH - gPausedGameTexture.getWidth()) / 2, PAUSED_GAME_POSY, gRenderer);
        SDL_Rect* CurrentClip_Continue = &gContinueButton[ContinueButton.mCurrentSprite];
        ContinueButton.render(CurrentClip_Continue, gRenderer, gContinueButtonTexture);
        SDL_Rect* CurrentClip_Home = &gHomeButton[HomeButton.mCurrentSprite];
        HomeButton.render(CurrentClip_Home, gRenderer, gHomeButtonTexture);

        SDL_RenderPresent(gRenderer);
	}
}

void HandlePauseButton(SDL_Event &e, Button &PauseButton, SDL_Rect gPauseButton, Button &ContinueButton, SDL_Rect gContinueButton[], LTexture &gContinueButtonTexture,
                       Button &HomeButton, SDL_Rect gHomeButton[], LTexture &gHomeButtonTexture,
                       LTexture &gPausedMenuTexture, bool &GameState, Mix_Chunk* gClick, SDL_Renderer* gRenderer, bool &quit, bool &playAgain, bool &quitGame)
{
    if(PauseButton.inInside(e, gPauseButton))
    {
        if(e.type == SDL_MOUSEMOTION)
        {
            PauseButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
            PauseButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
        }
        else if(e.type == SDL_MOUSEBUTTONUP)
        {
            GameState = false;
            HandleContinueButton(e, ContinueButton, gContinueButton, gContinueButtonTexture,
                                 HomeButton, gHomeButton, gHomeButtonTexture, gPausedMenuTexture, GameState, gClick, gRenderer, quit, playAgain, quitGame);
        }
    }
    else
    {
        PauseButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }
}

void DrawEndGameSelection(SDL_Event &e, SDL_Renderer* gRenderer, LTexture &gGameOverTexture, Button &PlayAgainButton, SDL_Rect gPlayAgainButton[], LTexture &gPlayAgainButtonTexture,
                                                    Button &HomeButton, SDL_Rect gHomeButton[], LTexture &gHomeButtonTexture, Mix_Chunk* gClick, bool &playAgain, bool &quitGame)
{
    if (playAgain)
	{
		bool End_Game = true;
		while (End_Game)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					playAgain = false;
                    quitGame = true;
                    End_Game = false;
				}
                if(PlayAgainButton.inInside(e, gPlayAgainButton[0]))
                {
                    if(e.type == SDL_MOUSEMOTION)
                    {
                        PlayAgainButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
                    }
                    else if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                        PlayAgainButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
                        End_Game = false;
                    }
                }
                else
                {
                    PlayAgainButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
                }
                if(HomeButton.inInside(e, gHomeButton[0]))
                {
                    if(e.type == SDL_MOUSEMOTION)
                    {
                        HomeButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
                    }
                    else if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                        HomeButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER;
                        playAgain = false;
                        End_Game = false;
                    }
                }
                else
                {
                    HomeButton.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
                }
			}

			gGameOverTexture.render((SCREEN_WIDTH - gGameOverTexture.getWidth())/2, GAME_OVER_POSY, gRenderer);
            SDL_Rect* CurrentClip_PlayAgain = &gPlayAgainButton[PlayAgainButton.mCurrentSprite];
            PlayAgainButton.render(CurrentClip_PlayAgain, gRenderer, gPlayAgainButtonTexture);
            SDL_Rect* CurrentClip_Home = &gHomeButton[HomeButton.mCurrentSprite];
            HomeButton.render(CurrentClip_Home, gRenderer, gHomeButtonTexture);
			SDL_RenderPresent(gRenderer);
		}
	}
}
bool checkCollision1(Character A, SDL_Rect* A_clips,
                    Enemy B, SDL_Rect* B_clips)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    // side of A
    leftA = A.getPosX() +17;
    rightA = A.getPosX() + A_clips->w - 10;
    topA = A.getPosY() + 4;
    bottomA = A.getPosY() + A_clips->h ;
    // side of V
    leftB = B.getPosX() + 4;
    rightB = B.getPosX() + B_clips->w - 8 ;
    topB = B.getPosY() + 4;
    bottomB = B.getPosY() + B_clips->h - 4;
    // not collision
    if(bottomA <= topB)            return false;
    if(topA >= bottomB)            return false;
    if(rightA <= leftB)            return false;
    if(leftA >= rightB)            return false;
    //  collision
    return true;
}

bool checkCollision2(Ammo A, SDL_Rect A_clips,
                    Enemy B, SDL_Rect B_clips)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    // side of A
    leftA = A.getPosX();
    rightA = A.getPosX() + A_clips.w;
    topA = A.getPosY();
    bottomA = A.getPosY() + A_clips.h ;
    // side of V
    leftB = B.getPosX() + 4;
    rightB = B.getPosX() + B_clips.w -4 ;
    if(B.getType() == ENEMY_TYPE_4)
    {
        topB = B.getPosY() + 8;
        bottomB = B.getPosY() + B_clips.h - 4;
    }
    else
    {
        topB = B.getPosY() + 4;
        bottomB = B.getPosY() + B_clips.h - 4;
    }
    // not collision
    if(bottomA <= topB)            return false;
    if(topA >= bottomB)            return false;
    if(rightA <= leftB)            return false;
    if(leftA >= rightB)            return false;
    //  collision
    return true;
}


void renderScrollingBackground(std::vector <double>& BaseSpeed_Background,
	LTexture(&gBackgroundTexture)[BACKGROUND_LAYER],
	SDL_Renderer* gRenderer)
{
	std::vector <double> layer_speed;
	layer_speed.push_back(LAYER_1_SPEED);
	layer_speed.push_back(LAYER_2_SPEED);
	layer_speed.push_back(LAYER_3_SPEED);
	layer_speed.push_back(LAYER_4_SPEED);
	layer_speed.push_back(LAYER_5_SPEED);
	layer_speed.push_back(LAYER_6_SPEED);

	for (int i = 0; i < BACKGROUND_LAYER - 1; i++)
	{
		BaseSpeed_Background[i] -= layer_speed[i];
		if (BaseSpeed_Background[i] < -gBackgroundTexture[i].getWidth())
		{
			BaseSpeed_Background[i] = 0;
		}
		gBackgroundTexture[i].render(BaseSpeed_Background[i], 0, gRenderer);
		gBackgroundTexture[i].render(BaseSpeed_Background[i] + gBackgroundTexture[i].getWidth(), 0, gRenderer);
	}
}

void renderScrollingGround(LTexture &Ground, double &speed, SDL_Renderer* gRenderer)
{
    speed -= GROUND_SPEED;
    if( speed < -Ground.getWidth())
    {
        speed = 0;
    }
    Ground.render(speed, SCREEN_HEIGHT - Ground.getHeight(), gRenderer);
    Ground.render(speed + Ground.getWidth(), SCREEN_HEIGHT - Ground.getHeight(), gRenderer);
}

void renderCharacterPower(LTexture &gHP_img, LTexture &gMP_img, LTexture &gHP_num, LTexture &gMP_num, int &char_hp, int &char_mp, SDL_Renderer* gRenderer, TTF_Font* gFont)
{
    SDL_Color textColor = {0, 0, 0};
    std::string hp = "X " + std::to_string(char_hp);
    if(!gHP_num.loadFromRenderedText(hp, textColor, gFont, gRenderer))
    {
        printf("Failed to render HP texture!\n");
    }
    gHP_img.render(HP_IMG_POSX, HP_IMG_POSY, gRenderer);
    gHP_num.render(HP_NUM_POSX, HP_NUM_POSY, gRenderer);

    std::string mp = "X " + std::to_string(char_mp);
    if(!gMP_num.loadFromRenderedText(mp, textColor, gFont, gRenderer))
    {
        printf("Failed to render MP texture!\n");
    }
    gMP_img.render(MP_IMG_POSX, MP_IMG_POSY, gRenderer);
    gMP_num.render(MP_NUM_POSX, MP_NUM_POSY, gRenderer);
}
void DrawPlayerScore(LTexture &gScoreTexture, int &score, TTF_Font* gFont, SDL_Renderer* gRenderer)
{
    SDL_Color textColor = {0, 0, 0};
    std::string Score = "SCORE:                 " + std::to_string(score);
    if(!gScoreTexture.loadFromRenderedText(Score, textColor, gFont, gRenderer))
    {
        printf("Failed to render score texture!\n");
    }
    gScoreTexture.render(SCORE_POSX, SCORE_POSY, gRenderer);
}
void DrawPlayerHighScore(LTexture &gHighScoreTexture, int &highScore, TTF_Font* gFont, SDL_Renderer* gRenderer)
{
    SDL_Color textColor = {0, 0, 0};
    std::string HighScore = "HIGHSCORE:    " + std::to_string(highScore);
    if(!gHighScoreTexture.loadFromRenderedText(HighScore, textColor, gFont, gRenderer))
    {
        printf("Failed to render high score texture!\n");
    }
    gHighScoreTexture.render(HIGHSCORE_POSX, HIGHSCORE_POSY, gRenderer);
}

void ControlCharFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_CHAR >= CHAR_FRAMES - 3)
	{
		frame = 0;
	}
}

void ControlEnemy1Frame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_ENEMY1 >= ENEMY1_FRAMES-1)
	{
		frame = 0;
	}
}

void ControlEnemy2Frame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_ENEMY2 >= ENEMY2_FRAMES-1)
	{
		frame = 0;
	}
}

void ControlEnemy3Frame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_ENEMY3 >= ENEMY3_FRAMES-1)
	{
		frame = 0;
	}
}

void ControlEnemy4Frame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_ENEMY4 >= ENEMY4_FRAMES-1)
	{
		frame = 0;
	}
}

void ControlAmmoFrame(int &frame)
{
    frame += FRAME_INCREASEMENT;
    if(frame / SLOW_FRAME_DART >= DART_FRAMES)
    {
        frame =0 ;
    }
}

void ControlCharacterFireFrame(int &frame, Character &character)
{
    if(character.isShooting())  frame += FRAME_INCREASEMENT;
    if(frame / SLOW_FRAME_CHAR_FIRE >= 4 )
    {
        frame = 0 ;
        character.getStatus(false);
    }
}



