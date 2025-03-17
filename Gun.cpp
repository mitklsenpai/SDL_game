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
    Free();
}

void Gun::HandleMouseEvents(SDL_Event event, SDL_Renderer* screen)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        x_target = x; y_target = y;
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
    BulletBase *bullet = new BulletBase();
    if(is_shot)
    {
        float diff_x = x_target - x_pos;
        float diff_y = y_target - y_pos;
        bullet->angle = atan2(diff_y,diff_x);
        float gun_offset = 20; //chieu dai cay sung
        bullet->x_pos = x_pos + gun_offset + cos(bullet->angle);
        bullet->y_pos = y_pos + gun_offset + sin(bullet->angle);

        bullets.push_back(bullet);
    }
    else if(is_shot == false)
    {
        delete bullet;
        bullet = NULL;
    }
}

void Gun::ShowBullet(SDL_Renderer *des)
{
    bullet_texture = IMG_LoadTexture(des,"images//bullet.png");
    for(int i=0;i<(int) bullets.size();i++)
    {
        BulletBase* bullet = bullets.at(i);
        if(bullet != NULL)
        {
            bullet->x_pos += cos(bullet->angle) * FIRERATE;
            bullet->y_pos += sin(bullet->angle) * FIRERATE;

            BulletRect_.x = bullet->x_pos;
            BulletRect_.y = bullet->y_pos;
            BulletRect_.w = 10;
            BulletRect_.h = 10;
            SDL_RenderCopy(des,bullet_texture,NULL,&BulletRect_);
        }
    }
}
