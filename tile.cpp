//Arman Farhangi
//May 14, 2015
//BOX-MAN Game
//C++ and SDL

//headers
#include "tile.h"
#include "globals.h"

/******* TILE CLASS DEFS *******/

//constructor determines clip for tile to be rendered
Tile::Tile( int obstacle_state, int x_tile, int y_tile )
{
    //if tile is obstacle
    if ( obstacle_state == 1 )
    {
        //set obstacle clip to render from spritesheet
        clip = { TILE_WIDTH*1, TILE_HEIGHT*0, TILE_WIDTH, TILE_HEIGHT };
        //set hitbox on window position
        hitbox = { TILE_WIDTH * x_tile, TILE_HEIGHT * y_tile, TILE_WIDTH, TILE_HEIGHT };
    }
    //if tile isn't obstacle
    else if ( obstacle_state == 0 )
    {
        //set non-obstacle clip to render from spritesheet
        clip = { TILE_WIDTH*0, TILE_HEIGHT*0, TILE_WIDTH, TILE_HEIGHT };
        //set hitbox on window position
        hitbox = { 0, 0, 0, 0 };
    }
}

//gets clip
SDL_Rect& Tile::get_clip()
{
    return clip;
}