#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "commonFunc.h"
#include "Player.h"

#define PLAYER_SPEED 5

class MainObject : public Player // tái sử dụng hàm class Player
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
    void Show(SDL_Renderer* des);// ham trinh chieu animation
    void HandleInputAction(SDL_Event svents, SDL_Renderer* screen); // hàm xử lý sự kiện
    void set_clips(); // hàm xử lý animation
    void DoPlayer(); // ham xu ly di chuyen
    void Normalize_Motion(float &x_val_, float &y_val_);
    void ShowHPBar(SDL_Renderer *des);

    float Get_x_pos(){return x_pos_;}
    float Get_y_pos(){return y_pos_;}
    float Get_height_frame() {return height_frame_;}
    float Get_width_frame() {return width_frame_;}
    SDL_Rect GetRect() {return rect_;}
    void Minus_Hp_When_Hit(int dame) {hp -= dame;}
    bool Dead();
    void ShowDead(SDL_Renderer *screen);

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

    SDL_Rect dead_frame_clip[4];
    int dead_frame;
    SDL_Rect r_dead;
    SDL_Texture *dead_texture = NULL;

    struct HP_Bar
    {
        SDL_Rect HP_Inner;
        const SDL_Rect HP_Outer ={0,0,254,32};
    }HP_Bar;

};



#endif // MAIN_OBJECT_H_
