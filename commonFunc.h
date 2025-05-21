#ifndef _COMMON_FUNCTION_H_
#define _COMMON_FUNCTION_H_

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int SMALL_ENEMY_FRAME_OFFSET = 30;
const int PLAYER_FRAME_OFFSET = 26;

const int SCREEN_HEIGHT_MID = 320;
const int SCREEN_WIDTH_MID = 640;
const int SPAWN_RADIUS = 300;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static TTF_Font* g_font = NULL;


// Thiet lap man hinh
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

// Set mau cho anh
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

// set timer, fps, ...
const int FRAME_PER_SECOND = 40;

// set thong so map
#define TILE_SIZE 64
#define MAX_MAP_X 34
#define MAX_MAP_Y 10
typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;

};

typedef struct Input
{
    int left_;
    int rigth_;
    int up_;
    int down_;
};



#endif
