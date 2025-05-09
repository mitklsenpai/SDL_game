#ifndef PLAYER_H_
#define PLAYER_H_

#include "commonFunc.h"

class Player
{
public:
    Player();
    ~Player();

    void SetRect(const int& x, const int& y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Texture* GetObject() const {return p_object_;} // ham lay ra p_object
    void Render(SDL_Renderer *des, const SDL_Rect* clips = NULL);
    void Render(SDL_Renderer *des, SDL_Texture* texture, const SDL_Rect &rect);
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    SDL_Texture* Loadimg(std::string path, SDL_Renderer* screen);
    void Free();
    void PlayAnimation(SDL_Renderer *des, SDL_Rect clips[], int currentFrame, SDL_Rect renderQuad, SDL_Texture *texture);
    void setClips(SDL_Rect clips[], int clips_size, int wid, int hei);

    SDL_Texture* p_object_;
    SDL_Rect rect_;
};


#endif // PLAYER_H_
