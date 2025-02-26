
#ifndef MAP_H_
#define MAP_H_

#include "commonFunc.h"
#include "Player.h"

class TileMat : public Player
{
public:
    TileMat(){;}
    ~TileMat(){;}
};

class GameMap
{
public:
    GameMap(){;}
    ~GameMap(){;}

    void LoadMap(char* name);  // doc cai file chua map
    void LoadTiles(SDL_Renderer* screen); // load tile cua map
    void DrawMap(SDL_Renderer* screen);

private:
    Map game_map_;
    TileMat tile_mat[20];

};


#endif // MAP_H_
