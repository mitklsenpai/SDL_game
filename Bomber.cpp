
#include "Bomber.h"

Bomber::Bomber(SDL_Renderer *des)
{
    // main
    x_pos = 0;
    y_pos = 0;
    Hp = 10;
    LitchTexture = Loadimg("images//The Summoner.png", des);
    LitchDeathTexture = Loadimg("images//The Summoner Death.png", des);
    tele_skill = IMG_LoadTexture(des, "images//Tele effect.png");
    setClips(LitchClips, 12, 80, 80);
    setClips(TeleClips, 13, 64, 64);
    setClips(LitchDeathClips, 9, 80, 80);

    SkillData* Tele = new SkillData{0, 77, 0, 0};
    SkillData* Skill_1 = new SkillData{0, 83, 10, 0};
    SkillData* Death = new SkillData{0, 100, 0, 0};
    Combo.push_back(Tele);
    Combo.push_back(Skill_1);
    // Combo.push_back(Skill_2)...
    Combo.push_back(Death);

}

Bomber::~Bomber()
{
    SDL_DestroyTexture(LitchTexture);
    SDL_DestroyTexture(tele_skill);
}

SDL_Rect Bomber::GetRect()
{
    SDL_Rect res = {x_pos, y_pos, 80, 80};
    return res;
}

void Bomber::Reset()
{
    Hp = 10;
}

void Bomber::UpdateSkill(NukeManager &nukemanager, MainObject &player)
{
    Uint32 currentTime = SDL_GetTicks();
    if(IsDead()){
        UpdateDeadFrame(currentTime);
    }
    else{
        nukemanager.updateBomb(player);
        switch(currentState)
        {
            case IDLE:
            {
                currentState = CASTING_SKILL;
                break;
            }
            case TELEPORTING:
            {
                UpdateTeleSkill(currentTime);
                break;
            }
            case CASTING_SKILL:
            {
                UpdateCastingSkill(currentTime, nukemanager, player);
                break;
            }
            case COOLDOWN:
            {
                if(currentTime - CoolDownStart >= CoolDownBetweenSkills)
                {
                    currentState = IDLE;
                    CoolDownStart = currentTime;
                }
                break;
            }
        }
    }
}

void Bomber::UpdateTeleSkill(Uint32 currentTime)
{
    SkillData *TelePorting = Combo[0];
    if(currentTime - TelePorting->casting_time >= TelePorting->frame_duration){
        TelePorting->currentFrame++;

        if(TelePorting->currentFrame == 5){
            SDL_Point Target = Make_random_point(200, 300);
            x_pos = Target.x;
            y_pos = Target.y;
        }
        else if(TelePorting->currentFrame >= 12){
            currentState = COOLDOWN;
            TelePorting->currentFrame = 0;
        }

        TelePorting->casting_time = currentTime;
    }
}

void Bomber::UpdateCastingSkill(Uint32 currentTime, NukeManager &nukemanager, MainObject &player)
{
    SkillData* Casting = Combo[1];
    if(currentTime - Casting->casting_time >= Casting->frame_duration){
        Casting->currentFrame++;
        if(Casting->currentFrame >= 11){
            SDL_Rect pos = player.GetRect();
            SDL_Point target = {pos.x, pos.y};
            nukemanager.SpawnBomb(5, target);

            currentState = TELEPORTING;
            Casting->currentFrame = 0;
        }
        Casting->casting_time = currentTime;
    }
}

void Bomber::UpdateDeadFrame(Uint32 currentTime)
{
    SkillData* Death = Combo[2];
    if(currentTime - Death->casting_time >= Death->frame_duration){
        Death->currentFrame ++;
        Death->casting_time = currentTime;
    }
}

void Bomber::Activate(SDL_Renderer *des, NukeManager &nukemanager, MainObject &player)
{
    SDL_Rect pos = {x_pos, y_pos, 80, 80};
    if(IsDead()){
        PlayAnimation(des, LitchDeathClips, Combo[2]->currentFrame, pos, LitchDeathTexture);
    }
    else
    {
        ShowHpBar(des);
        switch(currentState)
        {
            case TELEPORTING:
            {
                PlayAnimation(des, TeleClips, Combo[0]->currentFrame, pos, tele_skill);
                break;
            }
            case CASTING_SKILL:
            {
                PlayAnimation(des, LitchClips, Combo[1]->currentFrame, pos, LitchTexture);
                break;
            }
        }
        nukemanager.Render(des);
    }
}

void Bomber::MinusHP(int dame)
{
    Hp-=dame;
}

void Bomber::ShowHpBar(SDL_Renderer *des)
{
    double progress = Hp*1.6;
    SDL_Rect rect2 = {x_pos + 17, y_pos + 34, progress, 2};
    SDL_SetRenderDrawColor(des, 144, 238, 144, 255);
    SDL_RenderDrawRect(des, &rect2);
}

bool Bomber::IsDead()
{
    if(Hp <= 0){
        return true;
    }
    return false;
}
