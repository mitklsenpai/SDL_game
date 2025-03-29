
#ifndef GAME_H_
#define GAME_H_

#include "commonFunc.h"
#include "MainObject.h"
#include "Gun.h"
#include "Map.h"
#include "BulletBase.h"
#include "SmallEnemy.h"


class Game
{
public:
    Game();
    ~Game();
    void HandleMouseHover(SDL_Event event);
    bool CheckButton(SDL_Point &point);
    bool Is_Menu() {return menu;}
    void RenderStartMenu(SDL_Renderer *des);
    void FreePlayButton();
    void YouLose(SDL_Renderer *des, TTF_Font *font);

private:
    const int WIDTH_BUTTON = 192;
    const int HEIGH_BUTTON = 96;
    SDL_Rect Play_button_clips[3];
    SDL_Texture *play_button;
    SDL_Texture *Logo;
    SDL_Rect r_logo = {140,10,1000,215};
    SDL_Rect r_play_button;
    SDL_Point p_play;
    int play_button_frame = 0;
    bool menu = true;
	bool pressed[2] = { false };
	int mouse_x, mouse_y;
};

#endif
