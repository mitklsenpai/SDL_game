
#ifndef BULLET_BASE_H_
#define BULLET_BASE_H_
#include "Player.h"

#define FIRERATE 20

class BulletBase
{
public:

    float x_pos;
    float y_pos;
    float angle;

    SDL_Rect GetRect()
    {
        SDL_Rect r_;
        r_.x = x_pos;
        r_.y = y_pos;
        r_.w = 10;
        r_.h = 10;

        return r_;
    }
};

#endif // BULLET_BASE_H_
