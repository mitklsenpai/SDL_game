
#include "Game.h"

Game::Game()
{
    p_play.x = 544; p_play.y = 400;
    p_replay.x = 544; p_replay.y = 272;
    p_quit.x = 544; p_quit.y = 388;
    P_YouLose.x = 544; P_YouLose.y = 100;
}

Game::~Game()
{
}

bool Game::CheckButton(SDL_Point &point)
{
    int left = point.x;
    int right = point.x + WIDTH_BUTTON;
    int top = point.y;
    int bottom = point.y + HEIGH_BUTTON;

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
                    if(CheckButton(p_play))
                    {
                        pressed[0] = true;
                    }
                }
                else
                {
                    if(CheckButton(p_replay))
                    {
                        pressed[1] = true;
                    }
                    else if(CheckButton(p_quit))
                    {
                        pressed[2] = true;
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
            break;
        }
        case SDL_MOUSEMOTION:
        {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            if(menu)
            {
                if(CheckButton(p_play))
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
            else
            {
                if(CheckButton(p_replay))
                {
                   replay_button_frame++;
                   if(replay_button_frame == 3)
                        replay_button_frame = 2;
                }
                else
                {
                    replay_button_frame = 0;
                }
                if(CheckButton(p_quit))
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
            break;
        }
    }
    if(pressed[0])
    {
        menu = false;
    }
}

void Game::RenderStartMenu(SDL_Renderer *des)
{
    Setclip_and_Render(des, p_play, play_button, r_play_button, play_button_frame, "images//Play_button.png");
    Logo = IMG_LoadTexture(des, "images//Logo.png");
    SDL_RenderCopy(des,Logo,NULL,&r_logo);
}

void Game::Setclip_and_Render(SDL_Renderer *des, SDL_Point &point, SDL_Texture *&texture, SDL_Rect &button_rect, int &frame, const char* name)
{
    SDL_Rect button_clips[3];
    for(int i=0;i<3;i++)
    {
        button_clips[i].x = WIDTH_BUTTON*i;
        button_clips[i].y = 0;
        button_clips[i].w = WIDTH_BUTTON;
        button_clips[i].h = HEIGH_BUTTON;
    }
    if(texture == NULL)
    {
        texture = IMG_LoadTexture(des, name);
    }
    button_rect = {point.x, point.y, WIDTH_BUTTON, HEIGH_BUTTON};
    SDL_Rect *current_frame = &button_clips[frame];
    SDL_RenderCopy(des, texture, current_frame, &button_rect);
}

void Game::FreeButton(SDL_Texture*& texture, SDL_Rect &rect)
{
    if(texture!=nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        rect.w = 0;
        rect.h = 0;
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

void Game::Replay(SDL_Renderer*des, TTF_Font* font, bool &game_event, bool &is_quit, MainObject &player, std::vector<SmallEnemy*> &Spawner)
{
    SDL_Texture* Youlose = Render_Text(des, font, "YOU LOSE", P_YouLose);
    Setclip_and_Render(des, p_replay, Replay_button, r_replay_button, replay_button_frame, "images//Replay_button.png");
    Setclip_and_Render(des, p_quit, Quit_button, r_quit_button, quit_button_frame, "images//Quit_button.png");
    game_event = false;
    Spawner.clear();

    if(pressed[1] == true)
    {
        FreeButton(Replay_button, r_replay_button);
        FreeButton(Quit_button, r_quit_button);
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
