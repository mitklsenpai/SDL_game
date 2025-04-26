
#ifndef COLLISION_H_
#define COLLISION_H_

#include "commonFunc.h"
#include "Gun.h"
#include "SmallEnemy.h"
#include "MainObject.h"
#include "Nuke.h"

class Collision
{
public:
    Collision();
    ~Collision();

    bool CheckCollision(const SDL_Rect &a, const SDL_Rect &b);
    void Col_bullet_enemy(MainObject &player, std::vector<SmallEnemy*> &SmallSpawner, Gun &gun, std::vector<Exp*> &Exp_List, SDL_Renderer *des);
    void Col_player_enemy(std::vector<SmallEnemy*> &SmallSpawner, MainObject &player);
    void Col_player_exp(std::vector<Exp*> &Exp_List, MainObject &player, SDL_Renderer *des);
    void Col_player_nuke(MainObject &p_player,const std::vector<Nuke*> &nukes);
    void Col_enemy_nuke(std::vector<SmallEnemy*> &SmallSpawner,const std::vector<Nuke*> &nukes);
};

#endif // COLLISION_H_
