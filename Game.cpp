
#include "Game.h"

Game::Game()
{
    p_play.x = 544; p_play.y = 400;
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
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            pressed[0] = false;
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
                    if(play_button_frame>3)
                        play_button_frame = 0;
                }
                else
                    play_button_frame = 0;
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
    for(int i=0;i<3;i++)
    {
        Play_button_clips[i].x = WIDTH_BUTTON*i;
        Play_button_clips[i].y = 0;
        Play_button_clips[i].w = WIDTH_BUTTON;
        Play_button_clips[i].h = HEIGH_BUTTON;
    }

    play_button = IMG_LoadTexture(des,"images//Play_button.png");
    Logo = IMG_LoadTexture(des, "images//Logo.png");

    r_play_button.h = HEIGH_BUTTON;
    r_play_button.w = WIDTH_BUTTON;
    r_play_button.x = 544;
    r_play_button.y = 400;

    SDL_Rect *current_frame = &Play_button_clips[play_button_frame];
    SDL_RenderCopy(des,play_button,current_frame,&r_play_button);
    SDL_RenderCopy(des,Logo,NULL,&r_logo);
}

void Game::FreePlayButton()
{
    if(play_button!=NULL)
    {
        SDL_DestroyTexture(play_button);
        SDL_DestroyTexture(Logo);
        play_button = NULL;
        Logo = NULL;
        r_play_button.w = 0;
        r_play_button.h = 0;
    }
}

void Game::YouLose(SDL_Renderer *des, TTF_Font *font)
{
    SDL_Color textColor = { 255, 0, 0 }; // Màu đỏ
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "YOU LOSE", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(des, textSurface);

    SDL_Rect textRect = {640, 320, textSurface->w, textSurface->h };
    SDL_RenderCopy(des, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

