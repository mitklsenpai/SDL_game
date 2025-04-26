#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "commonFunc.h"
#include "Player.h"

#define PLAYER_SPEED 5

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
    void Reset_status() {
        hp = 210;
        score = 0;
        frame_ = 0;
        x_pos_ = 570;
        y_pos_ = 270;
        x_val_ = 0;
        y_val_ = 0;
        width_frame_ = 0;
        height_frame_ = 0;
        status_ = -1;
        input_type_.left_ = 0;
        input_type_.rigth_ = 0;
        input_type_.down_ = 0;
        input_type_.up_ = 0;
        LEVEL = 0;
        MAX_EXP = 10;
        G_EXP = 0;
    }

    void SetExp(int x) {G_EXP += x;}

private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;
    int hp;
    bool is_dead;

    SDL_Rect frame_clip_[4];
    Input input_type_;
    int frame_;
    int status_;
    int score;
    int G_EXP;
    int MAX_EXP;
    int LEVEL;

    SDL_Texture *HP_Bar_Inner;
    SDL_Texture *HP_Bar_Outer;
    SDL_Texture *Exp_Bar_Outer;
    SDL_Texture *Exp_Bar_Inner;

    struct HP_Bar
    {
        SDL_Rect HP_Inner;
        const SDL_Rect HP_Outer ={0,0,254,32};
    }HP_Bar;

    struct Exp_Bar
    {
        SDL_Rect Exp_Inner;
        const SDL_Rect Exp_Outer = {0,30,254,8};
    }Exp_Bar;

};



#endif // MAIN_OBJECT_H_
