
#ifndef GUN_H_
#define GUN_H_

#include "commonFunc.h"
#include "MainObject.h"
#include "BulletBase.h"

class Gun : public Player
{
public:
    Gun();
    ~Gun();

    void Rotation(MainObject &player, SDL_Renderer* des);
    void HandleMouseEvents(SDL_Event events, SDL_Renderer* screen);
    void SetBullet();
    void ShowBullet(SDL_Renderer *des);

    bool is_shot;
    float x_pos;
    float y_pos;

    int x_target;
    int y_target;
    SDL_Texture *bullet_texture;

    std::vector<BulletBase*> bullets;
    SDL_Rect BulletRect_;
};


#endif // SHOT_GUN_H_
