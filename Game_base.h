#ifndef GAME_BASE_H
#define GAME_BASE_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<ctime>
#include<fstream>
#include<random>
#include<cstring>
#include<map>
#include<set>


#define GROUND 336
#define MAX_HEIGHT 100

// Enemy type
#define ENEMY_TYPE_1 11
#define ENEMY_TYPE_2 12
#define ENEMY_TYPE_3 13
#define ENEMY_TYPE_4 14

#define FRAME_INCREASEMENT 1
#define SCORE_INCREASEMENT 1
#define SCORE_INCREASEMENT_ENEMY1 5
#define SCORE_INCREASEMENT_ENEMY2 5
#define SCORE_INCREASEMENT_ENEMY3 10
#define SCORE_INCREASEMENT_ENEMY4 20
#define TIME_INCREASEMENT 1

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0
#define MIX_CHANNEL -1

#define BASE_SPEED 0
#define GROUND_SPEED 4

#define SLOW_FRAME_CHAR 6
#define SLOW_FRAME_DART 4
#define SLOW_FRAME_CHAR_FIRE 6
#define SLOW_FRAME_ENEMY1 5
#define SLOW_FRAME_ENEMY2 10
#define SLOW_FRAME_ENEMY3 5
#define SLOW_FRAME_ENEMY4 4

#define BUTTON_TOTAL 2

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

const int CHAR_FRAMES = 9;
const int CHAR_FIRE_FRAMES = 6;
const int ENEMY1_FRAMES = 4;
const int ENEMY2_FRAMES = 4;
const int ENEMY3_FRAMES = 4;
const int ENEMY4_FRAMES = 4;
const int DART_FRAMES = 8;

const int BACKGROUND_LAYER = 7;

const int ENEMY1_SPEED = 6;
const int ENEMY2_SPEED = 5;
const double LAYER_1_SPEED = 0.1;
const double LAYER_2_SPEED = 0.25;
const double LAYER_3_SPEED = 0.5;
const double LAYER_4_SPEED = 0.75;
const double LAYER_5_SPEED = GROUND_SPEED + 0.3;
const double LAYER_6_SPEED = GROUND_SPEED ;
const double LAYER_7_SPEED = GROUND_SPEED + 0.3;

const int GAME_TITLE_POSX = 0;
const int GAME_TITLE_POSY = 0;
const int PLAY_BUTON_POSX = 346;
const int PLAY_BUTTON_POSY= 230;
const int HELP_BUTTON_POSX = 222;
const int HELP_BUTTON_POSY = 230;
const int EXIT_BUTTON_POSX = 470;
const int EXIT_BUTTON_POSY = 230;
const int BACK_BUTTON_POSX = 0;
const int BACK_BUTTON_POSY = 0;
const int PAUSE_BUTTON_POSX = 0;
const int PAUSE_BUTTON_POSY = 0;
const int CONTINUE_BUTTON_POSX = 270 ;
const int CONTINUE_BUTTON_POSY = 230;
const int HOME_BUTTON_POSX = 423;
const int HOME_BUTTON_POSY = 230;
const int PLAY_AGAIN_BUTTON_POSX = 270;
const int PLAY_AGAIN_BUTTON_POSY = 230;
const int PAUSED_GAME_POSY = 90;
const int GAME_OVER_POSY = 90;
const int SCORE_POSX = 600;
const int SCORE_POSY = 10;
const int HIGHSCORE_POSX = 600;
const int HIGHSCORE_POSY = 40;
const int HP_IMG_POSX = 80;
const int HP_IMG_POSY = 5;
const int HP_NUM_POSX = 126;
const int HP_NUM_POSY = 14;
const int MP_IMG_POSX = 87;
const int MP_IMG_POSY = 47;
const int MP_NUM_POSX = 125;
const int MP_NUM_POSY = 51;
const int EXPLOSION_TIME = 20;

enum ButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER = 1,
    BUTTON_SPRITE_TOTAL = 2
};

#endif // GAME_BASE_H
