
#ifndef SMALL_ENEMY_H_
#define SMALL_ENEMY_H_

#include "commonFunc.h"
#include "Player.h"
#include "MainObject.h"

#define SMALL_ENEMY_SPEED 1
#define MAX_SMALL_ENEMIES 30
#define SMALL_ENEMY_DAME 1

class SmallEnemy : public Player
{
public:
    SmallEnemy();
    ~SmallEnemy();

    bool LoadImg(std::string path, SDL_Renderer *screen);
    void set_clips();
    void Show(SDL_Renderer *des);
    void Follow(MainObject &player);
    void SetSpawnPoint(int X, int Y);

    float Get_X_Pos() {return x_pos;}
    float Get_Y_Pos() {return y_pos;}
    int Get_Height_Frame() {return height_frame_;}
    int Get_Width_Frame() {return width_frame_;}

private:
    float x_pos;
    float y_pos;

    int frame_;
    int height_frame_;
    int width_frame_;
    SDL_Rect frame_clips[6];

    bool is_move;
    int hp;
    SDL_Rect HP_bar;

};

#endif // SMALL_ENEMY_H_
