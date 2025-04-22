
#ifndef SMALL_ENEMY_H_
#define SMALL_ENEMY_H_

#include "commonFunc.h"
#include "Player.h"
#include "MainObject.h"

#define MAX_SMALL_ENEMIES 40
#define EXP 2

class SmallEnemy : public Player
{
public:
    SmallEnemy();
    ~SmallEnemy();
    SDL_Point Make_random_point()
    {
        SDL_Point p;
        int a = rand()%SCREEN_WIDTH;
        int b = rand()%SCREEN_HEIGHT;
        p.x = a; p.y = b;
        return p;
    }

    void set_clips();
    void Show(SDL_Renderer *des);
    void Follow(MainObject &player);
    void SetSpawnPoint(SDL_Point &position);
    SDL_Rect GetRect();

    float Get_X_Pos() {return x_pos;}
    float Get_Y_Pos() {return y_pos;}
    int Get_Height_Frame() {return height_frame_;}
    int Get_Width_Frame() {return width_frame_;}
    bool LoadImg(std::string path, SDL_Renderer *screen);

    std::vector<SmallEnemy*> Make_S_Spawner()
{
    std::vector<SmallEnemy*> SmallSpawner;

    SmallEnemy* smallenemy = new SmallEnemy[MAX_SMALL_ENEMIES];
    for(int i=0;i<MAX_SMALL_ENEMIES;i++)
    {
        SmallEnemy* object = smallenemy + i;

        if(object != NULL)
        {
            SDL_Point random = Make_random_point();
            object->LoadImg("images/Run_Right.png", g_screen);
            object->set_clips();
            object->SetSpawnPoint(random);
            SmallSpawner.push_back(object);
        }
    }
    return SmallSpawner;
}

    void Set_Speed() {SMALL_ENEMY_SPEED ++;}
    void Set_Dame() {SMALL_ENEMY_DAME ++;}

    int SMALL_ENEMY_SPEED = 1;
    int SMALL_ENEMY_DAME = 2;

private:

    float x_pos;
    float y_pos;

    int frame_;
    int height_frame_;
    int width_frame_;
    SDL_Rect frame_clips[6];

    bool is_move;
};

class Exp : public Player
{
public:
    bool Load(std::string path, SDL_Renderer *des);
    void Set_Position(int x, int y) {r_exp.x = x; r_exp.y = y;}
    SDL_Rect GetRect() {return r_exp;}

    SDL_Rect r_exp;
    SDL_Texture* exp_orb;
};

#endif // SMALL_ENEMY_H_
