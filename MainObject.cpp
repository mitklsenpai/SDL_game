
#include "MainObject.h"
#include "commonFunc.h"

MainObject::MainObject(SDL_Renderer *des, Gun &gunRef) : gun(gunRef)
{
    score = 0;
    frame_ = 0;
    x_pos_ = 570;
    y_pos_ = 270;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.rigth_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;
    LEVEL = 0;
    MAX_EXP = 10;
    G_EXP = 0;
    IsReverse = false;
    InProgress = true;
    IsAdrenaline = false;
    IsEndophine = false;
    wasEndophineActive = false;
    wasAdrenalineActive = false;
    original_dame = 0;
    original_hp = 0;

    LoadImg("images//4_direct_move.png", des);
    set_clips();
    HP_Bar_Inner = IMG_LoadTexture(des, "images//hp_bar_inner.png");
    HP_Bar_Outer = IMG_LoadTexture(des, "images//hp_bar_outer.png");
    Exp_Bar_Outer = IMG_LoadTexture(des, "images//experience_bar_background.png");

    Adrenaline.Texture = IMG_LoadTexture(des, "images//Adrenaline.png");
    Adrenaline.progress = IMG_LoadTexture(des, "images//Adrenaline_boost.png");
    Adrenaline.currentFrame = 0;
    Adrenaline.currentProgressFrame = 0;
    Adrenaline.FrameDuration = 80;
    Adrenaline.Position = {-30, 30, 154, 68};
    setClips(Adrenaline.clips, 50, 154, 68, 10, 5);
    setClips(Adrenaline.progress_clips, 9, 64, 64);

    Endophine.Texture = IMG_LoadTexture(des, "images//Rage.png");
    Endophine.progress = IMG_LoadTexture(des, "images//Endophine_boost.png");
    Endophine.currentFrame = 0;
    Endophine.currentProgressFrame = -1;
    Endophine.FrameDuration = 1000;
    Endophine.Position = {100, 41, 138, 36};
    setClips(Endophine.clips, 50, 138, 36, 10, 5);
    setClips(Endophine.progress_clips, 9, 64, 64);
}


MainObject::~MainObject()
{
}

void MainObject::ResetInput()
{
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.rigth_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;
}

void MainObject::Normalize_Motion(float &x_val, float &y_val)
{
    float distance = sqrt(x_val_*x_val_ + y_val_*y_val_);
    if(distance!=0)
    {
        float normal_x = (x_val_/distance)*PLAYER_SPEED;
        float normal_y = (y_val_/distance)*PLAYER_SPEED;

        x_pos_ += normal_x;
        y_pos_ += normal_y;
    }
}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Player::LoadImg(path, screen);

    if(ret == true)
    {
        width_frame_ = rect_.w/4;
        height_frame_ = rect_.h;
    }
    return ret;
}

void MainObject::set_clips()
{
    if(width_frame_>0 && height_frame_ >0)
    {
        for(int i=0;i<4;i++){
            frame_clip_[i] = {i*width_frame_, 0, width_frame_, height_frame_};
        }
    }
}

void MainObject::Show(SDL_Renderer* des)
{
    if(status_ == WALK_LEFT || status_ == WALK_RIGHT)
    {
        LoadImg("images//4_direct_move.png", des);
    }
    else if (status_ == GO_DOWN || status_ == GO_UP)
    {
        LoadImg("images//4_direct_move.png", des);
    }


    if(input_type_.left_ == 1 || input_type_.rigth_ == 1 || input_type_.down_ == 1 || input_type_.up_ == 1)
    {
        frame_++;
    }

    if(frame_>=4)
    {
        frame_ = 0;
    }

    rect_.x = x_pos_;
    rect_.y = y_pos_;

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_d:
            {
                status_ = WALK_RIGHT;
                input_type_.rigth_ = 1;
            }
            break;
        case SDLK_a:
            {
                status_ = WALK_LEFT;
                input_type_.left_ = 1;
            }
            break;
        case SDLK_w:
            {
                status_ = GO_UP;
                input_type_.up_ = 1;
            }
            break;
        case SDLK_s:
            {
                status_ = GO_DOWN;
                input_type_.down_ = 1;
            }
            break;
        }
    }
    else if(events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_d:
            {
                status_ = WALK_RIGHT;
                input_type_.rigth_ = 0;
            }
            break;
        case SDLK_a:
            {
                status_ = WALK_LEFT;
                input_type_.left_ = 0;
            }
            break;
        case SDLK_w:
            {
                status_ = GO_UP;
                input_type_.up_ = 0;
            }
            break;
        case SDLK_s:
            {
                status_ = GO_DOWN;
                input_type_.down_ = 0;
            }
            break;
        }
    }
}

void MainObject::DoPlayer()
{
    x_val_ = 0;
    y_val_ = 0;
    // di chuyen thang
    if(input_type_.left_ == 1 && input_type_.rigth_ == 0 && input_type_.down_ == 0 && input_type_.up_ == 0)
    {
        x_val_ -= PLAYER_SPEED;
        x_pos_ += x_val_;
    }
    else if(input_type_.rigth_ == 1 && input_type_.left_ == 0 && input_type_.down_ == 0 && input_type_.up_ == 0)
    {
        x_val_ += PLAYER_SPEED;
        x_pos_ += x_val_;
    }
    else if(input_type_.up_ == 1 && input_type_.down_ == 0 && input_type_.rigth_ == 0 && input_type_.left_ == 0)
    {
        y_val_ -= PLAYER_SPEED;
        y_pos_ += y_val_;
    }
    else if (input_type_.down_ == 1 && input_type_.up_ == 0 && input_type_.rigth_ == 0 && input_type_.left_ == 0)
    {
        y_val_ += PLAYER_SPEED;
        y_pos_ += y_val_;
    }
    // di chuyen cheo
    else if (input_type_.left_ == 1 && input_type_.up_ == 1 && input_type_.down_ == 0 && input_type_.rigth_ == 0)
    {
        x_val_ -= PLAYER_SPEED;
        y_val_ -= PLAYER_SPEED;

        Normalize_Motion(x_val_,y_val_);
    }
    else if (input_type_.rigth_== 1 && input_type_.up_ == 1 && input_type_.down_ == 0 && input_type_.left_ == 0)
    {
        x_val_ += PLAYER_SPEED;
        y_val_ -= PLAYER_SPEED;

        Normalize_Motion(x_val_,y_val_);
    }
    else if (input_type_.rigth_ == 1 && input_type_.down_ == 1 && input_type_.left_ == 0 && input_type_.up_ == 0)
    {
        x_val_ += PLAYER_SPEED;
        y_val_ += PLAYER_SPEED;

        Normalize_Motion(x_val_,y_val_);
    }
    else if (input_type_.left_ == 1 && input_type_.down_ == 1 && input_type_.rigth_ == 0 && input_type_.up_ == 0)
    {
        x_val_ -= PLAYER_SPEED;
        y_val_ += PLAYER_SPEED;

        Normalize_Motion(x_val_,y_val_);
    }

    // va cham voi man hinh
    if(x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if(x_pos_ + width_frame_ > SCREEN_WIDTH)
    {
        x_pos_ = SCREEN_WIDTH - width_frame_;
    }
    else if (y_pos_ < 0)
    {
        y_pos_ = 0;
    }
    else if(y_pos_ + height_frame_ > SCREEN_HEIGHT)
    {
        y_pos_ = SCREEN_HEIGHT - width_frame_;
    }

}

void MainObject::ShowBar(SDL_Renderer *des)
{
    SDL_RenderCopy(des, Exp_Bar_Outer, NULL, &Exp_Bar.Exp_Outer);
//    SDL_RenderCopy(des, Adrenaline.Texture, &Adrenaline.clips[0], &Adrenaline.Position);
//    SDL_RenderCopy(des, Endophine.Texture, &Endophine.clips[0], &Endophine.Position);

    HP_Bar.HP_Inner = {40, 10, hp*2.1, 12};
    HP_Bar.HP_Outer = {0, 0, MAX_HP*2.1 + 44, 32};

    double percent_progress = (double)G_EXP/MAX_EXP;
    double progress = 254.0*percent_progress;
    Exp_Bar.Exp_Inner = {0, 31, (int) progress, 6};

    SDL_SetRenderDrawColor(des, 255, 255, 0, 255);
    SDL_RenderFillRect(des, &Exp_Bar.Exp_Inner);

    SDL_RenderCopy(des, Adrenaline.Texture, &Adrenaline.clips[Adrenaline.currentFrame], &Adrenaline.Position);
    SDL_RenderCopy(des, Endophine.Texture, &Endophine.clips[Endophine.currentFrame], &Endophine.Position);
    SDL_RenderCopy(des, HP_Bar_Outer, NULL, &HP_Bar.HP_Outer);
    SDL_RenderCopy(des, HP_Bar_Inner, NULL, &HP_Bar.HP_Inner);
}

void MainObject::UpdateBoostFrame(bool &player_nuke, bool &player_enemy, bool &bullet_enemy, bool &bullet_lich)
{
    Uint32 currentTime = SDL_GetTicks();
    //boost Endophine
    if(IsEndophine != wasEndophineActive) {
        if (IsEndophine) {
            original_dame = gun.GetDame();
            original_hp = hp;
            gun.GetDame() += 5;
            hp += 20;
        } else {
            gun.GetDame() = original_dame;
            hp = original_hp;
        }
        wasEndophineActive = IsEndophine;
    }
    //boost Adrenaline
    if(IsAdrenaline != wasAdrenalineActive){
        if(IsAdrenaline){
            original_dame = gun.GetDame();
            original_hp = hp;
            gun.GetDame() ++;
            hp += 5;
        }
        else{
            gun.GetDame() = original_dame;
            hp = original_hp;
        }
        wasAdrenalineActive = IsAdrenaline;
    }
    // Endophine
    if(!player_enemy && !player_nuke){
        if(currentTime - Endophine.LastTime >= Endophine.FrameDuration){
            if(!IsReverse){
                Endophine.currentFrame ++;
                if(Endophine.currentFrame == 40){
                    Endophine.FrameDuration = 80;
                    IsEndophine = true;
                }
                else if(Endophine.currentFrame >= 49){
                    Endophine.currentFrame = 40;
                    IsReverse = true;
                }
            }
            else{
                Endophine.currentFrame --;
                if(Endophine.currentFrame <= 0){
                    Endophine.currentFrame = 0;
                    Endophine.FrameDuration = 1000;
                    IsReverse = false;
                    IsEndophine = false;
                }
            }
            Endophine.LastTime = currentTime;
        }
    }
    else{
        Endophine.currentFrame -= 3;
        if(Endophine.currentFrame <= 0){
            Endophine.currentFrame = 0;
            if (IsEndophine) {
                IsEndophine = false;
                gun.GetDame() = original_dame;
                hp = original_hp;
            }
        }
    }
    //Endophine progress
    if(IsEndophine){
        if(currentTime - Endophine.Last >= 80){
            Endophine.currentProgressFrame ++;
            if(Endophine.currentProgressFrame >= 8){
                Endophine.currentProgressFrame = 0;
            }
            Endophine.Last = currentTime;
        }
    }
    else{
        Endophine.currentProgressFrame = -1;
    }
    //Adrenaline
    if(bullet_enemy || bullet_lich){
        if(InProgress){
            if(Adrenaline.currentFrame >= 0 && Adrenaline.currentFrame <= 38){
                Adrenaline.currentFrame +=5;
            }
        }
    }
    else{
        if(currentTime - Adrenaline.LastTime >= 5000){
            Adrenaline.currentFrame --;
            if(Adrenaline.currentFrame <= 0){
                Adrenaline.currentFrame = 0;
            }
            Adrenaline.LastTime = currentTime;
        }
    }

    if(InProgress && Adrenaline.currentFrame >= 39 && Adrenaline.currentFrame <= 49){
        if(currentTime - Adrenaline.LastTime >= Adrenaline.FrameDuration){
            Adrenaline.currentFrame++;
            if(Adrenaline.currentFrame >= 49){
                Adrenaline.currentFrame = 39;
                InProgress = false;
                IsAdrenaline = true;
            }
            Adrenaline.LastTime = currentTime;
        }
    }
    if(!InProgress){
        Adrenaline.currentFrame --;
        if(Adrenaline.currentFrame <= 0){
            Adrenaline.currentFrame = 0;
            IsAdrenaline = false;
            InProgress = true;
        }
    }
    //Adrenaline progress
    if(IsAdrenaline){
        if(currentTime - Adrenaline.Last >= 80){
            Adrenaline.currentProgressFrame ++;
            if(Adrenaline.currentProgressFrame >= 8){
                Adrenaline.currentProgressFrame = 0;
            }
            Adrenaline.Last = currentTime;
        }
    }
    else{
        Adrenaline.currentProgressFrame = -1;
    }
}

void MainObject::RenderBoost(SDL_Renderer *des)
{
    if(!IsAdrenaline && !IsEndophine){
        return;
    }
    else if(IsAdrenaline){
        SDL_Rect Adrenaline_Position = {x_pos_, y_pos_ + 10, 64, 64};
        SDL_RenderCopy(des, Adrenaline.progress, &Adrenaline.progress_clips[Adrenaline.currentProgressFrame], &Adrenaline_Position);
    }
    else if(IsEndophine){
        SDL_Rect Endophine_Position = {x_pos_ , y_pos_ - 30, 64, 64};
        SDL_RenderCopy(des, Endophine.progress, &Endophine.progress_clips[Endophine.currentProgressFrame], &Endophine_Position);
    }
}

bool MainObject::Dead()
{
    if(hp<=0)
        return true;
    return false;
}

void MainObject::Reset_status()
{
    hp = 100;
    MAX_HP = 100;
    PLAYER_SPEED = 5;
    score = 0;
    frame_ = 0;
    x_pos_ = 570;
    y_pos_ = 270;
    x_val_ = 0;
    y_val_ = 0;
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.rigth_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;
    LEVEL = 0;
    MAX_EXP = 10;
    G_EXP = 0;
    IsAdrenaline = false;
    IsEndophine = false;
    wasAdrenalineActive = false;
    wasEndophineActive = false;
}

void MainObject::Score(SDL_Renderer *des, TTF_Font *font)
{
    std::string s = std::to_string(score);
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "KILLS: ", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(des, textSurface);

    SDL_Surface* Surface = TTF_RenderText_Solid(font, s.c_str(), textColor);
    SDL_Texture* Scores = SDL_CreateTextureFromSurface(des, Surface);

    SDL_Rect textRect = {1000, 0, textSurface->w, textSurface->h };
    SDL_Rect ScoreRect = {1060, 0, Surface->w, Surface->h };

    SDL_RenderCopy(des, textTexture, NULL, &textRect);
    SDL_RenderCopy(des, Scores, NULL, &ScoreRect);

    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(Surface);
}

void MainObject::IncreaseSpeed()
{
    int percent = round(PLAYER_SPEED*0.2);
    PLAYER_SPEED += percent;
}

void MainObject::IncreaseMaxHealth()
{
    int percent = round(MAX_HP*0.1);
    MAX_HP += percent;
}

void MainObject::Healing()
{
    if(hp == MAX_HP)
    {
        hp = MAX_HP;
    }
    else
    {
        float healHp = 0.15*MAX_HP;
        int newHp = hp + healHp;

        hp = std::min(newHp, MAX_HP);
    }
}
