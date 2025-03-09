
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

void MainObject::Show(SDL_Renderer* des)   // ham dua hinh anh ra main
{
    if(status_ == WALK_LEFT || status_ == WALK_RIGHT)
    {
        LoadImg("images//right_left.png", des);
    }
    else if (status_ == GO_DOWN || status_ == GO_UP)
    {
        LoadImg("images//up_down.png", des);
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

// sử lý chuyển động
void MainObject::DoPlayer()
{
    x_val_ = 0;
    y_val_ = 0;

    if(input_type_.left_ == 1)
    {
        x_val_ -= PLAYER_SPEED;
    }
    else if(input_type_.rigth_ == 1)
    {
        x_val_ += PLAYER_SPEED;
    }
    else if(input_type_.up_ == 1)
    {
        y_val_ -= PLAYER_SPEED;
    }
    else if (input_type_.down_ == 1)
    {
        y_val_ += PLAYER_SPEED;
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if(x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if(x_pos_ + width_frame_ > SCREEN_WIDTH)
    {
        x_pos_ = SCREEN_WIDTH;
    }
    else if (y_pos_ < 0)
    {
        y_pos_ = 0;
    }
    else if(y_pos_ + height_frame_ > SCREEN_HEIGHT)
    {
        y_pos_ = SCREEN_HEIGHT;
    }
}
