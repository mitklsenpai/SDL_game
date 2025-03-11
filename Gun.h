
#ifndef GUN_H_
#define GUN_H_

#include "commonFunc.h"
#include "MainObject.h"

#define MAX_BULLETS 3

class Gun : public Player
{
public:
    Gun();
    ~Gun();

    void Rotation(MainObject &player, SDL_Renderer* des);
    void HandleMouseEvents(SDL_Event events, SDL_Renderer* screen);
    void SetPosition();
    bool LoadImg(std::string path, SDL_Renderer* screen);

private:
    float x_pos;
    float y_pos;

    int x_target;
    int y_target;

    bool is_shot;
};


#endif // SHOT_GUN_H_
