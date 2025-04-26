
#ifndef NUKE_H_
#define NUKE_H_
#define NUKE_DAME 50
#include "commonFunc.h"

class Nuke
{
public:
    Nuke(SDL_Renderer *des);
    ~Nuke();

    void RenderAnimation(SDL_Renderer* des);
    void Set_Position();
    void set_clips();
//    void Follow();
    void update();
    bool is_explosive() {return explosive_active;}
    SDL_Rect GetRect();
    int get_boom_frame() const {return boom_frame;}
private:

    int x_pos;
    int y_pos;

    int x_target;
    int y_target;

    const int nuke_wid_frame = 96;
    const int nuke_hei_frame = 96;
    const int boom_wid_frame = 48;
    const int boom_hei_frame = 48;

    int nuke_frame;
    int boom_frame;
    bool explosive_active;

    SDL_Texture *nuke_texture;
    SDL_Texture *boom_texture;
    SDL_Texture *target;

    SDL_Rect boom_clips[6];
    SDL_Rect nuke_clips[4];
};

class NukeManager
{
public:
    NukeManager(SDL_Renderer* des);

    void SpawnBomb(int number);
    void updateBomb();
    void Render(SDL_Renderer *des);
    std::vector<Nuke*> Get_Nuke_List() {return Nuke_List;}

private:
    SDL_Renderer* renderer;
    std::vector<Nuke*> Nuke_List;
    Uint32 lastSpawnTime;
    Uint32 spawnInterval;

    const int MAX_NUKES = 10;
};

#endif // NUKE_H_
