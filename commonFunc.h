#ifndef _COMMON_FUNCTION_H_
#define _COMMON_FUNCTION_H_

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

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


#define TILE_SIZE 64
#define MAX_MAP_X 400
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
    int jump_;
};

#endif
