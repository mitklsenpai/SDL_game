
#ifndef MENU_H_
#define MENU_H_

#include "commonFunc.h"

class Menu
{
public:
    Menu();
    ~Menu();
    void HandleMouseHover(SDL_Event event);
    void RenderPlay(SDL_Renderer *des);
    void RenderRestart(SDL_Renderer *des);
    void RenderLogo(SDL_Renderer *des);
    bool Is_Menu() {return menu;}
    bool Is_Restart() {return restart;}
    void LoadImg(SDL_Renderer *des);
    void In_Which_Button(SDL_Event event);
    void set_clips();

private:
    const int WIDTH_BUTTON = 192;
    const int HEIGH_BUTTON = 96;

    SDL_Rect Play_button_clips[3];
    SDL_Rect Restart_button_clips[3];

    SDL_Texture *play_button;
    SDL_Texture *restart_button;
    SDL_Texture *Logo;

    SDL_Rect r_logo = {140,10,1000,215};
    SDL_Rect r_play_button;
    SDL_Rect r_restart_button;

    int play_button_frame = 0;
    int restart_button_frame = 0;

    bool menu = true, restart = false, in_play_button = false, in_restart_button = false;
	bool selected[2] = { false };
	bool pressed[2] = { false };
};

#endif // MENU_H_
