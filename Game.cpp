
#include "Game.h"

Game::Game()
{
    p_play.x = 544; p_play.y = 400;
    p_replay.x = 544; p_replay.y = 272;
    p_quit.x = 544; p_quit.y = 388;
    P_YouLose.x = 544; P_YouLose.y = 100;
    p_pause_button.x = 1200, p_pause_button.y = 0;
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

SDL_Texture* Game::Render_Text(SDL_Renderer *des, TTF_Font *font, const char *text, SDL_Point point)
{
    SDL_Color textColor = { 255, 0, 0 }; // Màu đỏ

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(des, textSurface);

    SDL_Rect textRect = {point.x, point.y, textSurface->w, textSurface->h };
    SDL_RenderCopy(des, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);

    return textTexture;
}

void Game::Replay(SDL_Renderer*des, TTF_Font* font, bool &game_event, bool &is_quit, MainObject &player, std::vector<SmallEnemy*> &Spawner, std::vector<Exp*> &exp_list, std::vector<Nuke*> &nuke_list)
{
    SDL_Texture* Youlose = Render_Text(des, font, "YOU LOSE", P_YouLose);
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
        paused = false;
        setting_pressed[1] = false;
    }
    else if(setting_pressed[2] == true)
    {
        FreeButton(Quit_button_setting);
        is_quit = true;
        setting_pressed[2] = false;
    }
}
