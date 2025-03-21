
#ifndef COLLISION_H_
#define COLLISION_H_

#include "commonFunc.h"

class Collision
{
public:
    Collision();
    ~Collision();

    bool CheckCollision(const SDL_Rect &a, const SDL_Rect &b);

};

#endif // COLLISION_H_
