
#include "commonFunc.h"
#include "Player.h"
#include "MainObject.h"
#include "Map.h"
#include "Timer.h"
#include "SmallEnemy.h"
#include "Gun.h"
#include "Collision.h"
#include "Game.h"
#include "Nuke.h"

Player g_background;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    int res = TTF_Init();
    if(ret<0)
        return false;
    if(res < 0)
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("MITKL'S SDL2 GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window == NULL)
        success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&& imgFlags))
                success = false;
        }
        g_font = TTF_OpenFont("Pixel Game.otf", 28);
        if(g_font == NULL)
        {
            std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
            success = false;
        }
    }
    return success;
}
bool LoadBackground()
{
    bool ret = g_background.LoadImg("images//back_ground.png" ,g_screen);
    return ret;
}
void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    TTF_CloseFont(g_font);
    g_font = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_QUIT;
}

//Ham main
int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    SmallEnemy smallenemy;
    if(InitData()==false)
        return -1;
    if(LoadBackground() == false)
        return -1;

    MainObject p_player(g_screen);
    p_player.LoadImg("images//4_direct_move.png", g_screen);
    p_player.set_clips();
    Gun gun(g_screen);
    gun.LoadImg("images//shot_gun.png", g_screen);
    Game game(g_screen, gun, p_player);
    std::vector<SmallEnemy*> SmallSpawner = smallenemy.Make_S_Spawner();
    std::vector<Exp*> Exp_List;
    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);
    Collision collision;
    NukeManager nukemanager(g_screen);
    std::vector<Nuke*> nuke_list = nukemanager.Get_Nuke_List();
    // Vong lap game
    bool is_quit = false;
    bool player_event = true;
    while(!is_quit)
    {
        fps_timer.start(); // chay dong ho
        while (SDL_PollEvent(&g_event)!=0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            if(!game.Is_Paused())
            {
                game.HandleMouseHover(g_event);
                if(player_event)
                {
                    p_player.HandleInputAction(g_event,g_screen);
                    gun.HandleMouseEvents(g_event, g_screen);
                }
            }
            else
            {
                game.HandleMouseHover(g_event);
            }
        }
        if(game.Is_Menu())
        {
            g_background.Render(g_screen, NULL);
            game.RenderStartMenu(g_screen);
        }
        else if(!game.Is_Menu())
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            SDL_RenderClear(g_screen);

            game_map.DrawMap(g_screen);
            p_player.Show(g_screen);
            p_player.ShowBar(g_screen);
            p_player.Score(g_screen, g_font);
            gun.Rotation(p_player,g_screen);
            gun.ShowBullet(g_screen);
            for(auto *smallenemy : SmallSpawner)
            {
                if(smallenemy != nullptr)
                    smallenemy->Show(g_screen);
            }
            for(auto *exp : Exp_List)
            {
                if(exp != nullptr)
                    exp->Render(g_screen, exp->exp_orb, exp->r_exp);
            }
            nukemanager.Render(g_screen);
            if(!game.Is_Paused())
            {
                p_player.DoPlayer();

                gun.update();
                for(auto *smallenemy : SmallSpawner)
                {
                    if(smallenemy != nullptr)
                        smallenemy->Follow(p_player);
                }
                collision.Col_bullet_enemy(p_player, SmallSpawner,gun, Exp_List, g_screen);
                collision.Col_player_enemy(SmallSpawner,p_player);
                collision.Col_player_exp(Exp_List, p_player, g_screen);
                collision.Col_enemy_nuke(SmallSpawner, nukemanager.Get_Nuke_List());
                collision.Col_player_nuke(p_player, nukemanager.Get_Nuke_List());

                if(SmallSpawner.size() < 0.1 * MAX_SMALL_ENEMIES && !p_player.Dead())
                {
                    std::vector<SmallEnemy*> newSpawner = smallenemy.Make_S_Spawner();
                    int maxSpawn = 20;
                    int numToAdd = std::min((int)newSpawner.size(), maxSpawn);

                    SmallSpawner.insert(SmallSpawner.end(), newSpawner.begin(), newSpawner.begin() + numToAdd);
                }
                nukemanager.updateBomb(p_player.GetLEVEL());
                game.RenderPaused(g_screen);
                game.ApplyBuff(p_player, gun);
            }
            else
            {
                for(auto *smallenemy : SmallSpawner)
                {
                    if(smallenemy != nullptr) smallenemy->SetMove(false);
                }
                p_player.ResetInput();
                if(game.is_buff())
                {
                    game.RenderBuff(g_screen);
                    game.RenderNoteTB(g_screen, g_font);
                    game.RenderPreview(g_screen, g_font, p_player, gun);
                }
                else
                {
                    game.RenderPausedList(g_screen, is_quit, player_event);
                    game.RenderNoteTB(g_screen, g_font);
                }
            }

            if(p_player.Dead())
            {
                game.Replay(g_screen, g_font, player_event, is_quit, p_player, SmallSpawner, Exp_List, nuke_list);
            }
        }

        SDL_RenderPresent(g_screen);

        // xu ly fps
        int read_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; // 1s = 1000ms -> tgian 1 framae o tgian thuc

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

