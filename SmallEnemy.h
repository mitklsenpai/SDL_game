
#ifndef SMALL_ENEMY_H_
#define SMALL_ENEMY_H_

#include "commonFunc.h"
#include "Player.h"
#include "MainObject.h"

#define SMALL_ENEMY_SPEED 2

class SmallEnemy : public Player
{
public:
    SmallEnemy();
    ~SmallEnemy();

    enum WalkType{
        Left = 1,
        Right = 2,
        Up = 3,
        Down = 4,
    };

    bool LoadImg(std::string path, SDL_Renderer *screen);
    void set_clips();
    void Show(SDL_Renderer *des);

    void Follow(MainObject &player);
private:
    float x_pos;
    float y_pos;

    float x_val;
    float y_val;

    int frame_;
    int height_frame_;
    int width_frame_;

    SDL_Rect frame_clips[6];
    int status;

    Input input_type;
};

#endif // SMALL_ENEMY_H_
