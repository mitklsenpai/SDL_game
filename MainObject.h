
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "commonFunc.h"
#include "Player.h"

class MainObject : public Player
{
public:
    MainObject(SDL_Renderer *des);
    ~MainObject();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
        GO_UP = 2,
        GO_DOWN = 3
    };
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event svents, SDL_Renderer* screen);
    void set_clips();
    void DoPlayer();
    void Normalize_Motion(float &x_val_, float &y_val_);
    void ShowBar(SDL_Renderer *des);

    float Get_x_pos(){return x_pos_;}
    float Get_y_pos(){return y_pos_;}
    float Get_height_frame() {return height_frame_;}
    float Get_width_frame() {return width_frame_;}
    SDL_Rect GetRect() {return rect_;}
    void Minus_Hp_When_Hit(int dame) {hp -= dame;}
    bool Dead();
    void Score(SDL_Renderer *des, TTF_Font *font);
    void Set_score() {score++;}
    void Reset_status();
    void ResetInput();
    void SetExp(int x) {G_EXP += x;}
    int GetLEVEL() {return LEVEL;}
    int GetExp() {return G_EXP;}
    int GetMaxExp() {return MAX_EXP;}
//buff
    void IncreaseSpeed();
    void IncreaseMaxHealth();

    int G_EXP;
    int MAX_EXP;
    int LEVEL;
private:

    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    bool is_dead;

    SDL_Rect frame_clip_[4];
    Input input_type_;
    int frame_;
    int status_;
    int score;

    int PLAYER_SPEED;
    int hp;
    int MAX_HP;

    SDL_Texture *HP_Bar_Inner;
    SDL_Texture *HP_Bar_Outer;
    SDL_Texture *Exp_Bar_Outer;
    SDL_Texture *Exp_Bar_Inner;

    struct HP_Bar
    {
        SDL_Rect HP_Inner;
        SDL_Rect HP_Outer;
    }HP_Bar;

    struct Exp_Bar
    {
        SDL_Rect Exp_Inner;
        const SDL_Rect Exp_Outer = {0,30,254,8};
    }Exp_Bar;
};



#endif // MAIN_OBJECT_H_
