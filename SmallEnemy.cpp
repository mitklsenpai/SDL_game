
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

    if(input_type.rigth_ == 1 || input_type.left_ == 1)
    {
        frame_++;
    }
    else
    {
        frame_ = 0;
    }

    if(frame_ > 6){frame_ = 0;}

    rect_.x = x_pos;
    rect_.y = y_pos;

    SDL_Rect* current_clip = &frame_clips[frame_];  // hàm lấy thông tin của frame hiện tại

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};  // hàm lấy thông tin của frame (vị trí frame, kích thước)

    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);  // hàm chạy animation
}

void SmallEnemy::Moving()
{
    x_val = 0;
    y_val = 0;

    if(input_type.rigth_ == 1)
    {
        x_val += SMALL_ENEMY_SPEED;
    }
    else if(input_type.left_ == 1)
    {
        x_val -= SMALL_ENEMY_SPEED;
    }

    x_pos+=x_val;
    y_pos+=y_val;

    if(x_pos < 0)
    {
        x_pos = 0;
    }
    else if(y_pos < 0)
    {
        y_pos = 0;
    }
    else if(x_pos + width_frame_ > SCREEN_WIDTH)
    {
        x_pos = SCREEN_WIDTH - width_frame_;
    }
    else if(y_pos + height_frame_ > SCREEN_HEIGHT)
    {
        y_pos = SCREEN_HEIGHT - width_frame_;
    }
}

//void SmallEnemy::MovingToPlayer(MainObject &p_object)
//{
//    double distance;
//    int player_x_pos = p_object.x_pos_;
//    int player_y_pos = p_object.y_pos_;
//
//    distance = pow((x_pos - player_x_pos),2) + pow()
//}
