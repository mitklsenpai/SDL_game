#include "Gun.h"
#include "commonFunc.h"
Gun::Gun(SDL_Renderer *des)
{
    x_pos = 0;
    y_pos = 0;
    x_target = 0;
    y_target = 0;
    last_shot = 0;
    bullet_delay = 200;
    last_bullet = 0;
    is_shot = false;

    bullet_texture = IMG_LoadTexture(des,"images//bullet.png");
}

Gun::~Gun()
{
    SDL_DestroyTexture(bullet_texture);
    for(auto bullet : bullets) delete bullet;
}

void Gun::HandleMouseEvents(SDL_Event event, SDL_Renderer* screen)
{
    if(event.type == SDL_MOUSEMOTION)
    {
        SDL_GetMouseState(&x_target, &y_target);
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState(&x_target, &y_target);
        if(!is_shot)
        {
            is_shot = true;
            last_bullet = 0;
            last_shot = SDL_GetTicks();
        }
    }
}

void Gun::update(AudioManager &audio)
{
    if(is_shot)
    {
        Uint32 currentTime = SDL_GetTicks();
        if(currentTime - last_shot >= bullet_delay)
        {
            if(last_bullet < MAX_BULLETS_PER_BURST)
            {
                SetBullet();
                audio.PlaySound("gun");
                last_shot = currentTime;
                last_bullet++;
            }
            else
            {
                is_shot = false;
                last_bullet = 0;
            }
        }
    }

    for(int i = bullets.size() - 1; i>=0; i--)
    {
        BulletBase *bullet = bullets.at(i);
        if(bullet!=nullptr || !is_shot)
        {
            bullet->x_pos += cos(bullet->angle) * FIRERATE;
            bullet->y_pos += sin(bullet->angle) * FIRERATE;
        }
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
        float diff_x = x_target - x_pos;
        float diff_y = y_target - y_pos;
        bullet->angle = atan2(diff_y,diff_x);

        bullet->x_pos = x_pos + GUN_OFFSET + cos(bullet->angle);
        bullet->y_pos = y_pos + GUN_OFFSET + sin(bullet->angle);

        bullets.push_back(bullet);
}


void Gun::ShowBullet(SDL_Renderer *des)
{
    for(int i=bullets.size() - 1; i>=0; i--)
    {
        BulletBase* bullet = bullets.at(i);
        if(bullet != NULL)
        {

            BulletRect_.x = bullet->x_pos;
            BulletRect_.y = bullet->y_pos;
            BulletRect_.w = 10;
            BulletRect_.h = 10;
            if(BulletRect_.x < 0 || BulletRect_.y < 0 || BulletRect_.x + BulletRect_.w > SCREEN_WIDTH || BulletRect_.h + BulletRect_.y > SCREEN_HEIGHT)
            {
                delete bullet;
                bullet = NULL;
                bullets.erase(bullets.begin() + i);
            }
            else
            {
                SDL_RenderCopy(des,bullet_texture,NULL,&BulletRect_);
            }
        }
    }
}

void Gun::RemoveBullet(const int &index)
{
    int size = bullets.size();
    if(index < size && size > 0)
    {
        BulletBase* bullet = bullets.at(index);
        if(bullet != NULL)
        {
            delete bullet;
            bullet = NULL;
        }
        bullets.erase(bullets.begin() + index);
    }
}
