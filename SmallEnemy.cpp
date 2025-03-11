
#include "SmallEnemy.h";
#include "commonFunc.h"
#include "MainObject.h"

SmallEnemy::SmallEnemy()
{
    x_pos = 0;
    y_pos = 0;

    x_val = 0;
    y_val = 0;

    frame_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;

    status = -1;
}

SmallEnemy::~SmallEnemy()
{

}

void SmallEnemy::SetSpawnPoint(float &x, float &y)
{
    x_pos = x;
    y_pos = y;
}

bool SmallEnemy::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Player::LoadImg(path, screen);

    if(ret == true)
    {
        width_frame_ = rect_.w/6;   // thông tin về 1 frame quai vat
        height_frame_ = rect_.h;
    }
    return ret;
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

void SmallEnemy::Show(SDL_Renderer* des)
{
    if(status == Right)
    {
        LoadImg("images//Run_Right.png", des);
    }
    else
    {
        LoadImg("images//Run_left.png", des);
    }

    if(input_type.rigth_ == 1 || input_type.left_ == 1 || input_type.up_ == 1 || input_type.down_ == 1)
    {
        frame_++;
    }
    else
    {
        frame_ = 0;
    }

    if(frame_ > 6)
    {
        frame_ = 0;
    }

    rect_.x = x_pos;
    rect_.y = y_pos;

    SDL_Rect* current_clip = &frame_clips[frame_];  // hàm lấy thông tin của frame hiện tại

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};  // hàm lấy thông tin của frame (vị trí frame, kích thước)

    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);  // hàm chạy animation
}

void SmallEnemy::Follow(MainObject &player)
{
    int player_x_ = player.Get_x_pos();
    int player_y_ = player.Get_y_pos();
    float diff_x,diff_y,distance,normalize_x,normalize_y,enemy_move_x,enemy_move_y;
// quai chay theo nhan vat
    diff_x = player_x_ - x_pos;
    diff_y = player_y_ - y_pos;

    distance = sqrt((diff_x*diff_x + diff_y*diff_y));

    if(distance != 0)
    {
        normalize_x = diff_x/distance;
        normalize_y = diff_y/distance;

        enemy_move_x = normalize_x * SMALL_ENEMY_SPEED;
        enemy_move_y = normalize_y * SMALL_ENEMY_SPEED;
    }

    if(x_pos+=enemy_move_x)
    {
        status = Right;
        input_type.rigth_ = 1;
    }
    if(y_pos+=enemy_move_y)
    {
        status = Up;
        input_type.up_ = 1;
    }
}
