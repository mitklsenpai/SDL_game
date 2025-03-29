#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "commonFunc.h"
#include "Player.h"

#define PLAYER_SPEED 5

class MainObject : public Player
{
public:
    MainObject();
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
    void ShowHPBar(SDL_Renderer *des);

    float Get_x_pos(){return x_pos_;}
    float Get_y_pos(){return y_pos_;}
    float Get_height_frame() {return height_frame_;}
    float Get_width_frame() {return width_frame_;}
    SDL_Rect GetRect() {return rect_;}
    void Minus_Hp_When_Hit(int dame) {hp -= dame;}
    bool Dead();
    void Score(SDL_Renderer *des, TTF_Font *font);
    void Set_score() {score++;}

private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;
    int hp;

    SDL_Rect frame_clip_[4];
    Input input_type_;
    int frame_;
    int status_;
    int score;

    struct HP_Bar
    {
        SDL_Rect HP_Inner;
        const SDL_Rect HP_Outer ={0,0,254,32};
    }HP_Bar;

};



#endif // MAIN_OBJECT_H_
