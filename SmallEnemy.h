
#ifndef SMALL_ENEMY_H_
#define SMALL_ENEMY_H_

#include "commonFunc.h"
#include "Player.h"
#include "MainObject.h"

#define SMALL_ENEMY_SPEED 1
#define MAX_SMALL_ENEMIES 10

class SmallEnemy : public Player
{
public:
    SmallEnemy();
    ~SmallEnemy();

    bool LoadImg(std::string path, SDL_Renderer *screen);
    void set_clips();
    void Show(SDL_Renderer *des);
    void Follow(MainObject &player);
    void SetSpawnPoint(float &X, float &Y);

private:
    float x_pos;
    float y_pos;

    int frame_;
    int height_frame_;
    int width_frame_;
    SDL_Rect frame_clips[6];

    bool is_move;

};

#endif // SMALL_ENEMY_H_
