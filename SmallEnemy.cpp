
#include "SmallEnemy.h";
#include "commonFunc.h"
SmallEnemy::SmallEnemy()
{
    x_pos = 0;
    y_pos = 0;

    frame_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    MAX_HP = 10;
    Hp = 10;

    is_move = false;
}

SmallEnemy::~SmallEnemy()
{
}

void SmallEnemy::MinusHP(int dame)
{
    Hp-=dame;
}

void SmallEnemy::ShowHpBar(SDL_Renderer *des)
{
    double progress = Hp*1.6;
    SDL_Rect rect2 = {x_pos + 17, y_pos + 34, progress, 2};
    SDL_SetRenderDrawColor(des, 144, 238, 144, 255);
    SDL_RenderDrawRect(des, &rect2);
}

bool SmallEnemy::IsDead()
{
    if(Hp <= 0)
        return true;
    return false;
}

bool SmallEnemy::LoadImg(std::string path, SDL_Renderer *des)
{
    bool ret = Player::LoadImg(path,des);
    if(ret)
    {
        width_frame_ = rect_.w/6;
        height_frame_ = rect_.h;
    }
    return ret;
}


void SmallEnemy::SetSpawnPoint(SDL_Point &position)
{
    x_pos = position.x;
    y_pos = position.y;
}

SDL_Rect SmallEnemy::GetRect()
{
    SDL_Rect r_;
    r_.x = x_pos;
    r_.y = y_pos;
    r_.h = height_frame_;
    r_.w = width_frame_;

    return r_;
}


void SmallEnemy::set_clips()
{
    if(height_frame_>0 && width_frame_>0)
    {
        for(int i=0;i<6;i++)
        {
            frame_clips[i].x = i*width_frame_;
            frame_clips[i].y = 0;
            frame_clips[i].h = height_frame_;
            frame_clips[i].w = width_frame_;
        }
    }
}

void SmallEnemy::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos;
    rect_.y = y_pos;

    SDL_Rect* current_clip = &frame_clips[frame_];

//    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
    SDL_Rect renderQuad = {rect_.x, rect_.y, 48, 48};
    SDL_RenderCopy(screen, p_object_, current_clip, &renderQuad);
}

void SmallEnemy::Follow(MainObject &player, float deltaTime)
{
    int player_x_ = player.Get_x_pos();
    int player_y_ = player.Get_y_pos();
    float diff_x,diff_y,distance,normalize_x,normalize_y,enemy_move_x,enemy_move_y;
    diff_x = player_x_ - x_pos;
    diff_y = player_y_ - y_pos;

    distance = sqrt((diff_x*diff_x + diff_y*diff_y));

    if(distance != 0)
    {
        normalize_x = diff_x/distance;
        normalize_y = diff_y/distance;

        enemy_move_x = normalize_x * SMALL_ENEMY_SPEED;
        enemy_move_y = normalize_y * SMALL_ENEMY_SPEED;
        x_pos+=enemy_move_x;
        y_pos += enemy_move_y;
        is_move = true;

        animationTimer += deltaTime;
        if (animationTimer >= FRAME_DURATION) {
            animationTimer = 0.0f;
            if (isForward) {
                frame_++;
                if (frame_ >= 5) isForward = false;
            } else {
                frame_--;
                if (frame_ <= 0) isForward = true;
            }
        }
    }
    else
    {
        is_move = false;
    }
}

bool Exp::Load(std::string path, SDL_Renderer *des)
{
    if(exp_orb == NULL)
    {
        exp_orb = Loadimg("images//exp_orb.png", des);
        r_exp.h = 7;
        r_exp.w = 7;
        return true;
    }
    return false;
}
