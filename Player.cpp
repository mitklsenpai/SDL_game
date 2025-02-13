
#include "Player.h"

Player::Player()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

Player::~Player()
{

}
// ham nay se co nhiem vu load anh
bool Player::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;        // buc anh cuoi cung, sau khi xu ly

    SDL_Surface* load_surface = IMG_Load(path.c_str());         // tao anh tu duong dan
    if(load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_MapRGB(load_surface->format, COLOR_KEY_B,COLOR_KEY_G,COLOR_KEY_R)); //xoa phong buc anh
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL)
        {
            rect_.w = load_surface->w;  // thu duoc chieu cao/do rong cua anh sau xu ly
            rect_.h = load_surface->h;
        }

        SDL_FreeSurface(load_surface); // xoa anh cu
    }
    p_object_ = new_texture; //
    return p_object_ != NULL;
}
