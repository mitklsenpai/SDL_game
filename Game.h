#pragma once
#ifndef GAME_H_
#define GAME_H_

#include "commonFunc.h"
#include "MainObject.h"
#include "Gun.h"
#include "Map.h"
#include "SmallEnemy.h"
#include "Nuke.h"

class Gun;
class MainObject;

class Game
{
public:
    Game(SDL_Renderer *des, Gun &gun, MainObject &player);
    ~Game();

    bool Is_Menu() {return menu;}
    bool Is_Paused() {return paused;}
    bool is_buff() {return buff;}
    bool is_buff_active() {return buff_active;}
    void FreeButton(SDL_Texture *&texture);
    SDL_Texture* Render_Text(SDL_Renderer *des, TTF_Font *font, const char* text, SDL_Point point, SDL_Color textColor);
    void Setclip_and_Render(SDL_Renderer *des, SDL_Point &point, SDL_Texture *&texture, int &frame, int NUMBER_OF_FRAMES, const char* name, int wid, int hei);

    void HandleMouseHover(SDL_Event event);
    bool CheckButton(SDL_Point &point, int wid, int hei);
    //menu
    void RenderStartMenu(SDL_Renderer *des);
    //setting
    void RenderPaused(SDL_Renderer *des);
    void RenderPausedList(SDL_Renderer *des, bool &is_quit, bool &game_event);
    // replay & quit
    void YouLose(SDL_Renderer *des, TTF_Font *font);
    void Replay(SDL_Renderer*des, TTF_Font* font, bool &game_event, bool &is_quit, MainObject &player, std::vector<SmallEnemy*> &Spawner, std::vector<Exp*> &exp_list, std::vector<Nuke*> &nuke_list);
    //buff
    void RenderBuff(SDL_Renderer *des);
    void ApplyBuff(MainObject &player, Gun &gun);
    void RandomPick();

    void TriggerBuff()
    {
        paused = true;
        buff = true;
        buff_active = true;
        RandomPick();
    }

private:
    Gun &gun_;
    MainObject &player_;

    int mouse_x, mouse_y;
    SDL_Color textColor = { 255, 0, 0 }; // Màu đỏ
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
	bool setting_pressed[4] = {false};
    bool paused = false;

    SDL_Texture *Pause_button = NULL;
    SDL_Texture *Resume_button = NULL;
    SDL_Texture *Quit_button_setting = NULL;

    SDL_Point p_pause_button;
    SDL_Point p_resume_button;
    SDL_Point p_quit_button_setting;

    int paused_frame = 0;
    int resume_frame = 0;
    int quit_frame = 0;

    //buff
    bool buff = false;
    bool buff_active = false;
    const int TOTAL_BUFFS = 5;
    const int MAIN_BUFFS = 3;
    const int WIDTH_BUFF = 32;
    const int HEIGHT_BUFF = 32;

    int first_buff_frame = 0;
    int second_buff_frame = 0;
    int third_buff_frame = 0;

    SDL_Texture *frame;
    SDL_Point p_frame;
    SDL_Texture *info;
    SDL_Point p_info;

    std::string selected_buff;
    std::map<char*, char*> Buffs;
    SDL_Texture* Main_buffs_texture[3];
    SDL_Texture* Note_table[5];
    std::map<int, char*> Main_buffs_name;
    std::map<char*, SDL_Point> Points;
    std::map<char*, bool> Press;
};

#endif



