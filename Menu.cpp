
#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::set_clips()
{
        for(int i=0;i<3;i++)
    {
        Play_button_clips[i].x = WIDTH_BUTTON*i;
        Play_button_clips[i].y = 0;
        Play_button_clips[i].w = WIDTH_BUTTON;
        Play_button_clips[i].h = HEIGH_BUTTON;

        Restart_button_clips[i].x = i*WIDTH_BUTTON;
        Restart_button_clips[i].y = 0;
        Restart_button_clips[i].w = WIDTH_BUTTON;
        Restart_button_clips[i].h = HEIGH_BUTTON;
    }
}

void Menu::LoadImg(SDL_Renderer *des)
{
    play_button = IMG_LoadTexture(des,"images//Play_button.png");
    restart_button = IMG_LoadTexture(des,"images//Restart_button.png");
    Logo = IMG_LoadTexture(des, "images//Logo.png");

    r_play_button.h = HEIGH_BUTTON;
    r_play_button.w = WIDTH_BUTTON;
    r_play_button.x = 544;
    r_play_button.y = 400;

    r_restart_button.h = HEIGH_BUTTON;
    r_restart_button.w = WIDTH_BUTTON;
    r_restart_button.x = 544;
    r_restart_button.y = 350;
}

void Menu::In_Which_Button(SDL_Event event)
{
    int left_p_button, left_r_button;
    int right_p_button, right_r_button;
    int top_p_button, top_r_button;
    int bottom_p_button, bottom_r_button;

    left_p_button = r_play_button.x;
    right_p_button = r_play_button.x + WIDTH_BUTTON;
    top_p_button = r_play_button.y;
    bottom_p_button = r_play_button.y + HEIGH_BUTTON;

    left_r_button = r_restart_button.x;
    right_r_button = r_restart_button.x + WIDTH_BUTTON;
    top_r_button = r_restart_button.y;
    bottom_r_button = r_restart_button.y + HEIGH_BUTTON;

    int mouse_x, mouse_y;
    if(event.type == SDL_MOUSEMOTION)
    {
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if(mouse_x >= left_p_button && mouse_x <= right_p_button
           && mouse_y >= top_p_button && mouse_y <= bottom_p_button)
        {
            in_play_button = true;
            play_button_frame++;
        }
        else if(mouse_x >= left_r_button && mouse_x <= right_r_button
                && mouse_y >= top_r_button && mouse_y <= bottom_r_button)
        {
            in_restart_button = true;
            restart_button_frame++;
        }
    }
}

void Menu::HandleMouseHover(SDL_Event event)
{
switch(event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(in_play_button)
                {
                    pressed[0] = true;
                    menu = false;
                }
                else if(in_restart_button)
                {
                    pressed[1] = true;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            pressed[0] = false;
            pressed[1] = false;
        }
    }
}

void Menu::RenderPlay(SDL_Renderer *des)
{
    if(play_button_frame>3) play_button_frame = 0;
    SDL_Rect *current_frame = &Play_button_clips[play_button_frame];
    SDL_RenderCopy(des,play_button,current_frame,&r_play_button);
}

void Menu::RenderRestart(SDL_Renderer *des)
{
    if(restart_button_frame>3) restart_button_frame=0;
    SDL_Rect *current_frame = &Restart_button_clips[restart_button_frame];
    SDL_RenderCopy(des,restart_button,current_frame,&r_restart_button);
}

void Menu::RenderLogo(SDL_Renderer *des)
{
    SDL_RenderCopy(des,Logo,NULL,&r_logo);
}

