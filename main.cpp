#include <iostream>
#include "commonFunc.h"
#include "Player.h"
#include "MainObject.h"
#include "Map.h"
#include "Timer.h"
#include "SmallEnemy.h"

Player g_background;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret<0)
    {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("MITKL'S SDL2 GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&& imgFlags))
                success = false;
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("images//dark_space_background" ,g_screen);
    if(ret = false)
        return false;
    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_QUIT;
}

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

    if(InitData()==false)
        return -1;

    if(LoadBackground() == false)
        return -1;


// Load animation cho Nhan vat
    MainObject p_player;
    p_player.LoadImg("images//right_left.png", g_screen);
    p_player.set_clips();

// Load animation cho Quai nho
    SmallEnemy small_mod;
    small_mod.LoadImg("images//Run_Left.png", g_screen);
    small_mod.set_clips();

// Load map anh
    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);


// Vong lap game
    bool is_quit = false;
    while(!is_quit)
    {
        fps_timer.start(); // chay dong ho
        while (SDL_PollEvent(&g_event)!=0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction(g_event,g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);


        // ve map
        game_map.DrawMap(g_screen);

        // chay chuyen dong
        p_player.DoPlayer();
        p_player.Show(g_screen);

        small_mod.Follow(p_player);
        small_mod.Show(g_screen);


        SDL_RenderPresent(g_screen);

        // xu ly fps va delay thoi gian
        int read_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; // 1s = 1000ms -> tgian 1 frame o tgian thuc

        if(read_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - read_imp_time;
            if(delay_time >= 0)
                SDL_Delay(delay_time);
        }
    }

    close();

    return 0;
}
