#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "commonFunc.h"
#include "Player.h"

#define PLAYER_SPEED 0.8

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
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event svents, SDL_Renderer* screen); // hàm xử lý sự kiện
    void set_clips(); // hàm xử lý animation
    void DoPlayer(); // ham xu ly di chuyen
private:
    float x_val_;  // vị trí thực
    float y_val_;

    float x_pos_;  // vị trí sau xử lý
    float y_pos_;

    int width_frame_;   // thông tin dãy frame nhân vật
    int height_frame_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;
};



#endif // MAIN_OBJECT_H_
