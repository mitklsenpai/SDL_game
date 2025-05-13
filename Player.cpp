#include "commonFunc.h"
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
    Free();
}
// ham nay se co nhiem vu load anh
bool Player::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;        // buc anh cuoi cung, sau khi xu ly

    SDL_Surface* load_surface = IMG_Load(path.c_str());         // tao anh tu duong dan
    if(load_surface != NULL)
    {
        SDL_SetColorKey(load_surface,SDL_TRUE ,SDL_MapRGB(load_surface->format, 167, 175, 180)); //xoa phong buc anh
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL)
        {
            rect_.w = load_surface->w;  // thu duoc chieu cao/do rong cua anh sau xu ly
            rect_.h = load_surface->h;
        }

        SDL_FreeSurface(load_surface); // xoa anh cu
    }
    p_object_ = new_texture; // lay anh moi sau chinh sua
    return p_object_ != NULL;
}

SDL_Texture* Player::Loadimg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;        // buc anh cuoi cung, sau khi xu ly

    SDL_Surface* load_surface = IMG_Load(path.c_str());         // tao anh tu duong dan
    if(load_surface != NULL)
    {
        SDL_SetColorKey(load_surface,SDL_TRUE ,SDL_MapRGBA(load_surface->format, 247,118,122,255)); //xoa phong buc anh
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);

        SDL_FreeSurface(load_surface); // xoa anh cu
    }

    return new_texture;
}

void Player::Render(SDL_Renderer *des, const SDL_Rect* clips)
{
    SDL_RenderCopy(des, p_object_, NULL, &rect_);
}

void Player::Render(SDL_Renderer *des, SDL_Texture* texture, const SDL_Rect &rect)
{
    SDL_RenderCopy(des, texture, NULL, &rect);
}

void Player::PlayAnimation(SDL_Renderer *des, SDL_Rect clips[], int currentFrame, SDL_Rect renderQuad, SDL_Texture *texture)
{
    SDL_Rect *current = &clips[currentFrame];

    SDL_RenderCopy(des, texture, current, &renderQuad);
}

void Player::setClips(SDL_Rect clips[], int clips_size, int wid, int hei)
{
    for(int i=0;i<clips_size;i++)
    {
        clips[i] = {i*wid, 0, wid, hei};
    }
}

void Player::setClips(SDL_Rect clips[], int clips_size, int wid, int hei, int row, int col)
{
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            int i = r * col + c;
            clips[i] = {c*wid, r*hei, wid, hei};
        }
    }
}

void Player::Free()
{
    if(p_object_!=NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
