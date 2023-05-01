#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "Game_base.h"
#include "LTexture.h"
#include "Character.h"
#include "Enemy.h"
#include "Button.h"

bool init();

bool loadMedia();

void close();

std::string getHighScoreFromFile(std::string path);

void updateHighScore(std::string path, const int &highScore);

void GenerateEnemy(Enemy &enemy1, Enemy &enemy2, Enemy &enemy3, Enemy &enemy4, SDL_Renderer* gRenderer);

void updateGameAndScore(int &time, int &score, int &highScore, Enemy &enemy1, Enemy &enemy2, Enemy &enemy3, Enemy &enemy4,SDL_Renderer* gRenderer );

void renderScrollingBackgroundMenu(std::vector <double>& BaseSpeed_Background, LTexture gBackgroundTexture[], SDL_Renderer* gRenderer);

void HandlePlayButton(SDL_Event &e, Button &PlayButton, SDL_Rect gPlayButton, bool &quitMenu, bool &playAgain, Mix_Chunk* gClick);

void HandleHelpButton(SDL_Event &e, Button &HelpButton, SDL_Rect gHelpButton,
                      Button &BackButton, SDL_Rect gBackButton[], LTexture &gBackButtonTexture,
                      Mix_Chunk* gClick, SDL_Renderer* gRenderer, std::vector <double> &OffsetSpeed_BackgroundMenu,
                      LTexture gBackgroundTexture[], bool &quitMenu, bool &quitGame);

void HandleBackButton(SDL_Event &e, Button &BackButton, SDL_Rect gBackButton[], LTexture &gBackButtonTexture,
                      Mix_Chunk* gClick, SDL_Renderer* gRenderer, std::vector <double> &OffsetSpeed_BackgroundMenu,
                      LTexture gBackgroundTexture[], bool &quitMenu, bool &quitGame);

void HandleExitButton(SDL_Event &e, Button &ExitButton, SDL_Rect gExitButton, bool &quitMenu, bool &quitGame, Mix_Chunk* gClick);

void HandleContinueButton(SDL_Event &e, Button &ContinueButton, SDL_Rect gContinueButton[], LTexture &gContinueButtonTexture,
                          Button &HomeButton, SDL_Rect gHomeButton[], LTexture &gHomeButtonTexture, LTexture &gPausedMenuTexture,
                          bool &GameState, Mix_Chunk* gClick, SDL_Renderer* gRenderer, bool &quit, bool &playAgain, bool &quitGame);

void HandlePauseButton(SDL_Event &e, Button &PauseButton, SDL_Rect gPauseButton,
                       Button &ContinueButton, SDL_Rect gContinueButton[], LTexture &gContinueButtonTexture,
                       Button &HomeButton, SDL_Rect gHomeButton[], LTexture &gHomeButtonTexture,
                       LTexture &gPausedGameTexture, bool &GameState, Mix_Chunk* gClick, SDL_Renderer* gRenderer,
                       bool &quit, bool &playAgain, bool &quitGame);

void DrawEndGameSelection(SDL_Event &e, SDL_Renderer* gRenderer, LTexture &gGameOverTexture,
                          Button &PlayAgainButton, SDL_Rect gPlayAgainButton[], LTexture &gPlayAgainButtonTexture,
                          Button &HomeButton, SDL_Rect gHomeButton[], LTexture &gHomeButtonTexture, Mix_Chunk* gClick, bool &playAgain, bool &quitGame);

bool checkCollision1(Character A, SDL_Rect* A_clips,
                     Enemy B, SDL_Rect* B_clips);

bool checkCollision2(Ammo A, SDL_Rect A_clips,
                     Enemy B, SDL_Rect B_clips);

void renderScrollingBackground(std::vector <double>& BaseSpeed_Background, LTexture(&gBackgroundTexture)[BACKGROUND_LAYER], SDL_Renderer* gRenderer);

void renderScrollingGround(LTexture &Ground, double &speed, SDL_Renderer* gRenderer);

void renderCharacterPower(LTexture &gHP_img, LTexture &gMP_img, LTexture &gHP_num, LTexture &gMP_num,
                          int &char_hp, int &char_mp, SDL_Renderer* gRenderer, TTF_Font* gFont);

void DrawPlayerScore(LTexture &gScoreTexture, int &score, TTF_Font* gFont, SDL_Renderer* gRenderer);

void DrawPlayerHighScore(LTexture &gHighScoreTexture, int &highScore, TTF_Font* gFont, SDL_Renderer* gRenderer);

void ControlCharFrame(int &frame);

void ControlEnemy1Frame(int& frame);

void ControlEnemy2Frame(int& frame);

void ControlEnemy3Frame(int& frame);

void ControlEnemy4Frame(int& frame);

void ControlAmmoFrame(int &frame);

void ControlCharacterFireFrame(int &frame, Character &character);

#endif // GAME_UTILS_H
