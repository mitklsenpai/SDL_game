
#include "Nuke.h"

Nuke::Nuke(SDL_Renderer *des)
{
    x_pos = 0;
    y_pos = 0;
    x_target = 0;
    y_target = 0;
    nuke_frame = 0;
    boom_frame = 0;
    explosive_active = false;

    nuke_texture = IMG_LoadTexture(des, "images//Nuke.png");
    boom_texture = IMG_LoadTexture(des, "images//Boom.png");
    target = IMG_LoadTexture(des, "images//Target.png");

    set_clips();
    Set_Position();
}

Nuke::~Nuke()
{
    SDL_DestroyTexture(nuke_texture);
    SDL_DestroyTexture(boom_texture);
    SDL_DestroyTexture(target);
}

void Nuke::Set_Position()
{
    x_target = rand()%1280;
    y_target = rand()%640;

    x_pos = x_target;
    y_pos = y_target - 200;
}

SDL_Rect Nuke::GetRect()
{
    SDL_Rect r;
    r.x = x_target;
    r.y = y_target;
    r.w = 30;
    r.h = 27;

    return r;
}

void Nuke::update()
{
    if (!explosive_active)
    {
        y_pos += 1;
        nuke_frame = (nuke_frame + 1) % 4;
        if(y_pos >= y_target)
        {
            explosive_active = true;
            boom_frame = 0;
        }
    }
    else
    {
        if (boom_frame < 5)
        {
            boom_frame++;
        }
        else
        {
            explosive_active = false;
        }
    }
}

void Nuke::set_clips()
{
    for(int i=0;i<4;i++)
    {
        nuke_clips[i].x = i*nuke_wid_frame;
        nuke_clips[i].y = 0;
        nuke_clips[i].w = nuke_wid_frame;
        nuke_clips[i].h = nuke_hei_frame;
    }
    for(int i=0;i<6;i++)
    {
        boom_clips[i].x = i*boom_wid_frame;
        boom_clips[i].y = 0;
        boom_clips[i].w = boom_wid_frame;
        boom_clips[i].h = boom_hei_frame;
    }
}

void Nuke::RenderAnimation(SDL_Renderer* des)
{
    if(!explosive_active)
    {
        SDL_Rect renderQuad = {x_target-33,y_pos-59,nuke_wid_frame,nuke_hei_frame};
        SDL_Rect *current = &nuke_clips[nuke_frame];
        SDL_RenderCopy(des, nuke_texture, current, &renderQuad);

        SDL_Rect r = {x_target, y_target, 30, 27};
        SDL_RenderCopy(des, target, NULL, &r);
    }
    else
    {
        SDL_Rect r_ = {x_target, y_target, 48, 48};
        SDL_Rect *current_ = &boom_clips[boom_frame];
        SDL_RenderCopy(des, boom_texture, current_, &r_);
    }
}

NukeManager::NukeManager(SDL_Renderer* des)
{
    renderer = des;
    spawnInterval = 5000;
    lastSpawnTime = 0;
}

void NukeManager::SpawnBomb(int number)
{
    for(int i=0;i<number;i++)
    {
        Nuke_List.push_back(new Nuke(renderer));
    }
}

void NukeManager::updateBomb()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastSpawnTime >= spawnInterval) {
        SpawnBomb(MAX_NUKES);
        lastSpawnTime = currentTime;
    }

    for(int i = Nuke_List.size() - 1; i >= 0; i--)
    {
        Nuke *nuke = Nuke_List.at(i);
        nuke->update();
        if(!nuke->is_explosive() && nuke->get_boom_frame() >= 5)
        {
            delete nuke;
            nuke = NULL;
            Nuke_List.erase(Nuke_List.begin() + i);
        }
    }
}

void NukeManager::Render(SDL_Renderer *renderer)
{
    for(auto *nuke : Nuke_List)
    {
        nuke->RenderAnimation(renderer);
    }
}

