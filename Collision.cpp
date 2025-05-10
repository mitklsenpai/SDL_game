#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::CheckCollision(const SDL_Rect &a, const SDL_Rect &b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
    {
        return false;
    }
    return true;
}

void Collision::Col_bullet_enemy(MainObject &player, std::vector<SmallEnemy*> &SmallSpawner, Gun &gun, std::vector<Exp*> &Exp_List, SDL_Renderer *des)
{
    std::vector<BulletBase*> bullet_list = gun.Get_Bullets();
    for(int i=0; i<(int)bullet_list.size(); i++)
    {
        BulletBase *bullet = bullet_list.at(i);
        if(bullet != NULL)
        {
            for(int j=0; j<(int)SmallSpawner.size(); j++)
            {

                SmallEnemy* smallenemy = SmallSpawner.at(j);
                SDL_Rect r_bullet, r_small_enemy;
                r_small_enemy = smallenemy->GetRect();
                r_bullet = bullet->GetRect();
                bool enemy_bullet = CheckCollision(r_small_enemy,r_bullet);
                if(enemy_bullet)
                {
                    gun.RemoveBullet(i);
                    smallenemy->MinusHP(gun.BULLET_DAME);
                    if(smallenemy->IsDead())
                    {
                        Exp* exp = new Exp;
                        exp->Load("images//exp_orb.png", des);
                        exp->Set_EXP(smallenemy->SMALL_EXP);
                        exp->Set_Position(r_small_enemy.x+31, r_small_enemy.y+31);
                        Exp_List.push_back(exp);
                        player.Set_score();

                        smallenemy->Free();
                        SmallSpawner.erase(SmallSpawner.begin() + j);
                        smallenemy = NULL;
                    }
                }
            }
        }
    }
}

void Collision::Col_player_enemy(std::vector<SmallEnemy*> &SmallSpawner, MainObject &p_player, AudioManager &audio)
{
    for(int i=0;i<(int) SmallSpawner.size(); i++)
    {
        SmallEnemy *smallenemy = SmallSpawner.at(i);

        SDL_Rect r_enemy, r_player;
        r_enemy = {smallenemy->Get_X_Pos(), smallenemy->Get_Y_Pos(),
                   smallenemy->Get_Width_Frame()-SMALL_ENEMY_FRAME_OFFSET,
                   smallenemy->Get_Height_Frame()-SMALL_ENEMY_FRAME_OFFSET};

        r_player = {p_player.Get_x_pos(), p_player.Get_y_pos(),
                    p_player.Get_width_frame()-PLAYER_FRAME_OFFSET,
                    p_player.Get_height_frame()-PLAYER_FRAME_OFFSET};

        bool enemy_player = CheckCollision(r_enemy, r_player);
        if(enemy_player)
        {
            p_player.Minus_Hp_When_Hit(smallenemy->SMALL_ENEMY_DAME);
            audio.PlaySound("hit");
        }
    }
}

void Collision::Col_player_exp(std::vector<Exp*> &Exp_List, MainObject &p_player)
{
    for(int i=Exp_List.size()-1;i>=0;i--)
    {
        Exp* exp = Exp_List.at(i);

        if(exp!=nullptr)
        {

            SDL_Rect r_player; SDL_Rect r_exp;
            r_player = {p_player.Get_x_pos(), p_player.Get_y_pos(),
                    p_player.Get_width_frame()-PLAYER_FRAME_OFFSET,
                    p_player.Get_height_frame()-PLAYER_FRAME_OFFSET};

            r_exp = exp->r_exp;
            bool player_exp = CheckCollision(r_player, r_exp);
            if(player_exp)
            {
                p_player.SetExp(exp->EXP);
                exp->Free();
                delete exp;
                exp = NULL;
                Exp_List.erase(Exp_List.begin() + i);
            }
        }
    }
}

void Collision::Col_player_nuke(MainObject &p_player, const std::vector<Nuke*> &nukes)
{
    for(auto *nuke : nukes)
    {
        if(nuke != NULL)
        {
            SDL_Rect r_nuke; SDL_Rect r_player;

            r_player = {p_player.Get_x_pos(), p_player.Get_y_pos(),
                        p_player.Get_width_frame(),
                        p_player.Get_height_frame()};

            r_nuke = nuke->GetRect();

            bool col_player_nuke = CheckCollision(r_player, r_nuke);
            bool is_done = nuke->is_explosive();

            if(col_player_nuke && is_done)
            {
                p_player.Minus_Hp_When_Hit(NUKE_DAME);
            }
        }
    }
}

void Collision::Col_enemy_nuke(std::vector<SmallEnemy*> &SmallSpawner, const std::vector<Nuke*> &nukes)
{
    for(auto *smallenemy : SmallSpawner)
    {
        if(smallenemy != NULL)
        {
            for(auto *nuke : nukes)
            {
                if(nuke != NULL)
                {
                    SDL_Rect r_nuke; SDL_Rect r_enemy;

                    r_enemy = {smallenemy->Get_X_Pos(), smallenemy->Get_Y_Pos(),
                                smallenemy->Get_Width_Frame()-SMALL_ENEMY_FRAME_OFFSET,
                                smallenemy->Get_Height_Frame()-SMALL_ENEMY_FRAME_OFFSET};
                    r_nuke = nuke->GetRect();

                    bool nuke_enemy = CheckCollision(r_nuke, r_enemy);
                    bool is_nuke_active = nuke->is_explosive();
                    if(nuke_enemy && is_nuke_active)
                    {
                        smallenemy->Set_Speed();
                        smallenemy->Set_Dame();
                    }
                }
            }
        }
    }
}

void Collision::Col_bullet_lich(Gun &gun, Lich &lich, SDL_Renderer *des)
{
    if(lich.IsDead()) return;
    if(!lich.IsDead()){
        std::vector<BulletBase*> bullet_list = gun.Get_Bullets();

        for(int i=0; i<(int)bullet_list.size(); i++)
        {
            BulletBase* bullet = bullet_list.at(i);
            if(bullet != nullptr)
            {
                SDL_Rect r_bullet; SDL_Rect r_lich;
                r_bullet = bullet->GetRect();
                r_lich = lich.GetRect();

                bool bullet_lich = CheckCollision(r_bullet, r_lich);
                if(bullet_lich)
                {

                    gun.RemoveBullet(i);
                    if(!lich.IsTelePorting()){
                        lich.MinusHP(gun.BULLET_DAME);
                    }
                }
            }
        }
    }
}
