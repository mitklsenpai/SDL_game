
#ifndef BOMBER_H_
#define BOMBER_H_
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

class Bomber : public SmallEnemy
{
public:
    Bomber(SDL_Renderer *des);
    ~Bomber();

    void UpdateSkill(NukeManager &nukemanager, MainObject &player);
    void UpdateCastingSkill(Uint32 currentTime, NukeManager &nukemanager, MainObject &player);
    void UpdateTeleSkill(Uint32 currentTime);
    void UpdateDeadFrame(Uint32 currentTime);
    void Activate(SDL_Renderer *des, NukeManager &nukemanager, MainObject &player);
    bool IsDead();
    void ShowHpBar(SDL_Renderer *des);
    void MinusHP(int dame);
    SDL_Rect GetRect();
    void Reset();

    enum SkillType
    {
        IDLE,
        TELEPORTING,
        CASTING_SKILL,
        COOLDOWN,
        DEAD,
    };

private:
    float x_pos;
    float y_pos;
    int Hp;
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
};



#endif // BOMBER_H_
