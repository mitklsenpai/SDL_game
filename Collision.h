
#ifndef COLLISION_H_
#define COLLISION_H_

#include "commonFunc.h"
#include "Gun.h"
#include "BulletBase.h"
#include "SmallEnemy.h"
#include "MainObject.h"

class Collision
{
public:
    Collision();
    ~Collision();

    bool CheckCollision(const SDL_Rect &a, const SDL_Rect &b);
    bool Col_bullet_enemy(std::vector<SmallEnemy*> &SmallSpawner, Gun &gun, std::vector<Exp*> &Exp_List, SDL_Renderer *des);
    void Col_player_enemy(std::vector<SmallEnemy*> &SmallSpawner, MainObject &player);
    void Col_player_exp(std::vector<Exp*> &Exp_List, MainObject &player, SDL_Renderer *des);
};

#endif // COLLISION_H_
