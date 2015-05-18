//Arman Farhangi
//May 15, 2015
//BOX-MAN Game
//C++ and SDL

//libraries
#include <SDL2/SDL.h>
//headers
#include "pellet.h"
#include "globals.h"


/******* PELLET CLASS DEFS *******/
//constructor sets clip in relation to bool
Pellet::Pellet(int pellet_type, int x, int y)
{
    //if regular pellet
    if (pellet_type == 1)
        hitbox = { (x + TILE_WIDTH/2 - 2), (y + TILE_HEIGHT/2 - 2), 4, 4 };
    //if big pellet
    else if (pellet_type == 2)
        hitbox = { (x + TILE_WIDTH/2 - 6), (y + TILE_HEIGHT/2 - 6), 12, 12 };
        //if no pellet
    else if (pellet_type == 0)
        hitbox = { 0, 0, 0, 0};
}


//render pellet
void Pellet::render()
{
    SDL_RenderFillRect(renderer, &hitbox);
}

//destroy pellet
void Pellet::destroy()
{
    hitbox = { 0, 0, 0, 0 };
}