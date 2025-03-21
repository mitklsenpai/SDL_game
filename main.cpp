#include <iostream>
#include <stdlib.h>
#include "commonFunc.h"
#include "Player.h"
#include "MainObject.h"
#include "Map.h"
#include "Timer.h"
#include "SmallEnemy.h"
#include "Gun.h"
#include "BulletBase.h"
#include "Collision.h"

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

// Load animation + Vi tri spawn SMALL_ENEMY
std::vector<SmallEnemy*> SmallEnemySpawner()
{
    std::vector<SmallEnemy*> SmallSpawner;

    SmallEnemy* smallenemy = new SmallEnemy[MAX_SMALL_ENEMIES];
    for(int i=0;i<MAX_SMALL_ENEMIES;i++)
    {
        SmallEnemy* object = smallenemy + i;
        if(object != NULL)
        {
            float rand_x = rand()%1280;
            float rand_y = rand()%640;
            object->LoadImg("images//Run_Left.png", g_screen);
            object->set_clips();
            object->SetSpawnPoint(rand_x,rand_y);

            SmallSpawner.push_back(object);
        }
    }
    return SmallSpawner;
}


//Ham main
int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

    if(InitData()==false)
        return -1;

    if(LoadBackground() == false)
        return -1;


    // Load animation cho Nhan vat
    MainObject p_player;
    p_player.LoadImg("images//4_direct_move.png", g_screen);
    p_player.set_clips();

    //Load sung
    Gun gun;
    gun.LoadImg("images//shot_gun.png", g_screen);

    // Spawn Small_enemy + rect quai
    std::vector<SmallEnemy*> SmallSpawner = SmallEnemySpawner();

    //Check va cham
    Collision collision;


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
            gun.HandleMouseEvents(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        // ve map
        game_map.DrawMap(g_screen);


        // chay chuyen dong cho nhan vat
        p_player.DoPlayer();
        p_player.Show(g_screen);
        p_player.ShowHPBar(g_screen);

        //sung
        gun.Rotation(p_player,g_screen);
        gun.SetBullet();
        gun.ShowBullet(g_screen);

        //chuyen dong + show animation cho SmallEnemy
        for(int i=0;i<(int)SmallSpawner.size();i++)
        {
            SmallEnemy* smallenemy = SmallSpawner.at(i);
            if(smallenemy!=NULL)
            {
                smallenemy->Show(g_screen);
                smallenemy->Follow(p_player);
            }
        }

        std::vector<BulletBase*> bullet_list = gun.Get_Bullets();
        for(int index=0;index<(int) bullet_list.size(); index++)
        {
            BulletBase *bullet = bullet_list[index];
            if(bullet != NULL)
            {
                for(int j=0;j<SmallSpawner.size();j++)
                {
                    SmallEnemy* smallenemy = SmallSpawner[j];
                    SDL_Rect r_bullet, r_small_enemy;

                    r_small_enemy.x = smallenemy->Get_X_Pos();
                    r_small_enemy.y = smallenemy->Get_Y_Pos();
                    r_small_enemy.w = smallenemy->Get_Width_Frame();
                    r_small_enemy.h = smallenemy->Get_Height_Frame();

                    r_bullet = {bullet->x_pos, bullet->y_pos, 10, 10};

                    bool col = collision.CheckCollision(r_small_enemy,r_bullet);
                    if(col)
                    {
                        gun.RemoveBullet(index);
                        smallenemy->Free();
                        SmallSpawner.erase(SmallSpawner.begin() + j);
                    }
                }
            }
        }


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
