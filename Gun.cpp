#include "Gun.h"
#include "commonFunc.h"
Gun::Gun()
{
    x_pos = 0;
    y_pos = 0;
    x_target = 0;
    y_target = 0;
    is_shot = false;
}

Gun::~Gun()
{

}

void Gun::HandleMouseEvents(SDL_Event event, SDL_Renderer* screen)
{
    switch(event.type)
    {
    case SDL_MOUSEMOTION:
        {
            int x,y;
            SDL_GetMouseState(&x, &y);
            x_target = x; y_target = y;
            break;
        }
    case SDL_MOUSEBUTTONDOWN:
        {
            is_shot = true;
            break;
        }
    case SDL_MOUSEBUTTONUP:
        {
            is_shot = false;
            break;
        }
    }
}

void Gun::SetPosition()
{

}

bool Gun::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Player::LoadImg(path, screen);
    return ret;
}

void Gun::Rotation(MainObject& player, SDL_Renderer* des)
{
    float player_x = player.Get_x_pos();
    float player_y = player.Get_y_pos();

    SDL_Point center;
    center.x = player_x + player.Get_width_frame()*0.1;
    center.y = player_y;

    float diff_x = x_target - x_pos;
    float diff_y = y_target - y_pos;

    float angle = atan2(diff_y,diff_x)*180 / M_PI;

    x_pos = center.x;
    y_pos = center.y;

    rect_.x = x_pos;
    rect_.y = y_pos;

    SDL_Rect renderQuad = {rect_.x, rect_.y, 48, 48};

    SDL_RenderCopyEx(des,p_object_,NULL,&renderQuad,angle,NULL,SDL_FLIP_NONE);
}
