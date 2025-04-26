
#ifndef GAME_H_
#define GAME_H_

#include "commonFunc.h"
#include "MainObject.h"
#include "Gun.h"
#include "Map.h"
#include "SmallEnemy.h"
#include "Nuke.h"


class Game
{
public:
    Game();
    ~Game();
    void HandleMouseHover(SDL_Event event);
    bool CheckButton(SDL_Point &point);
    bool Is_Menu() {return menu;}
    void RenderStartMenu(SDL_Renderer *des);
    void FreeButton(SDL_Texture *&texture, SDL_Rect &rect);
    void YouLose(SDL_Renderer *des, TTF_Font *font);
    void Replay(SDL_Renderer*des, TTF_Font* font, bool &game_event, bool &is_quit, MainObject &player, std::vector<SmallEnemy*> &Spawner, std::vector<Exp*> &exp_list, std::vector<Nuke*> &nuke_list);
    SDL_Texture* Render_Text(SDL_Renderer *des, TTF_Font *font, const char *text, SDL_Point point);
    void Setclip_and_Render(SDL_Renderer *des, SDL_Point &point, SDL_Texture *&texture, SDL_Rect &button_rect, int &frame,const char* name);

    void RenderPausedList();

private:
    // menu
    const int WIDTH_BUTTON = 192;
    const int HEIGH_BUTTON = 96;

    SDL_Texture *play_button = NULL;
    SDL_Texture *Logo = NULL;
    SDL_Texture *Replay_button = NULL;
    SDL_Texture *Quit_button = NULL;
    SDL_Texture *Pause_button = NULL;
    SDL_Texture *Resume_button = NULL;
    SDL_Texture *Setting_button = NULL;

    SDL_Rect Play_button_clips[3];
    SDL_Rect r_logo = {140,10,1000,215};
    SDL_Rect r_play_button;
    SDL_Rect r_replay_button;
    SDL_Rect r_quit_button;

    SDL_Point p_play;
    SDL_Point p_replay;
    SDL_Point p_quit;
    SDL_Point P_YouLose;

    int play_button_frame = 0;
    int replay_button_frame = 0;
    int quit_button_frame = 0;

    bool menu = true;
    bool paused = false;

	bool pressed[3] = {false};
	int mouse_x, mouse_y;

	// player_buff

};

#endif
