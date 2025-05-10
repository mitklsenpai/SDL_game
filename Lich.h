
#ifndef LICH_H_
#define LICH_H_
#include "commonFunc.h"
#include "SmallEnemy.h"
#include "MainObject.h"
#include "Nuke.h"

class SkillData
{
public:
    SkillData(Uint32 casting_time,
              Uint32 frame_duration,
                float damage,int currentFrame)
    {
        this->casting_time = casting_time;
        this->frame_duration = frame_duration;
        this->damage = damage;
        this->currentFrame = currentFrame;
    }

    Uint32 casting_time;
    Uint32 frame_duration;
    float damage;
    int currentFrame;
};

class Lich : public SmallEnemy
{
public:
    Lich(SDL_Renderer *des);
    ~Lich();

    void UpdateSkill(NukeManager &nukemanager, MainObject &player);
    void UpdateCastingSkill(Uint32 currentTime, NukeManager &nukemanager, MainObject &player);
    void UpdateTeleSkill(Uint32 currentTime);
    void UpdateDeadFrame(Uint32 currentTime);
    void DropExp();
    void Activate(SDL_Renderer *des, NukeManager &nukemanager, MainObject &player);
    bool IsDead();
    void ShowHpBar(SDL_Renderer *des);
    void MinusHP(int dame);
    SDL_Rect GetRect();
    void Reset();
    bool IsTelePorting();

    std::vector<Exp*>& GetExpList() {return Exp_list;}
    enum SkillType
    {
        IDLE,
        TELEPORTING,
        CASTING_SKILL,
        COOLDOWN,
        DEAD,
    };

    const int LICH_EXP = 5;

private:
    SDL_Renderer *renderer;

    float x_pos;
    float y_pos;
    float Hp;

    int isDeathStarted;
    int isDeathAnimationFinished;
    int hasDroppedExp;

    SkillType currentState = IDLE;
    Uint32 CoolDownStart = 0;
    Uint32 CoolDownBetweenSkills = 2000;

    SDL_Texture *LitchTexture = nullptr;
    SDL_Rect LitchClips[12];
    SDL_Texture *LitchDeathTexture = nullptr;
    SDL_Rect LitchDeathClips[9];
    SDL_Texture *tele_skill = nullptr;
    SDL_Rect TeleClips[13];
    std::vector<SkillData*> Combo;
    std::vector<Exp*> Exp_list;
};



#endif
