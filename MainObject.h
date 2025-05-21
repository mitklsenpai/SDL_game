
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "commonFunc.h"
#include "Player.h"
#include "Gun.h"

class Gun;

struct Boost_Bar
{
    SDL_Rect clips[50];
    SDL_Rect progress_clips[9];
    int currentFrame;
    int currentProgressFrame;
    SDL_Texture *Texture;
    SDL_Texture *progress;
    SDL_Rect Position;
    Uint32 FrameDuration;
    Uint32 LastTime = 0;
    Uint32 Last = 0;
};

class MainObject : public Player
{
public:
    MainObject(SDL_Renderer *des, Gun &gunRef);

    ~MainObject();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
        GO_UP = 2,
        GO_DOWN = 3
    };

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event svents, SDL_Renderer* screen);
    void set_clips();
    void DoPlayer();
    void Normalize_Motion(float &x_val_, float &y_val_);
    void ShowBar(SDL_Renderer *des);
    void UpdateBoostFrame(bool &player_nuke, bool &player_enemy, bool &bullet_enemy, bool &bullet_lich);

    float Get_x_pos(){return x_pos_;}
    float Get_y_pos(){return y_pos_;}
    float Get_height_frame() {return height_frame_;}
    float Get_width_frame() {return width_frame_;}
    SDL_Rect GetRect() {return rect_;}
    void Minus_Hp_When_Hit(int dame) {hp -= dame;}
    bool Dead();
    void Score(SDL_Renderer *des, TTF_Font *font);
    void Set_score() {score++;}
    void Reset_status();
    void ResetInput();
    void SetExp(int x) {G_EXP += x;}
    int &GetLEVEL() {return LEVEL;}
    int &GetExp() {return G_EXP;}
    int &GetMaxExp() {return MAX_EXP;}

    int &GetSpeed() {return PLAYER_SPEED;}
    int &GetMaxHp() {return MAX_HP;}
//buff
    void RenderBoost(SDL_Renderer *des);
    void TriggerAdrenaline();
    void TriggerEndophine();
    void IncreaseSpeed();
    void IncreaseMaxHealth();
    void Healing();

    int G_EXP;
    int MAX_EXP;
    int LEVEL;
private:
    Gun &gun;

    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    bool is_dead;
    bool IsReverse;
    bool InProgress;
    bool IsAdrenaline;
    bool IsEndophine;
    bool wasEndophineActive;
    bool wasAdrenalineActive;

    SDL_Rect frame_clip_[4];
    Input input_type_;
    int frame_;
    int status_;
    int score;

    int PLAYER_SPEED = 3;
    int hp = 100;
    int MAX_HP = 100;

    int original_dame;
    int original_hp;

    SDL_Texture *HP_Bar_Inner;
    SDL_Texture *HP_Bar_Outer;
    SDL_Texture *Exp_Bar_Outer;

    struct HP_Bar
    {
        SDL_Rect HP_Inner;
        SDL_Rect HP_Outer;
    }HP_Bar;

    struct Exp_Bar
    {
        SDL_Rect Exp_Inner;
        const SDL_Rect Exp_Outer = {0,30,254,8};
    }Exp_Bar;


    Boost_Bar Adrenaline;
    Boost_Bar Endophine;
};



#endif // MAIN_OBJECT_H_
