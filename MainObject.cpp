
#include "MainObject.h"
#include "commonFunc.h"

MainObject::MainObject()
{
    frame_ = 0;
    x_pos_ = 570;
    y_pos_ = 270;
    x_val_ = 0;
    y_val_ = 0;                     // thong so cua Nhan Vat chinh
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.rigth_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;
}


MainObject::~MainObject()
{


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
        width_frame_ = rect_.w/4;   // thông tin về 1 frame nhân vật
        height_frame_ = rect_.h;
    }
    return ret;
}

void MainObject::set_clips()
{
    if(width_frame_>0 && height_frame_ >0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].h = height_frame_;
        frame_clip_[0].w = width_frame_;

        frame_clip_[1].x = width_frame_;
        frame_clip_[1].y = 0;
        frame_clip_[1].h = height_frame_;
        frame_clip_[1].w = width_frame_;

        frame_clip_[2].x = 2*width_frame_;
        frame_clip_[2].y = 0;
        frame_clip_[2].h = height_frame_;
        frame_clip_[2].w = width_frame_;

        frame_clip_[3].x = 3*width_frame_;
        frame_clip_[3].y = 0;
        frame_clip_[3].h = height_frame_;
        frame_clip_[3].w = width_frame_;       // xét animation cho các khung hình
    }
}

// ham dua hinh anh ra main
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
    else
    {
        frame_ = 0;
    }

    if(frame_>=4)
    {
        frame_ = 0;
    }

    rect_.x = x_pos_;
    rect_.y = y_pos_;

    SDL_Rect* current_clip = &frame_clip_[frame_];  // hàm lấy thông tin của frame hiện tại

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};  // hàm lấy thông tin của frame (vị trí frame, kích thước)

    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);  // hàm chạy animation
}


void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)  // hàm sử lý sự kiện từ bàn phím, di chuyển cho nhân vật
{
    if(events.type == SDL_KEYDOWN) //khi phim nhan
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
    else if(events.type == SDL_KEYUP) // khi phim ko nhan
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

// xử lý chuyển động
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

