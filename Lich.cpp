
#include "Lich.h"

Lich::Lich(SDL_Renderer *des)
{
    // main
    x_pos = 0;
    y_pos = 0;
    Hp = 100;
    renderer = des;

    isDeathStarted = false;
    isDeathAnimationFinished = false;
    hasDroppedExp = false;

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

Lich::~Lich()
{
    SDL_DestroyTexture(LitchTexture);
    SDL_DestroyTexture(tele_skill);

    for (Exp* exp : Exp_list) {
        if (exp) {
            SDL_DestroyTexture(exp->exp_orb);
            delete exp;
        }
    }
    Exp_list.clear();
}

SDL_Rect Lich::GetRect()
{
    SDL_Rect res = {x_pos + 31, y_pos + 19, 17, 43};
    return res;
}

void Lich::Reset()
{
    Hp = 100;
    currentState = IDLE;
}

bool Lich::IsTelePorting()
{
    if(currentState == TELEPORTING){
        return true;
    }
    return false;
}

void Lich::UpdateSkill(NukeManager &nukemanager, MainObject &player)
{
    Uint32 currentTime = SDL_GetTicks();
    if(IsDead()){
        UpdateDeadFrame(currentTime);
        if(isDeathAnimationFinished && !hasDroppedExp && LitchDeathTexture == nullptr){
            DropExp();
        }
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

void Lich::UpdateTeleSkill(Uint32 currentTime)
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

void Lich::UpdateCastingSkill(Uint32 currentTime, NukeManager &nukemanager, MainObject &player)
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

void Lich::UpdateDeadFrame(Uint32 currentTime)
{
    SkillData* Death = Combo[2];

    if(currentTime - Death->casting_time >= Death->frame_duration){
        if(Death->currentFrame < 8)
            Death->currentFrame ++;
        else{
            isDeathAnimationFinished = true;
            SDL_DestroyTexture(LitchDeathTexture);
            LitchDeathTexture = nullptr;
        }
        Death->casting_time = currentTime;
    }
}

void Lich::DropExp()
{
    if(!hasDroppedExp){
        std::cout  << "lich da chet tao 10 orb" <<std::endl;
        for(int i=0;i < 10; i++)
        {
            Exp* exp = new Exp;
            exp->Load("images//lich_exp_orb.png", renderer);
            exp->Set_EXP(LICH_EXP);
            int x = x_pos + (rand() % 80 - 40);
            int y = y_pos + (rand() % 80 - 40);
            exp->Set_Position(x, y);
            std::cout << "Exp created at (" << x << ", " << y << ")" << std::endl;
            Exp_list.push_back(exp);
        }
        hasDroppedExp = true;
    }
}

void Lich::Activate(SDL_Renderer *des, NukeManager &nukemanager, MainObject &player)
{
    SDL_Rect pos = {x_pos, y_pos, 80, 80};
    if(IsDead()){
        int deathFrame = Combo[2]->currentFrame;
        deathFrame = std::min(deathFrame, 8);
        PlayAnimation(des, LitchDeathClips, deathFrame, pos, LitchDeathTexture);
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

void Lich::MinusHP(int dame)
{
    Hp-=dame;
}

void Lich::ShowHpBar(SDL_Renderer *des)
{
    double progress = Hp*0.16;
    SDL_Rect rect2 = {x_pos + 30, y_pos + 65, int(progress), 2};
    SDL_SetRenderDrawColor(des, 144, 238, 144, 255);
    SDL_RenderDrawRect(des, &rect2);
}

bool Lich::IsDead()
{
    if(Hp <= 0){
        return true;
    }
    return false;
}
