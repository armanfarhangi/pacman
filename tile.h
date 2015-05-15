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

/******* TILE CLASS DECLARES *******/
//obstacle or non-obstacle tile clip
class Tile
{
public:
    //constructor
    Tile(int obstacle_state);
    //accessor
    SDL_Rect& get_clip();
private:
    //clip to render tile
    SDL_Rect clip;
    //obstacle state
    bool is_obstacle;
};

#endif
