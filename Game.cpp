
#include "Game.h"

Game::Game(SDL_Renderer *des, Gun &gun, MainObject &player) : gun_(gun), player_(player)
{
    p_play = {544, 400};
    p_replay = {544, 272};
    p_quit = {544, 388};
    P_YouLose = {544, 100};
    P_YouLose = {580,200};
    p_pause_button = {SCREEN_WIDTH-WIDTH_BUTTON_SETTING, 0};

    frame = IMG_LoadTexture(des, "images//Buff_window.png");
    info = IMG_LoadTexture(des, "images//Info_table.png");
    for(int i=0;i<MAIN_BUFFS;i++)
    {
        Main_buffs_texture[i] = nullptr;
    }

    for(int i=0;i<TOTAL_BUFFS;i++)
    {
        Note_table[i] = nullptr;
    }

    Buffs["dame"] = "images//Dame.png";
    Buffs["total_bullets"] = "images//total_bullets.png";
    Buffs["speed"] = "images//Speed.png";
    Buffs["bullet_speed"] = "images//Bullet_speed.png";
    Buffs["max_health"] = "images//health.png";

    p_frame = {512, 235};
    p_info = {131, 209};
    Points["first"] = {564, 329};
    Points["second"] = {624, 329};
    Points["third"] = {684, 329};

    Press["first"] = false;
    Press["second"] = false;
    Press["third"] = false;
}


Game::~Game()
{
}

bool Game::CheckButton(SDL_Point &point, int wid, int hei)
{
    int left = point.x;
    int right = point.x + wid;
    int top = point.y;
    int bottom = point.y + hei;

    if(left <= mouse_x && right >= mouse_x && top <= mouse_y && bottom >= mouse_y)
        return true;
    return false;
}

void Game::HandleMouseHover(SDL_Event event)
{
switch(event.type)
    {
        case SDL_KEYDOWN:
        {
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                setting_pressed[0] = true;
            }
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                SDL_GetMouseState(&mouse_x, &mouse_y);
                if(menu)
                {
                    if(CheckButton(p_play, WIDTH_BUTTON, HEIGH_BUTTON))
                    {
                        pressed[0] = true;
                    }
                }
                else if(!menu)
                {
                    if(CheckButton(p_replay, WIDTH_BUTTON, HEIGH_BUTTON))
                    {
                        pressed[1] = true;
                    }
                    else if(CheckButton(p_quit, WIDTH_BUTTON, HEIGH_BUTTON))
                    {
                        pressed[2] = true;
                    }
                }

                if(!paused)
                {
                    if(CheckButton(p_pause_button, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                    {
                        setting_pressed[0] = true;
                    }
                }
                else if(paused)
                {
                    if(CheckButton(p_resume_button, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                    {
                        setting_pressed[1] = true;
                    }
                    else if(CheckButton(p_quit_button_setting, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                    {
                        setting_pressed[2] = true;
                    }
                }
                if(buff)
                {
                    if(CheckButton(Points["first"], WIDTH_BUFF, HEIGHT_BUFF))
                    {
                        Press["first"] = true;
                        selected_buff = Main_buffs_name[0];
                    }
                    else if(CheckButton(Points["second"], WIDTH_BUFF, HEIGHT_BUFF))
                    {
                        Press["second"] = true;
                        selected_buff = Main_buffs_name[1];
                    }
                    else if(CheckButton(Points["third"], WIDTH_BUFF, HEIGHT_BUFF))
                    {
                        Press["third"] = true;
                        selected_buff = Main_buffs_name[2];
                    }
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            for(int i=0;i<3;i++)
            {
                pressed[i] = false;
            }
            for(int i=0;i<4;i++)
            {
                setting_pressed[i] = false;
            }
            Press["first"] = false;
            Press["second"] = false;
            Press["third"] = false;
            break;
        }
        case SDL_MOUSEMOTION:
        {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            if(menu)
            {
                if(CheckButton(p_play, WIDTH_BUTTON, HEIGH_BUTTON))
                {
                    play_button_frame++;
                    if(play_button_frame == 3)
                    {
                        play_button_frame = 2;
                    }
                }
                else
                {
                    play_button_frame = 0;
                }
            }
            else if(!menu)
            {
                if(CheckButton(p_replay, WIDTH_BUTTON, HEIGH_BUTTON))
                {
                   replay_button_frame++;
                   if(replay_button_frame == 3)
                        replay_button_frame = 2;
                }
                else
                {
                    replay_button_frame = 0;
                }

                if(CheckButton(p_quit, WIDTH_BUTTON, HEIGH_BUTTON))
                {
                    quit_button_frame++;
                    if(quit_button_frame == 3)
                        quit_button_frame = 2;
                }
                else
                {
                    quit_button_frame = 0;
                }
            }

            if(!paused)
            {
                if(CheckButton(p_pause_button, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                {
                    paused_frame++;
                    if(paused_frame == 2)
                        paused_frame = 1;
                }
                else
                {
                    paused_frame = 0;
                }
            }
            else if(paused)
            {

                if(CheckButton(p_resume_button, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                {
                    resume_frame++;
                    if(resume_frame == 2)
                        resume_frame = 1;
                }
                else
                {
                    resume_frame = 0;
                }
                if(CheckButton(p_quit_button_setting, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                {
                    quit_frame++;
                    if(quit_frame == 2)
                        quit_frame = 1;
                }
                else
                {
                    quit_frame = 0;
                }
            }
            if(buff)
            {
                if(CheckButton(Points["first"], WIDTH_BUFF, HEIGHT_BUFF))
                {
                    first_buff_frame++;
                    if(first_buff_frame == 2)
                        first_buff_frame = 1;
                }
                else
                {
                    first_buff_frame = 0;
                }
                if(CheckButton(Points["second"], WIDTH_BUFF, HEIGHT_BUFF))
                {
                    second_buff_frame++;
                    if(second_buff_frame == 2)
                        second_buff_frame = 1;
                }
                else
                {
                    second_buff_frame = 0;
                }
                if(CheckButton(Points["third"], WIDTH_BUFF, HEIGHT_BUFF))
                {
                    third_buff_frame++;
                    if(third_buff_frame == 2)
                        third_buff_frame = 1;
                }
                else
                {
                    third_buff_frame = 0;
                }
            }
            break;
        }
    }
    if(pressed[0])
    {
        menu = false;
    }
    if(setting_pressed[0])
    {
        paused = true;
    }
    if(Press["first"] || Press["second"] || Press["third"])
    {
        ApplyBuff(player_, gun_);
        buff = false;
        paused = false;
        buff_active = false;
    }
}

void Game::RenderStartMenu(SDL_Renderer *des)
{
    Setclip_and_Render(des, p_play, play_button, play_button_frame,3, "images//Play_button.png", WIDTH_BUTTON, HEIGH_BUTTON);
    Logo = IMG_LoadTexture(des, "images//Logo.png");
    SDL_RenderCopy(des,Logo,NULL,&r_logo);
}

void Game::Setclip_and_Render(SDL_Renderer *des, SDL_Point &point, SDL_Texture *&texture, int &frame, int NUMBER_OF_FRAMES, const char* name, int wid, int hei)
{
    SDL_Rect button_clips[NUMBER_OF_FRAMES];
    for(int i=0;i<NUMBER_OF_FRAMES;i++)
    {
        button_clips[i].x = wid*i;
        button_clips[i].y = 0;
        button_clips[i].w = wid;
        button_clips[i].h = hei;
    }
    if(texture == NULL)
    {
        texture = IMG_LoadTexture(des, name);
        if (texture == NULL) {
            std::cerr << "Failed to load texture: " << name << "\n";
            return;
        }
    }
    SDL_Rect button_rect = {point.x, point.y, wid, hei};
    SDL_Rect *current_frame = &button_clips[frame];
    SDL_RenderCopy(des, texture, current_frame, &button_rect);
}

void Game::FreeButton(SDL_Texture*& texture)
{
    if(texture!=nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

SDL_Texture* Game::Render_Text(SDL_Renderer *des, TTF_Font *font, const char *text, SDL_Point point, SDL_Color textColor)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(des, textSurface);

    SDL_Rect textRect = {point.x, point.y, textSurface->w, textSurface->h };
    SDL_RenderCopy(des, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);

    return textTexture;
}

void Game::Replay(SDL_Renderer*des, TTF_Font* font, bool &game_event, bool &is_quit, MainObject &player, std::vector<SmallEnemy*> &Spawner, std::vector<Exp*> &exp_list, std::vector<Nuke*> &nuke_list)
{
    SDL_Texture* Youlose = Render_Text(des, font, "YOU LOSE", P_YouLose, textColor);
    Setclip_and_Render(des, p_replay, Replay_button, replay_button_frame,3, "images//Replay_button.png", WIDTH_BUTTON, HEIGH_BUTTON);
    Setclip_and_Render(des, p_quit, Quit_button, quit_button_frame,3, "images//Quit_button.png", WIDTH_BUTTON, HEIGH_BUTTON);
    game_event = false;
    Spawner.clear();
    exp_list.clear();
    nuke_list.clear();

    if(pressed[1] == true)
    {
        FreeButton(Replay_button);
        FreeButton(Quit_button);
        SDL_DestroyTexture(Youlose);
        Youlose = NULL;
        player.Reset_status();
        game_event = true;
        menu = true;
    }
    if(pressed[2] == true)
    {
        is_quit = true;
    }
}

void Game::RenderPaused(SDL_Renderer *des)
{
    Setclip_and_Render(des, p_pause_button, Pause_button, paused_frame,2, "images//Paused_button.png", 32, 32);
}

void Game::RenderPausedList(SDL_Renderer *des, bool &is_quit, bool &game_event)
{

    SDL_SetRenderDrawBlendMode(des, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(des, 0, 0, 0, 100);
    SDL_Rect overlay = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(des, &overlay);

    p_resume_button.x = SCREEN_WIDTH/2 - 64;
    p_resume_button.y = SCREEN_HEIGHT/2 -64;
    p_quit_button_setting.x = SCREEN_WIDTH/2 - 64;
    p_quit_button_setting.y = SCREEN_HEIGHT/2 ;

    Setclip_and_Render(des, p_resume_button, Resume_button, resume_frame,2, "images//Resume_button.png", 32, 32);
    Setclip_and_Render(des, p_quit_button_setting, Quit_button_setting, quit_frame,2, "images//quit_button_setting.png", 32, 32);
    if(setting_pressed[1] == true)
    {
        FreeButton(Resume_button);
        FreeButton(Quit_button_setting);
        FreeButton(Pause_button);
        paused = false;
        setting_pressed[1] = false;
    }
    else if(setting_pressed[2] == true)
    {
        FreeButton(Resume_button);
        FreeButton(Quit_button_setting);
        FreeButton(Pause_button);
        is_quit = true;
        setting_pressed[2] = false;
    }
}

void Game::ApplyBuff(MainObject &player, Gun &gun)
{
    if(player.G_EXP >= player.MAX_EXP)
    {
        paused = true;
        buff = true;
        buff_active = true;
        RandomPick();
        player.LEVEL++;
        player.G_EXP = 0;
        player.MAX_EXP = player.MAX_EXP * pow(1.5f, player.LEVEL - 1);
    }
    if(buff_active && !selected_buff.empty())
    {
        if(selected_buff == "images//Dame.png")
        {
            gun.IncreaseDame();
        }
        else if(selected_buff == "images//total_bullets.png")
        {
            gun.IncreaseTotalBullets();
        }
        else if(selected_buff == "images//Speed.png")
        {
            player.IncreaseSpeed();
        }
        else if(selected_buff == "images//Bullet_speed.png")
        {
            gun.IncreaseBulletSpeed();
        }
        else if(selected_buff == "images//health.png")
        {
            player.IncreaseMaxHealth();
        }
        for(int i=0;i<MAIN_BUFFS;i++)
        {
            FreeButton(Main_buffs_texture[i]);
        }
        selected_buff.clear();
        buff_active = false;
    }
}

void Game::RandomPick()
{
    std::vector<char*> availableBuffs = {
        "dame", "total_bullets", "speed", "bullet_speed", "max_health"
    };
    std::srand(std::time(0));
    std::random_shuffle(availableBuffs.begin(), availableBuffs.end());
    for(int i = 0; i < MAIN_BUFFS; i++) {
        if (i < availableBuffs.size())
        {
            Main_buffs_name[i] = Buffs[availableBuffs[i]];
        }
    }
}

void Game::RenderBuff(SDL_Renderer *des)
{
    SDL_SetRenderDrawBlendMode(des, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(des, 0, 0, 0, 100);
    SDL_Rect overlay = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(des, &overlay);

    SDL_Rect renderquad = {p_frame.x, p_frame.y, 255, 170};
    SDL_RenderCopy(des, frame, NULL, &renderquad);
    SDL_Rect renderquad2 = {p_info.x, p_info.y, 237, 223};
    SDL_RenderCopy(des, info, NULL, &renderquad2);

    for (int i = 0; i < MAIN_BUFFS; i++) {
        if (Main_buffs_texture[i] == nullptr) {
            Main_buffs_texture[i] = IMG_LoadTexture(des, Main_buffs_name[i]);
        }
    }

    // Render 3 buff
    Setclip_and_Render(des, Points["first"], Main_buffs_texture[0], first_buff_frame, 2, "", WIDTH_BUFF, HEIGHT_BUFF);
    Setclip_and_Render(des, Points["second"], Main_buffs_texture[1], second_buff_frame, 2, "", WIDTH_BUFF, HEIGHT_BUFF);
    Setclip_and_Render(des, Points["third"], Main_buffs_texture[2], third_buff_frame, 2, "", WIDTH_BUFF, HEIGHT_BUFF);
}


