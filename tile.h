//Arman Farhangi
//May 14, 2015
//BOX-MAN Game
//C++ and SDL

#ifndef pacman_tile_h
#define pacman_tile_h

//libraries
#include <SDL2/SDL.h>
//headers
#include "globals.h"
#include "collider.h"

/******* TILE CLASS DECLARES *******/
//obstacle or non-obstacle tile clip
class Tile : public Collider
{
public:
    //constructor
    Tile(int obstacle_state, int x_tile, int y_tile);
    //accessor
    SDL_Rect& get_clip();
private:
    //clip to render tile
    SDL_Rect clip;
};

#endif
