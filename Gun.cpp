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
    if(event.type == SDL_MOUSEMOTION)
        {
            int x,y;
            SDL_GetMouseState(&x, &y);
            x_target = x; y_target = y;
        }
    else if(event.type == SDL_MOUSEBUTTONDOWN)
        {
                is_shot = true;
        }
    else if(event.type == SDL_MOUSEBUTTONUP)
        {
            is_shot = false;
        }
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

void Gun::SetBullet()
{
    float diff_x = x_target - x_pos;
    float diff_y = y_target - y_pos;

    if(is_shot)
    {
        BulletBase *bullet = new BulletBase();
        bullet->angle = atan2(diff_y,diff_x)*180 / M_PI;
        bullet->x_pos = x_pos * cos(bullet->angle);
        bullet->y_pos = y_pos * sin(bullet->angle);

        bullets.push_back(bullet);
    }
}

void Gun::ShowBullet(SDL_Renderer *des)
{
    for(int i=0;i<(int) bullets.size();i++)
    {
        BulletBase* bullet = bullets.at(i);
        if(bullet != NULL)
        {
            bullet_texture = IMG_LoadTexture(des,"images//bullet.png");
            bullet->x_pos += FIRERATE * cos(bullet->angle);
            bullet->y_pos += FIRERATE * sin(bullet->angle);

            BulletRect_.x = bullet->x_pos;
            BulletRect_.y = bullet->y_pos;
            BulletRect_.w = 10;
            BulletRect_.h = 10;
            SDL_RenderCopy(des,bullet_texture,NULL,&BulletRect_);

            if(bullet->x_pos < 0 || bullet->y_pos < 0 || bullet->x_pos > SCREEN_WIDTH || bullet->y_pos > SCREEN_HEIGHT)
            {
                SDL_DestroyTexture(bullet_texture);
            }
        }
    }
}
