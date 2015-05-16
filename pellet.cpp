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
Pellet::Pellet(bool is_pellet, int x, int y)
{
    //if tile read in is pellet, then create pellet
    if (is_pellet == true)
        hitbox = { (x + TILE_WIDTH/2 - 2), (y + TILE_HEIGHT/2 - 2), 4, 4 };
    //if not, don't create anything
    else if (is_pellet == false)
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