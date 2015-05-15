//Arman Farhangi
//May 14, 2015
//BOX-MAN Game
//C++ and SDL

//headers
#include "tile.h"
#include "globals.h"

/******* TILE CLASS DEFS *******/

//constructor determines clip for tile to be rendered
Tile::Tile( int obstacle_state )
{
    //if tile is obstacle
    if ( obstacle_state == 1 )
    {
        clip = { TILE_WIDTH*1, TILE_HEIGHT*0, TILE_WIDTH, TILE_HEIGHT };
        is_obstacle = true;
    }
    //if tile isn't obstacle
    else if ( obstacle_state == 0 )
    {
        clip = { TILE_WIDTH*0, TILE_HEIGHT*0, TILE_WIDTH, TILE_HEIGHT };
        is_obstacle = false;
    }
}

//gets clip
SDL_Rect& Tile::get_clip()
{
    return clip;
}