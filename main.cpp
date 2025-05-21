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
#include "AudioManager.h"
#include "Lich.h"

Player g_background;
bool InitData()
{
    int flags = MIX_INIT_MP3 | MIX_INIT_OGG;
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    int res = TTF_Init();
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags)
    {
        std::cout << "Mix_Init Error: " << Mix_GetError() << std::endl;
        return false;
    }
    if(ret<0 || res < 0)
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
    if(InitData()==false)
        return -1;
    if(LoadBackground() == false)
        return -1;
    AudioManager audioManager;
    audioManager.PlayMusic();
    Gun gun(g_screen);
    MainObject p_player(g_screen, gun);
    Game game(g_screen, gun, p_player);
    SmallEnemy smallenemy();
    std::vector<SmallEnemy*> SmallSpawner;
    std::vector<Exp*> Exp_List;
    Lich lich(g_screen);
    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);
    Collision collision;
    NukeManager nukemanager(g_screen);
    std::vector<Nuke*> nuke_list = nukemanager.Get_Nuke_List();
    // Vong lap game
    bool is_quit = false;
    bool player_event = true;
    bool bullet_lich = false;
    bool can_spawn_ = true;
    Uint32 lastTime = 0;
    Uint32 lastFrameTime = SDL_GetTicks();
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
                game.HandleMouseHover(g_event, audioManager);
                if(player_event)
                {
                    p_player.HandleInputAction(g_event,g_screen);
                    gun.HandleMouseEvents(g_event, g_screen);
                }
            }
            else
            {
                game.HandleMouseHover(g_event, audioManager);
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
            p_player.RenderBoost(g_screen);
            p_player.Show(g_screen);
            p_player.ShowBar(g_screen);
            p_player.Score(g_screen, g_font);
            gun.Rotation(p_player,g_screen);
            gun.ShowBullet(g_screen);
            for(auto *smallenemy : SmallSpawner){
                if(smallenemy != nullptr){
                    smallenemy->Show(g_screen);
                    if(!smallenemy->IsDead()){
                        smallenemy->ShowHpBar(g_screen);
                    }else{
                        delete smallenemy;
                    }
                }
            }
            if(p_player.GetLEVEL() == 3){
                lich.Activate(g_screen, nukemanager, p_player);
            }
            for(auto *exp : Exp_List){
                if(exp != nullptr)
                    exp->Render(g_screen, exp->exp_orb, exp->r_exp);
            }
            for(auto *exp : lich.GetExpList()){
                if(exp != nullptr)
                    exp->Show(g_screen, exp->exp_orb, exp->r_exp);
            }
            if(!game.Is_Paused())
            {
                if(p_player.GetLEVEL() == 3){
                    lich.UpdateSkill(nukemanager, p_player);
                    bullet_lich = collision.Col_bullet_lich(gun, lich, g_screen);
                    if(lich.IsDead()){
                        can_spawn_ = true;
                        bullet_lich = false;
                    }
                    else{
                        can_spawn_ = false;
                        for(auto *obj : SmallSpawner){
                        if(obj != nullptr)
                            obj->Free();
                            delete obj;
                        }
                        SmallSpawner.clear();
                    }
                }
                p_player.DoPlayer();
                gun.update(audioManager);

                Uint32 currentTime = SDL_GetTicks();
                float deltaTime = (currentTime - lastFrameTime) / 1000.0f; // Chuyển sang giây
                lastFrameTime = currentTime;

                for(auto *smallenemy : SmallSpawner)
                {
                    if(smallenemy != nullptr) smallenemy->Follow(p_player, deltaTime);
                }

                bool bullet_enemy = collision.Col_bullet_enemy(p_player, SmallSpawner,gun, Exp_List, g_screen);
                bool player_enemy = collision.Col_player_enemy(SmallSpawner,p_player, audioManager);
                collision.Col_player_exp(Exp_List, p_player);
                collision.Col_enemy_nuke(SmallSpawner, nukemanager.Get_Nuke_List());
                bool player_nuke = collision.Col_player_nuke(p_player, nukemanager.Get_Nuke_List());
                collision.Col_player_exp(lich.GetExpList(), p_player);

                p_player.UpdateBoostFrame(player_enemy, player_nuke, bullet_enemy, bullet_lich);

                if(can_spawn_ && !p_player.Dead() && currentTime - lastTime >= 1000 && SmallSpawner.size() < SmallEnemy::MAX_SMALL_ENEMIES)
                {
                    SmallEnemy* newEnemy = SmallEnemy::SpawnNewEnemy();
                    SmallSpawner.push_back(newEnemy);
                    lastTime = currentTime;
                }

                game.RenderPaused(g_screen);
                game.ApplyBuff(p_player, gun, audioManager);
            }
            else
            {
                for(auto *smallenemy : SmallSpawner)
                {
                    if(smallenemy != nullptr) smallenemy->SetMove(false);
                }

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
                audioManager.MuteMusic();
                audioManager.PlaySound("youLose");
                game.Replay(g_screen, g_font, player_event, is_quit, p_player, SmallSpawner, Exp_List, nuke_list, lich, can_spawn_);
                p_player.ResetInput();
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

