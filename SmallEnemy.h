
#ifndef SMALL_ENEMY_H_
#define SMALL_ENEMY_H_

#include "commonFunc.h"
#include "Player.h"

#define SMALL_ENEMY_SPEED 1

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

    void Moving();
    void MovingToPlayer();

private:
    int x_pos;
    int y_pos;

    int x_val;
    int y_val;

    int frame_;
    int height_frame_;
    int width_frame_;

    SDL_Rect frame_clips[6];
    int status;

    Input input_type;
};

#endif // SMALL_ENEMY_H_
