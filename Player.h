//#ifndef PLAYER_H_
//#define PLAYER_H_

#include "commonFunc.h"

class Player
{
public:
    Player();
    ~Player();

// ham set kich thuoc
    void SetRect(const int& x, const int& y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect GetRect() const {return rect_;} // lay kich thuoc anh
    SDL_Texture* GetObject() const {return p_object_;} // ham lay ra p_object

// ham load anh
    bool LoadImg(std::string path, SDL_Renderer* screen);
// ham render anh
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();

private:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
};


//#endif // PLAYER_H_
