#pragma once
#ifndef GUN_H_
#define GUN_H_

#include "commonFunc.h"
#include "MainObject.h"
#include "AudioManager.h"

#define GUN_OFFSET 20

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

class Gun : public Player
{
public:
    Gun(SDL_Renderer *des);
    ~Gun();

    void Rotation(MainObject &player, SDL_Renderer* des);
    void HandleMouseEvents(SDL_Event events, SDL_Renderer* screen);
    void SetBullet();
    void ShowBullet(SDL_Renderer *des);
    std::vector<BulletBase*> Get_Bullets() {return bullets;}
    void RemoveBullet(const int &index);
    SDL_Rect GetRect() {return BulletRect_;}
    void update(AudioManager &audio);

    int GetDame() {return BULLET_DAME;}
    int GetTotalBullets() {return MAX_BULLETS_PER_BURST;}
    int GetBulletSpeed() {return FIRERATE;}

    void IncreaseDame() {BULLET_DAME++;}
    void IncreaseTotalBullets() {MAX_BULLETS_PER_BURST++;}
    void IncreaseBulletSpeed() {FIRERATE += round(FIRERATE*0.1);}
    bool IsShot() {return is_shot;}

    int BULLET_DAME = 2;
    int FIRERATE = 20;
    int MAX_BULLETS_PER_BURST = 3;
private:

    bool is_shot;
    float x_pos;
    float y_pos;

    int x_target;
    int y_target;



    SDL_Texture *bullet_texture;
    std::vector<BulletBase*> bullets;
    SDL_Rect BulletRect_;

    int last_bullet;
    Uint32 last_shot;
    Uint32 bullet_delay;

};



#endif // SHOT_GUN_H_
