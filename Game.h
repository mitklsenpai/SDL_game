
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
    bool Is_Menu() {return menu;}
    bool Is_Paused() {return paused;}
    void FreeButton(SDL_Texture *&texture);
    SDL_Texture* Render_Text(SDL_Renderer *des, TTF_Font *font, const char *text, SDL_Point point);
    void Setclip_and_Render(SDL_Renderer *des, SDL_Point &point, SDL_Texture *&texture, int &frame, int NUMBER_OF_FRAMES, const char* name, int wid, int hei);

    void HandleMouseHover(SDL_Event event);
    bool CheckButton(SDL_Point &point, int wid, int hei);

    void RenderStartMenu(SDL_Renderer *des);

    void RenderPaused(SDL_Renderer *des);
    void RenderPausedList(SDL_Renderer *des, bool &is_quit, bool &game_event);

    void YouLose(SDL_Renderer *des, TTF_Font *font);
    void Replay(SDL_Renderer*des, TTF_Font* font, bool &game_event, bool &is_quit, MainObject &player, std::vector<SmallEnemy*> &Spawner, std::vector<Exp*> &exp_list, std::vector<Nuke*> &nuke_list);
private:
    int mouse_x, mouse_y;

    // menu
    const int WIDTH_BUTTON = 192;
    const int HEIGH_BUTTON = 96;


    SDL_Texture *play_button = NULL;
    SDL_Texture *Logo = NULL;
    SDL_Texture *Replay_button = NULL;
    SDL_Texture *Quit_button = NULL;

    SDL_Rect Play_button_clips[3];
    SDL_Rect r_logo = {140,10,1000,215};

    SDL_Point p_play;
    SDL_Point p_replay;
    SDL_Point p_quit;
    SDL_Point P_YouLose;

    int play_button_frame = 0;
    int replay_button_frame = 0;
    int quit_button_frame = 0;

    bool menu = true;
	bool pressed[3] = {false};

	// settings
	const int WIDTH_BUTTON_SETTING = 32;
	const int HEIGH_BUTTON_SETTING = 32;
    bool paused = false;
	bool setting_pressed[4] = {false};

    SDL_Texture *Pause_button = NULL;
    SDL_Texture *Resume_button = NULL;
    SDL_Texture *Quit_button_setting = NULL;

    SDL_Point p_pause_button;
    SDL_Point p_resume_button;
    SDL_Point p_quit_button_setting;

    int paused_frame = 0;
    int resume_frame = 0;
    int quit_frame = 0;

	// player_buff

};

#endif
