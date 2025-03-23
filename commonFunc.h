#ifndef _COMMON_FUNCTION_H_
#define _COMMON_FUNCTION_H_

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <stdlib.h>

#define SMALL_ENEMY_FRAME_OFFSET 30
#define PLAYER_FRAME_OFFSET 26


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


// Thiet lap man hinh
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

// Set mau cho anh
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

// set timer, fps, ...
const int FRAME_PER_SECOND =35;



// set thong so map
#define TILE_SIZE 64
#define MAX_MAP_X 43
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
