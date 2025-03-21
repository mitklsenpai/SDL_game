
#ifndef GUN_H_
#define GUN_H_

#include "commonFunc.h"
#include "MainObject.h"
#include "BulletBase.h"

#define GUN_OFFSET 20
#define BULLET_DAME 2

class Gun : public Player
{
public:
    Gun();
    ~Gun();

    void Rotation(MainObject &player, SDL_Renderer* des);
    void HandleMouseEvents(SDL_Event events, SDL_Renderer* screen);
    void SetBullet();
    void ShowBullet(SDL_Renderer *des);
    std::vector<BulletBase*> Get_Bullets() {return bullets;}
    void RemoveBullet(const int &index);
    SDL_Rect GetRect() {return BulletRect_;}

private:
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
