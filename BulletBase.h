
#ifndef BULLET_BASE_H_
#define BULLET_BASE_H_
#include "Player.h"

#define FIRERATE 20

class BulletBase : public Player
{
public:

    float x_pos;
    float y_pos;
    float angle;
};

#endif // BULLET_BASE_H_
