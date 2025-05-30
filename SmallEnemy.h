
#ifndef SMALL_ENEMY_H_
#define SMALL_ENEMY_H_

#include "commonFunc.h"
#include "Player.h"
#include "MainObject.h"


class SmallEnemy : public Player
{
public:
    SmallEnemy();
    ~SmallEnemy();
    SDL_Point Make_random_point(int min_radius, int max_radius)
    {
        SDL_Point p;
        float angle = static_cast<float>(rand() % 360) * (M_PI / 180.0f);
        float radius = min_radius + static_cast<float>(rand() % (max_radius - min_radius));

        p.x = 640 + static_cast<int>(radius * cos(angle));
        p.y = 320 + static_cast<int>(radius * sin(angle));

        p.x = std::clamp(p.x, 0, SCREEN_WIDTH);
        p.y = std::clamp(p.y, 0, SCREEN_HEIGHT);
        return p;
    }

    void set_clips();
    void Show(SDL_Renderer *des);
    void Follow(MainObject &player, float deltaTime);
    void SetSpawnPoint(SDL_Point &position);
    SDL_Rect GetRect();

    float Get_X_Pos() {return x_pos;}
    float Get_Y_Pos() {return y_pos;}
    int Get_Height_Frame() {return height_frame_;}
    int Get_Width_Frame() {return width_frame_;}
    bool LoadImg(std::string path, SDL_Renderer *screen);
    void Set_Speed() {SMALL_ENEMY_SPEED += 0.1;}
    void Set_Dame() {SMALL_ENEMY_DAME += 0.1;}
    void SetMove(bool status) {is_move = status;}

    void MinusHP(int dame);
    void ShowHpBar(SDL_Renderer *des);
    bool IsDead();

    std::vector<SmallEnemy*> EnemyWave()
    {
        std::vector<SmallEnemy*> SmallSpawner;
        for(int i=0;i<MAX_SMALL_ENEMIES;i++)
        {
            SmallEnemy *object = SpawnNewEnemy();
            SmallSpawner.push_back(object);
        }
        return SmallSpawner;
    }

    static SmallEnemy* SpawnNewEnemy()
    {
        SmallEnemy* newEnemy = new SmallEnemy();
        SDL_Point p = newEnemy->Make_random_point(400, 500);
        newEnemy->LoadImg("images//Run_Right.png", g_screen);
        newEnemy->set_clips();
        newEnemy->SetSpawnPoint(p);

        return newEnemy;
    }

    float SMALL_ENEMY_SPEED = 0.5;
    int SMALL_ENEMY_DAME = 2;
    static const int MAX_SMALL_ENEMIES = 40;
    const int SMALL_EXP = 2;


protected:

    float x_pos;
    float y_pos;

    int frame_;
    int height_frame_;
    int width_frame_;
    int MAX_HP;
    int Hp;
    int isRight;

    SDL_Texture *Run_Right = nullptr;
    SDL_Texture *Run_Left = nullptr;
    SDL_Rect frame_clips[6];

    Uint32 last_spawn_time = 0;
    bool is_move;
    float animationTimer = 0.0f;
    const float FRAME_DURATION = 0.1f;
    bool isForward = true;
};

class Exp : public Player
{
public:
    bool Load(std::string path, SDL_Renderer *des);
    void Show(SDL_Renderer *des, SDL_Texture *texture, SDL_Rect rect);
    void Set_Position(int x, int y) {r_exp.x = x; r_exp.y = y;}
    void Set_EXP(int exp) {EXP = exp;}
    SDL_Rect GetRect() {return r_exp;}

    int EXP;
    SDL_Rect r_exp;
    SDL_Texture* exp_orb;
};

#endif // SMALL_ENEMY_H_
